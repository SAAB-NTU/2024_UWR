#include "../include/kalman_filter.h"
#include "../include/sonar_processing.h"



kf_v4::kf_v4() : moving_avg(10),moving_avg_vel(3),moving_avg_time(3) 
{
    x << 0,0,0;
    z << 0,0,0;
    H << 1,0,0,0,1,0,0,0,0;
    P << 1,0,0,0,1,0,0,0,1;
    Q << 1,1,1,1,1,1,1,1,1;
    R << 1,1,1,1,1,1,1,1,1;
    prev_measurement_dist=0;
    meas_bias=0;
    accel_bias=0;
    dist_bias=0;
    accel=0;
    jerk=0;
    vel=0;
    dist=0;
    avg_window=10;
    cutoff_frequency=0.01;
    samplingrate=400;
    bias_reset=false;
    moving_avg=SonarProcess(avg_window);
    //moving_avg_vel=SonarProcess(avg_window);
    bw_filter.setup(samplingrate, cutoff_frequency);
    bw_filter2.setup(samplingrate, 0.05);
}

kf_v4::kf_v4(int sample_size) : moving_avg(sample_size),moving_avg_vel(10),moving_avg_time(10)  // New constructor
{
    x << 0,0,0;
    z << 0,0,0;
    H << 1,0,0,0,1,0,0,0,0;
    P << 1,0,0,0,1,0,0,0,1;
    Q << 1,1,1,1,1,1,1,1,1;
    R << 1,1,1,1,1,1,1,1,1;
    prev_measurement_dist=0;
    meas_bias=0;
    accel_bias=0;
    dist_bias=0;
    accel=0;
    jerk=0;
    vel=0;
    dist=0;
    avg_window=sample_size;
    cutoff_frequency=0.01;
    samplingrate=400;
    bias_reset=false;
    moving_avg=SonarProcess(avg_window);
    //moving_avg_vel=SonarProcess(avg_window);
    bw_filter.setup(samplingrate, cutoff_frequency);
    bw_filter2.setup(samplingrate, 0.05);
}

Eigen::Vector3f kf_v4::prediction(double dt)
{
    F << 1, dt,(1/6) * dt * dt* dt, 0, 1,0.5 * dt * dt,0,0,dt;
    B<<0.5 * dt * dt,dt,1;
    x = F * x + B * accel;
    P = F * P * F.transpose() + Q;
    return x;
}

Eigen::Vector3f kf_v4::update()
{
    z << dist, vel,accel; 
    Eigen::Vector3f y = z - H * x;
    K = P * H.transpose() * (H * P * H.transpose() + R).inverse();
    x = x + K * y;
    P = (Eigen::Matrix3f::Identity() - K * H) * P;
    //prev_measurement_dist=dist;
    return x;
}

Eigen::Vector3f kf_v4::update(Eigen::Matrix3f& external_R) {
    Eigen::Vector3f external_z;
    external_z << dist, vel,accel; 
    Eigen::Vector3f y = external_z - H * x;
    //Eigen::Matrix2f external_R;
    //external_R<<1,0,0,1;
    K = P * H.transpose() * (H * P * H.transpose() + external_R).inverse();
    x = x + K * y;
    P = (Eigen::Matrix3f::Identity() - K * H) * P;
    //prev_measurement_dist=dist;
    return x;
}

double kf_v4::residual()
{
    double result=prev_measurement_dist-dist;
    //prev_measurement_dist=dist;
    return result;
}



double kf_v4::set_accel(double val)
{
    //accel = (val - accel_bias);
    accel =bw_filter2.filter(bw_filter.filter((val-accel_bias)));
    //accel =(bw_filter.filter((val-accel_bias)));
    return accel;
}

bool kf_v4::get_accel_bias()
{
    return bias_reset;
}

bool kf_v4::set_accel_bias(bool val, double bias)
{
    bias_reset = val;
    accel_bias = bias;
    return bias_reset;
}

double kf_v4::set_jerk(double dt)
{
    //Change direction to become opposite
    //vel = abs(x(0) - dist) / dt;
    //vel = moving_avg_vel.MovingAvg(abs(prev_measurement_dist - dist))/moving_avg_time.MovingAvg(dt);
    //vel = moving_avg_vel.MovingAvg((-prev_measurement_dist + dist))/moving_avg_time.MovingAvg(dt);
    //vel=-(prev_measurement_dist - dist) / dt;
    //jerk=(-accel_prev + accel) / dt;
    //accel_prev=accel;
    //prev_measurement_dist = (dist);
    return jerk;
}

bool kf_v4::set_dist_init(double init) //To use tf2 ros to standardize inertial to body frame transformation
{
    bias_reset_dist = true;
    x(0) = (init);
    prev_measurement_dist = (init);
    return bias_reset_dist;
} 

double kf_v4::set_dist(double val)
{
    dist = moving_avg.MovingAvg(val);
    
    return dist;
}

double kf_v4::set_vel(double dt)
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

void kf_v4::set_prev_dist()
{
    prev_measurement_dist = (dist);
}

Eigen::Vector3f kf_v4::get_state()
{
   return x; 
}





