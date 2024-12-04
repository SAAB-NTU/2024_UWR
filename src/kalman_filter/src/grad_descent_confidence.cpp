#include "rclcpp/rclcpp.hpp"
#include "sonar_msgs/msg/three_sonar_depth.hpp"
#include "std_msgs/msg/float64.hpp"
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>

class SonarConfidenceNode : public rclcpp::Node {
private:
    rclcpp::Subscription<sonar_msgs::msg::ThreeSonarDepth>::SharedPtr subscription_;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
    
    // Confidence metric variables
    double learningRate_;
    double maxLoss_;
    double weight_;
    std::vector<double> recentReadings_;
    int windowSize_;
    double previousReading_;

    // File stream for logging
    std::ofstream logFile_;

    // Utility function to calculate variance
    double calculateVariance(const std::vector<double>& readings) {
        if (readings.empty()) return 0.0;
        double mean = std::accumulate(readings.begin(), readings.end(), 0.0) / readings.size();
        double variance = 0.0;
        for (double r : readings) {
            variance += std::pow(r - mean, 2);
        }
        return variance / readings.size();
    }

    // Calculate confidence
 double calculateConfidence(double currentReading) {
    // Temporal loss
    double temporalLoss = std::abs(currentReading - previousReading_);
    
    // Variance loss
    double varianceLoss = calculateVariance(recentReadings_);
    
    // Total loss
    double totalLoss = temporalLoss + varianceLoss;

    // Adjust weight with recovery mechanism
    if (totalLoss < 1.0) { // Recovery when loss is very low
        weight_ += learningRate_;
    } else { // Normal adjustment during higher losses
        weight_ -= learningRate_ * totalLoss;
    }
    weight_ = std::clamp(weight_, 0.01, 100.0); // Keep weight in valid range
    
    // Update sliding window
    if (recentReadings_.size() >= windowSize_) {
        recentReadings_.erase(recentReadings_.begin());
    }
    recentReadings_.push_back(currentReading);

    // Weighted loss
    double weightedLoss = totalLoss * (1.0 - weight_); // Invert weight's impact on loss

    // Confidence metric
    RCLCPP_INFO(this->get_logger(), "Total Loss: %f, Weighted Loss: %f, Weight: %f", totalLoss, weightedLoss, weight_);
    return std::max(0.0, 1.0 - std::min(totalLoss / maxLoss_, 1.0));
}
    // Log data to CSV file
    void logToCSV(double distance, double confidence) {
        if (logFile_.is_open()) {
            logFile_ << distance << "," << confidence << "\n";
        }
    }

public:
    SonarConfidenceNode() : Node("sonar_confidence_node"), 
        learningRate_(0.001), maxLoss_(5000.0), weight_(100.0), 
        windowSize_(30), previousReading_(0.0) {
        
        // Open the log file in append mode
        logFile_.open("sonar_confidence_log.csv", std::ios::app);
        if (!logFile_) {
            RCLCPP_ERROR(this->get_logger(), "Failed to open log file!");
        } else {
            logFile_ << "Distance,Confidence\n"; // Add header row if creating a new file
        }

        // Create subscription to ThreeSonarDepth topic
        subscription_ = this->create_subscription<sonar_msgs::msg::ThreeSonarDepth>(
            "/sonar", 10,
            [this](const sonar_msgs::msg::ThreeSonarDepth::SharedPtr msg) {
                double currentReading = msg->distance_2;  // Extract distance from the z-axis
                double confidence = calculateConfidence(currentReading);
                
                // Publish confidence
                auto confidence_msg = std_msgs::msg::Float64();
                confidence_msg.data = static_cast<float>(confidence);
                publisher_->publish(confidence_msg);
                
                // Log to CSV
                logToCSV(currentReading, confidence);
                
                // Update previous reading
                previousReading_ = currentReading;

                RCLCPP_INFO(this->get_logger(), "Reading: %.2f, Confidence: %.2f", currentReading, confidence);
            });

        // Create publisher for confidence metric
        publisher_ = this->create_publisher<std_msgs::msg::Float64>("/sonar/confidence", 10);

        RCLCPP_INFO(this->get_logger(), "Sonar Confidence Node Initialized");
    }

    ~SonarConfidenceNode() {
        if (logFile_.is_open()) {
            logFile_.close();
        }
    }
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SonarConfidenceNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
