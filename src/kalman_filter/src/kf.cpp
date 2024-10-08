#include "../include/kalman_filter.h"
#include "../include/sonar_processing.h"


kf_v3::kf_v3() : moving_avg(10),moving_avg_vel(3),moving_avg_time(3)  // Default constructor
{
    x << 0,0;
    z << 0,0;
    H << 0,0,0,1;
    P << 1,0,0,1;
    Q << 0.0001,0,0,0.0001;
    R << 100,0,0,100;
    prev_measurement_dist=0;
    meas_bias=0;
    accel_bias=0;
    dist_bias=0;
    
    accel=0;
    vel=0;
    dist=0;
    avg_window=10;
    cutoff_frequency=100;
    samplingrate=1000;
    bias_reset=false;
    moving_avg=SonarProcess(avg_window);
    //moving_avg_vel=SonarProcess(avg_window);
    //moving_avg_time=SonarProcess(avg_window);
    bw_filter.setup(samplingrate, cutoff_frequency);
}

kf_v3::kf_v3(int sample_size) : moving_avg(sample_size),moving_avg_vel(10),moving_avg_time(10)  // New constructor
{
    x << 0,0;
    z << 0,0;
    H << 0,0,0,1;
    P << 1,0,0,1;
    Q << 0.0001,0,0,0.0001;
    R << 100,0,0,100;
    prev_measurement_dist=0;
    meas_bias=0;
    accel_bias=0;
    dist_bias=0;
    accel=0;
    vel=0;
    dist=0;
    avg_window=sample_size;
    cutoff_frequency=100;
    samplingrate=1000;
    bias_reset=false;
    moving_avg=SonarProcess(avg_window);
    //moving_avg_vel=SonarProcess(avg_window);
    bw_filter.setup(samplingrate, cutoff_frequency);
}

Eigen::Vector2f kf_v3::prediction(double dt)
{
    F << 1, dt, 0, 1;
    B << 0.5 * dt * dt, dt;
    x = F * x + B * accel;
    P = F * P * F.transpose() + Q;
    return x;
}

Eigen::Vector2f kf_v3::update()
{
    z << dist, vel; 
    Eigen::Vector2f y = z - H * x;
    K = P * H.transpose() * (H * P * H.transpose() + R).inverse();
    x = x + K * y;
    P = (Eigen::Matrix2f::Identity() - K * H) * P;
    //prev_measurement_dist=dist;
    return x;
}

Eigen::Vector2f kf_v3::update(double dist,double vel, Eigen::Matrix2f& external_H) {
    Eigen::Vector2f external_z;
    external_z << dist, vel; 
    Eigen::Vector2f y = external_z - external_H * x;
    Eigen::Matrix2f external_R;
    external_R<<1,0,0,1;
    K = P * external_H.transpose() * (external_H * P * external_H.transpose() + external_R).inverse();
    x = x + K * y;
    P = (Eigen::Matrix2f::Identity() - K * external_H) * P;
    //prev_measurement_dist=dist;
    return x;
}

double kf_v3::residual()
{
    double result=prev_measurement_dist-dist;
    //prev_measurement_dist=dist;
    return result;
}

bool kf_v3::get_accel_bias()
{
    return bias_reset;
}

bool kf_v3::set_accel_bias(bool val, double bias)
{
    bias_reset = val;
    accel_bias = bias;
    return bias_reset;
}

double kf_v3::set_accel(double val)
{
    accel = (val - accel_bias);
    accel = bw_filter.filter(accel);
    return accel;
}

bool kf_v3::set_dist_init(double init) //To use tf2 ros to standardize inertial to body frame transformation
{
    bias_reset_dist = true;
    x(0) = (init);
    prev_measurement_dist = (init);
    return bias_reset_dist;
} 

double kf_v3::set_dist(double val)
{
    dist = moving_avg.MovingAvg(val);
    
    return dist;
}

double kf_v3::set_vel(double dt)
{
    //Change direction to become opposite
    //vel = abs(x(0) - dist) / dt;
    //vel = moving_avg_vel.MovingAvg(abs(prev_measurement_dist - dist))/moving_avg_time.MovingAvg(dt);
    //vel = moving_avg_vel.MovingAvg((-prev_measurement_dist + dist))/moving_avg_time.MovingAvg(dt);
    //vel=-(prev_measurement_dist - dist) / dt;
    vel=(-prev_measurement_dist + dist) / dt;
    //prev_measurement_dist = (dist);
    return vel;
}

void kf_v3::set_prev_dist()
{
    prev_measurement_dist = (dist);
}

Eigen::Vector2f kf_v3::get_state()
{
   return x; 
}





