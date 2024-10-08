#ifndef CONFIDENCE_LEVEL_H
#define CONFIDENCE_LEVEL_H

#include <vector>
#include <string>

double adjustScalar(double currentConfidence, double targetConfidence = 95, double x = 1.0, double adjustmentFactor = 0.6, double maxScalar = 6.0);
std::vector<double> generateRandomNumbersWithNoise(int size = 200, double lowerBound = 1, double upperBound = 60, double mean = 0, double stdDev = 1);
std::vector<std::pair<std::vector<double>, std::string>> calculateConfidenceLevels(const std::vector<double>& numbers, double initialX = 1.0, double maxScalar = 6.0);

#endif // CONFIDENCE_LEVEL_H

