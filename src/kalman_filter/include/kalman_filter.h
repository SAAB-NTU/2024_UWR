#ifndef KALMAN_FILTER
#define KALMAN_FILTER

#include <eigen3/Eigen/Dense>
#include <iostream>
#include "Iir.h"
#include "sonar_processing.h"
#include <vector>
#include <cmath>
#include <random>
#include <numeric>
#include <algorithm>
#include <string>
#include <sstream>
#include <armadillo>

class KalmanFilter
{
public:
    KalmanFilter();
    Eigen::Vector2f prediction(const float& u, const float& dt);
    Eigen::Vector2f update(const Eigen::Vector2f& z);
    Eigen::Vector2f residual(const Eigen::Vector2f& z);
    Eigen::Matrix2f Q, R;

protected:
    Eigen::Matrix2f F, P, H;
    Eigen::Vector2f x, B;
};

class KalmanFilter_6dof
{
public:
    KalmanFilter_6dof();
    Eigen::Matrix<double, 6, 1> prediction(const Eigen::Matrix<double, 3, 1>& u, const float& dt);
    Eigen::Matrix<double, 6, 1> update(const Eigen::Matrix<double, 6, 1>& z);
    Eigen::Matrix<double, 6, 1> residual(const Eigen::Matrix<double, 6, 1>& z);
    Eigen::Matrix<double, 6, 6> Q, R;

protected:
    Eigen::Matrix<double, 6, 6> F, P, H, K;
    Eigen::Matrix<double, 6, 1> x;
    Eigen::Matrix<double, 6, 3> B;
};

class KalmanFilter_6dof_FLS
{
public:
    KalmanFilter_6dof_FLS();
    Eigen::Matrix<double, 6, 1> prediction(const Eigen::Matrix<double, 3, 1>& u, const float& dt);
    Eigen::Matrix<double, 6, 1> update(const Eigen::Matrix<double, 6, 1>& z, Eigen::Matrix<double, 6, 6>& R, Eigen::Matrix<double, 6, 6>& H);
    Eigen::Matrix<double, 6, 1> residual(const Eigen::Matrix<double, 6, 1>& z, Eigen::Matrix<double, 6, 6>& H);
    Eigen::Matrix<double, 6, 6> Q, R1, R2;

protected:
    Eigen::Matrix<double, 6, 6> F, P, H1, H2, K;
    Eigen::Matrix<double, 6, 1> x;
    Eigen::Matrix<double, 6, 3> B;
};

class kf_v3
{
public:
    kf_v3();
    kf_v3(int sample_size);  // New constructor
    Eigen::Vector2f prediction(double dt);
    
    Eigen::Vector2f update(), get_state();
    //update(const Eigen::Vector2f& external_z, const Eigen::Matrix2f& external_H);
    Eigen::Vector2f update(Eigen::Matrix2f& external_R);
    double residual();
    bool get_accel_bias(), set_accel_bias(bool val, double bias);
    bool set_dist_init(double init);
    double set_accel(double val);
    double set_dist(double val);
    double set_vel(double dt);
    void set_prev_dist();
    SonarProcess moving_avg,moving_avg_vel,moving_avg_time;

    Eigen::Matrix2f Q, R,K;

protected:
    Eigen::Matrix2f F, P, H;
    Eigen::Vector2f x, B, z, y;
    double prev_measurement_dist, final_dist, meas_bias, accel_bias, accel, vel, dist, previous_predict_time, conf;
    float samplingrate;
    double cutoff_frequency, dist_bias;
    int avg_window;
    bool bias_reset, bias_reset_dist;

    Iir::Butterworth::LowPass<4> bw_filter;
    Iir::Butterworth::HighPass<4> bw_filter2;
};

class kf_v4
{
public:
    kf_v4();
    kf_v4(int sample_size);  // New constructor
    Eigen::Vector3f prediction(double dt);
    
    Eigen::Vector3f update(), get_state();
    //update(const Eigen::Vector2f& external_z, const Eigen::Matrix2f& external_H);
    Eigen::Vector3f update(Eigen::Matrix3f& external_R);
    double residual();
    bool set_dist_init(double init);
    double set_accel(double val);
    double set_dist(double val);
    double set_vel(double dt);
     bool get_accel_bias(), set_accel_bias(bool val, double bias);
    double set_jerk(double dt);
    void set_prev_dist();
    SonarProcess moving_avg,moving_avg_vel,moving_avg_time;

    Eigen::Matrix3f Q, R,K;

protected:
    Eigen::Matrix3f F, P, H;
    Eigen::Vector3f x, B, z, y;
    double prev_measurement_dist, final_dist, meas_bias, accel_bias, accel, vel, dist, previous_predict_time, conf,jerk;
    float samplingrate;
    double cutoff_frequency, dist_bias;
    int avg_window;
    bool bias_reset, bias_reset_dist;

    Iir::Butterworth::LowPass<4> bw_filter;
    Iir::Butterworth::HighPass<4> bw_filter2;
};

#endif // KALMAN_FILTER



