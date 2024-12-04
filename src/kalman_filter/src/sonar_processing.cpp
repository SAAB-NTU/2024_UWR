#include "../include/sonar_processing.h"
#include "../include/ConfidenceLevel.h"
#include "../include/ConfidenceLevelVariation2.h"
#include <bits/stdc++.h>
#include <armadillo>


SonarProcess::SonarProcess(const int& window_size) 
: window_size{window_size}, confidence_window_size{10} {}

void SonarProcess::setSampleSize(int sample_size) {
    window_size = sample_size;
    multiplier=1;
}

// Getter for `output`
const std::pair<double, double>& SonarProcess::getOutput() const {
    return output;
}

void SonarProcess::clear_window()
{
    moving_avg_window.clear();
}

// Getter for `window_size`
int SonarProcess::getWindowSize() const {
    if(window_size>moving_avg_window.size())
        return 0;
    else
    return 1;
}

const std::deque<double>& SonarProcess::getMovingAvgWindow() const {
    return moving_avg_window;
}

//void SonarProcess::setSampleSize(int sample_size) {
//    window_size = sample_size;
//}

std::pair<double, double> SonarProcess::CalculateConfidenceLevelsVariation2(double expectedDifference) {
        

    if (moving_avg_window.size() == window_size) 
    {
    double fixedStdDev = expectedDifference * 3.0*multiplier;
    
    

    double lastNum = moving_avg_window.back();
    double difference = std::abs(lastNum - meanSequence);

    double sigmasAway = fixedStdDev != 0 ? std::abs(difference / fixedStdDev) : 0;
   // if (difference>expectedDifference) //If within the expected difference --> elevate to 100% 
   // {
        multiplier=1;
        confidencePercentage = sigmasAway <= 3 ? 100 - (std::abs(sigmasAway) / 3 * 100) : 0;
        confidencePercentage = std::max(0.0, std::min(100.0, confidencePercentage));
    //}
    //else
   // {
   //     multiplier=1;
   //     confidencePercentage=100.0;
   // }

    //if(confidencePercentage<20)
   // {
   //     moving_avg_window=temp_window; //Discard last element
    //    multiplier=3;//Become more lenient
   // }

    output.first = confidencePercentage;
    output.second = sigmasAway; 

    
    }
    else
    {
          output.first = 100;
        output.second = -5; 
    }
    return output;
}


double SonarProcess::MovingAvg(const float& raw_measurement) 
{
    temp_window=moving_avg_window;

    moving_avg_window.push_back(raw_measurement);
    if (moving_avg_window.size() > window_size) {
        moving_avg_window.pop_front();
    }

    else if (moving_avg_window.size() < window_size) {
        return raw_measurement;
    }
    
    std::vector<double> contiguousVector(moving_avg_window.begin(), moving_avg_window.end());
    arma::vec armaWindow(contiguousVector.data(), contiguousVector.size());

    meanSequence = arma::mean(armaWindow);
    
    return meanSequence;
    
}

//    output = CalculateConfidenceLevelsVariation2(0.006); 
 

//    return std::accumulate(moving_avg_window.begin(), moving_avg_window.end(), 0.0) / moving_avg_window.size();
//}

double SonarProcess::SequenceBeginning() {
    return moving_avg_window.front();
}

double SonarProcess::SequenceEnd() {
    return moving_avg_window.back();
}


