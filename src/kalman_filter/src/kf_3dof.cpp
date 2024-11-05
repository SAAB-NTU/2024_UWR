#include "../include/kalman_filter.h"

KalmanFilter_3dof::KalmanFilter_3dof(): moving_avg_surge(10),moving_avg_sway(10),moving_avg_heave(10),moving_avg_vel(10),moving_avg_time(10)
{
     

x << 0,0,0,0,0,0; //6x1 state variable


    
   P << 1, 0, 0, 0, 0, 0,
         0, 1, 0, 0, 0, 0,
         0, 0, 1, 0, 0, 0,
         0, 0, 0, 1, 0, 0,
         0, 0, 0, 0, 1, 0,
         0, 0, 0, 0, 0, 1; //6x6 covariancematrix; so no covariance between state variables
    Q << 1, 5, 10, 10, 10, 10,
         5, 1, 10, 10, 10, 10,
         0, 0, 0.001, 1, 0, 0,
         0, 0, 1, 0.001, 0, 0,
         0, 0, 0, 0, 1, 0,
         0, 0, 0, 0, 0, 1;

    R<< 1, 0, 0, 0, 0, 0,
         0, 1, 0, 0, 0, 0,
         0, 0, 100000, 0, 0, 0,
         0, 0, 0, 100000, 0, 0,
         0, 0, 0, 0, 1, 0,
         0, 0, 0, 0, 0, 1; //6x6 process noise
    
    H << 1, 0, 0, 0, 0, 0,
         0, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 1, 0,
         0, 0, 0, 0, 0, 1; //6x6 measurement noise
    
    prev_measurement_dist<<0,0,0;
    dist_bias=0;
    accel<<0,0,0;
    vel<<0,0,0;
    dist<<0,0,0;
    
    cutoff_frequency=0.01;
    samplingrate=400;
    bias_reset=false;
    moving_avg_surge=SonarProcess(10);
    moving_avg_sway=SonarProcess(10);
    moving_avg_heave=SonarProcess(10);
    //moving_avg_vel=SonarProcess(avg_window);
    bw_filter_surge.setup(samplingrate, cutoff_frequency);
    bw_filter_sway.setup(samplingrate, cutoff_frequency);
    bw_filter_heave.setup(samplingrate, cutoff_frequency);
   // bw_filter2.setup(samplingrate, 0.05);
         
}
/*
KalmanFilter_3dof::KalmanFilter_3dof(): moving_avg_surge(sample_size),moving_avg_sway(sample_size),moving_avg_heave(sample_size),moving_avg_vel(10),moving_avg_time(10)
{
     

x << 0,0,0,0,0,0; //6x1 state variable


    
   P << 0.01, 0, 0, 0, 0, 0,
         0, 0.01, 0, 0, 0, 0,
         0, 0, 0.01, 0, 0, 0,
         0, 0, 0, 0.01, 0, 0,
         0, 0, 0, 0, 0.01, 0,
         0, 0, 0, 0, 0, 0.01; //6x6 covariancematrix; so no covariance between state variables
    Q << 10, 0, 0, 0, 0, 0,
         0, 10, 0, 0, 0, 0,
         0, 0, 10, 0, 0, 0,
         0, 0, 0, 10, 0, 0,
         0, 0, 0, 0, 10, 0,
         0, 0, 0, 0, 0, 10; //6x6 process noise
    R << 0.01, 0, 0, 0, 0, 0,
         0, 0.01, 0, 0, 0, 0,
         0, 0, 0.01, 0, 0, 0,
         0, 0, 0, 0.01, 0, 0,
         0, 0, 0, 0, 0.01, 0,
         0, 0, 0, 0, 0, 0.01; //6x6 covariancematrix; so no covariance between state variables
    
    prev_measurement_dist<<0,0,0,0,0,0;
    dist_bias=0;
    accel<<0,0,0;
    vel<<0,0,0;
    dist<<0,0,0;
    
    cutoff_frequency=0.01;
    samplingrate=400;
    bias_reset=false;
    moving_avg_surge=SonarProcess(sample_size);
    moving_avg_sway=SonarProcess(sample_size);
    moving_avg_heave=SonarProcess(sample_size);
    //moving_avg_vel=SonarProcess(avg_window);
    bw_filter_surge.setup(samplingrate, cutoff_frequency);
    bw_filter_sway.setup(samplingrate, cutoff_frequency);
    bw_filter_heave.setup(samplingrate, cutoff_frequency);
   // bw_filter2.setup(samplingrate, 0.05);
         
}
*/

Eigen::Matrix<double,6,1> KalmanFilter_3dof::prediction(const float& dt)
{
    
    // x_k = F_k * x_k-1 + B_k*u_k
    // F << 1,dt,0,1;
    F << 1, dt, 0, 0, 0, 0,
         0, 1, 0, 0, 0, 0,
         0, 0, 1, dt, 0, 0,
         0, 0, 0, 1,0, 0,
         0, 0, 0, 0, 1, dt,
         0, 0, 0, 0, 0, 1;
    // B << 0.5*dt*dt,dt;
    B << 0.5 * dt * dt, 0, 0, 
          dt, 0, 0,
          0, 0.5 * dt * dt, 0,
          0, dt, 0,
          0, 0, 0.5 * dt * dt,
          0, 0, dt;


    x = F*x + B*accel;
    P = F*P*F.transpose() + Q; //Update the covariance matrix P from above (due to the system dynamics)

    return x;
}

Eigen::Matrix<double,6,1> KalmanFilter_3dof::update() //z = SONAR output
{
    
    Eigen::Matrix<double,6,6> identityMatrix = Eigen::Matrix<double,6,6>::Identity();
    Eigen::Matrix<double,6,1> y = residual(); //y = residual error
    K = P*H.transpose() * (H*P*H.transpose()+R).inverse(); //Kalman weighting matrix

    x = x + K*y;
    P =(identityMatrix - K * H) * P;
    return x;
  
}

Eigen::Matrix<double,6,1> KalmanFilter_3dof::update(Eigen::Matrix<double,6,6> external_R) //z = SONAR output
{
    
    Eigen::Matrix<double,6,6> identityMatrix = Eigen::Matrix<double,6,6>::Identity();
    Eigen::Matrix<double,6,1> y = residual(); //y = residual error
    K = P*H.transpose() * (H*P*H.transpose()+external_R).inverse(); //Kalman weighting matrix

    x = x + K*y;
    P =(identityMatrix - K * H) * P;
    return x;
  
}

Eigen::Matrix<double,6,1> KalmanFilter_3dof::residual()
{
   z<<dist(0),vel(0),dist(1),vel(1),dist(2),vel(2);
   return z-H*x; 
  
}

Eigen::Matrix<double,6,1> KalmanFilter_3dof::get_state()
{
   return x; 
}

void KalmanFilter_3dof::set_accel_bias(double bias_surge,double bias_sway,double bias_heave)
{
    
    accel_bias<<bias_surge,bias_sway,bias_heave;

}

Eigen::Vector3d KalmanFilter_3dof::set_accel(double accel_surge,double accel_sway,double accel_heave)
{
    accel<<accel_surge,accel_sway,accel_heave;
    accel=accel-accel_bias;
    accel<<bw_filter_surge.filter(accel(0)),bw_filter_sway.filter(accel(1)),bw_filter_heave.filter(accel(2));
    //accel = (bw_filter.filter((val - accel_bias)));
    return accel;
}

void KalmanFilter_3dof::set_dist_init(double init_surge,double init_sway,double init_heave) //To use tf2 ros to standardize inertial to body frame transformation
{
    bias_reset_dist = true;
    x(0,0) = (init_surge);
    x(2,0) = (init_sway);
    x(4,0) = (init_heave);
    prev_measurement_dist<<init_surge,init_sway,init_heave;
    
} 

Eigen::Vector3d KalmanFilter_3dof::set_dist(double val_surge,double val_sway, double val_heave)
{
    dist<<moving_avg_surge.MovingAvg(val_surge),moving_avg_sway.MovingAvg(val_sway),moving_avg_heave.MovingAvg(val_heave);
    
    return dist;
}

void KalmanFilter_3dof::set_vel(double dt)
{
    
    vel=(-prev_measurement_dist + dist) / dt;
    
}

void KalmanFilter_3dof::set_prev_dist()
{
    prev_measurement_dist = (dist);
}
