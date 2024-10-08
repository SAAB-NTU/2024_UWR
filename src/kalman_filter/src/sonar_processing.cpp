#include "../include/sonar_processing.h"
#include "../include/ConfidenceLevel.h"
#include "../include/ConfidenceLevelVariation2.h"
#include <bits/stdc++.h>
#include <armadillo>


SonarProcess::SonarProcess(const int& window_size) 
: window_size{window_size}, confidence_window_size{10} {}

void SonarProcess::setSampleSize(int sample_size) {
    window_size = sample_size;
}

// Getter for `output`
const std::pair<double, double>& SonarProcess::getOutput() const {
    return output;
}

// Getter for `window_size`
int SonarProcess::getWindowSize() const {
    return window_size;
}

const std::deque<double>& SonarProcess::getMovingAvgWindow() const {
    return moving_avg_window;
}

//void SonarProcess::setSampleSize(int sample_size) {
//    window_size = sample_size;
//}

std::pair<double, double> SonarProcess::CalculateConfidenceLevelsVariation2(double expectedDifference) {
    double fixedStdDev = expectedDifference / 3.0;
    
    // Convert deque to vector for Armadillo compatibility
    std::vector<double> contiguousVector(moving_avg_window.begin(), moving_avg_window.end());
    arma::vec armaWindow(contiguousVector.data(), contiguousVector.size());

    double meanSequence = arma::mean(armaWindow);
    double lastNum = moving_avg_window.back();
    double difference = std::abs(lastNum - meanSequence);

    double sigmasAway = fixedStdDev != 0 ? std::abs(difference / fixedStdDev) : 0;
    double confidencePercentage = sigmasAway <= 3 ? 100 - (std::abs(sigmasAway) / 3 * 100) : 0;
    confidencePercentage = std::max(0.0, std::min(100.0, confidencePercentage));

    output.first = confidencePercentage;
    output.second = sigmasAway; 

    return output;
}

double SonarProcess::MovingAvg(const float& raw_measurement) {
    moving_avg_window.push_back(raw_measurement);
    if (moving_avg_window.size() > window_size) {
        moving_avg_window.pop_front();
    }

    if (moving_avg_window.size() < window_size) {
        return 0.0;
    }

    output = CalculateConfidenceLevelsVariation2(0.006); 
 

    return std::accumulate(moving_avg_window.begin(), moving_avg_window.end(), 0.0) / moving_avg_window.size();
}

double SonarProcess::SequenceBeginning() {
    return moving_avg_window.front();
}

double SonarProcess::SequenceEnd() {
    return moving_avg_window.back();
}


