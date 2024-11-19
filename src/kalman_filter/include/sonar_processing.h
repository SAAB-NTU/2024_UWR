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
    
    
    void setSampleSize(int sample_size);
    double MovingAvg(const float& raw_measurement);
    double SequenceBeginning();
    double SequenceEnd();
    std::pair<double, double> CalculateConfidenceLevelsVariation2(double expectedDifference);

   
    // Getter for private members
    const std::pair<double, double>& getOutput() const;
    int getWindowSize() const;

    // Getter for moving_avg_window (from the previous update)
    const std::deque<double>& getMovingAvgWindow() const;

private:
    int window_size;
    int confidence_window_size;
    std::deque<double> moving_avg_window,temp_window;
    std::pair<double, double> output;
    double meanSequence,confidencePercentage,multiplier;


};

#endif // SONAR_PROCESSING



