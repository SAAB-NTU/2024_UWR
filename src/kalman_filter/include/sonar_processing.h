#ifndef SONAR_PROCESSING
#define SONAR_PROCESSING

#include <deque>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <cmath>
#include <random>
#include <numeric>
#include <algorithm>
#include <string>
#include <sstream>
#include <armadillo>

class SonarProcess {
public:
    SonarProcess(const int& window_size);
    double MovingAvg(const float& raw_measurement);
    double SequenceBeginning();
    double SequenceEnd();
    void setSampleSize(int sample_size);

    int window_size;
    std::pair<double, double> output,debug;

private:
    int confidence_window_size;
    std::deque<double> moving_avg_window;
    std::deque<double> confidence_window;

    std::pair<double, double> CalculateConfidenceLevels(double initialX, double maxScalar);
    double adjustScalar(double currentConfidence, double targetConfidence, double initialX, double adjustmentFactor, double maxScalar);
};

#endif // SONAR_PROCESSING



