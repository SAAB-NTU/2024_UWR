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
    Eigen::Vector2f x, B, z, y,IMU_x;
    double prev_measurement_dist, final_dist, meas_bias, accel_bias, accel, vel, dist, previous_predict_time, conf,init_dist;
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


class KalmanFilter_3dof
{
public:
    KalmanFilter_3dof();
    Eigen::Matrix<double, 6, 1> prediction(const float& dt);
    Eigen::Matrix<double, 6, 1> update(),update(Eigen::Matrix<double,6,6> external_R);
    Eigen::Matrix<double, 6, 1> residual();
    Eigen::Matrix<double, 6, 6> Q, R,K;
    Eigen::Matrix<double,6,1> get_state();


    void set_accel_bias(double bias_surge,double bias_sway,double bias_heave);
    void set_dist_init(double init_surge,double init_sway, double init_heave);
    Eigen::Vector3d set_accel(double accel_surge,double accel_sway, double accel_heave);
    SonarProcess moving_avg_surge,moving_avg_sway,moving_avg_heave,moving_avg_vel,moving_avg_time;
    Eigen::Vector3d set_dist(double val_surge,double val_sway, double val_heave);
    void set_vel(double dt);
    void set_prev_dist();
protected:
    Eigen::Matrix<double, 6, 6> F, P, H;
    Eigen::Matrix<double, 6, 1> x,z;
    Eigen::Matrix<double, 6, 3> B;
    Eigen::Vector3d dist,vel,conf,accel,prev_measurement_dist,accel_bias;
    


    // accel_bias, accel, vel, dist, previous_predict_time, conf;
    float samplingrate;
    double cutoff_frequency, dist_bias;
    int sample_size;
    bool bias_reset,bias_reset_dist;
    
    Iir::Butterworth::LowPass<4> bw_filter_surge,bw_filter_sway,bw_filter_heave;
    //Iir::Butterworth::HighPass<4> bw_filter2;
};
#endif // KALMAN_FILTER



