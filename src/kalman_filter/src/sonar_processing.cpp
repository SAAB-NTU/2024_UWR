#include "../include/sonar_processing.h"
#include <bits/stdc++.h>
#include <armadillo>

SonarProcess::SonarProcess(const int& window_size) : window_size{window_size}, confidence_window_size{10} {}

void SonarProcess::setSampleSize(int sample_size) {
    window_size = sample_size;
}

double SonarProcess::adjustScalar(double currentConfidence, double targetConfidence, double initialX, double adjustmentFactor, double maxScalar) {
    double x = initialX;
    double error = targetConfidence - currentConfidence;

    // Use a smaller threshold for more gradual changes
    if (std::abs(error) > 5) {
        x += std::copysign(adjustmentFactor, error);
    }
    else
    {
        x-=adjustmentFactor;
    }

    x = std::min(x, maxScalar);
    x = std::max(x, 1.0);

    return x;
}


std::pair<double, double> SonarProcess::CalculateConfidenceLevels(double initialX, double maxScalar) {
    double x = initialX;
    std::vector<double> contiguousVector(moving_avg_window.begin(), moving_avg_window.end());
    arma::vec armaWindow(contiguousVector.data(), contiguousVector.size());

    double meanSequence = arma::mean(armaWindow);
    double lastNum = moving_avg_window.back();
    double difference = std::abs(lastNum - meanSequence);//Max theoretically possible distance 0.1

    double stdDev = arma::stddev(armaWindow);
    //double mad = arma::mean(arma::abs(armaWindow - meanSequence));
    double adjustedStdDev = stdDev * x;
    double sigmasAway = adjustedStdDev != 0 ? difference / adjustedStdDev : 0;
    double confidencePercentage = sigmasAway <= 1.2 ? 100 - (sigmasAway /1.2 * 100) :0;
    //confidencePercentage = std::max(0.0, std::min(100.0, confidencePercentage));

    x = adjustScalar(confidencePercentage, 100, x, 0.01, maxScalar);  // Reduced adjustment factor for gradual changes

    output.first = confidencePercentage;
    output.second = x;
    debug.first=sigmasAway;
    debug.second=adjustedStdDev;

    return output;
}

double SonarProcess::MovingAvg(const float& raw_measurement) {
    if (moving_avg_window.size() == window_size) {
        moving_avg_window.pop_front();
    }
    moving_avg_window.push_back(raw_measurement);

   // output = CalculateConfidenceLevels(1, 1.5);  // Pass the current scalar value

    return std::accumulate(moving_avg_window.begin(), moving_avg_window.end(), 0.0) / moving_avg_window.size();
}

double SonarProcess::SequenceBeginning() {
    return moving_avg_window.front();
}

double SonarProcess::SequenceEnd() {
    return moving_avg_window.back();
}


