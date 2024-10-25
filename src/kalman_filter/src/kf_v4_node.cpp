#include <rclcpp/rclcpp.hpp>

#include "../include/sonar_processing.h"  // Custom header (make sure the path is correct)
#include "../include/kalman_filter.h"     // Custom header (make sure the path is correct)
#include "../include/bag_processing.h"    // Custom header (ROS2 does not have native rosbag API yet, so ensure compatibility)

// ROS2 message headers
#include "sonar_msgs/msg/three_sonar_depth.hpp"   // Replace with ROS2 message types, ensure these are available in your ROS2 package
#include <sonar_msgs/msg/conf_scal.hpp>
#include <sonar_msgs/msg/kf_values.hpp>

// ROS2 sensor messages
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <sensor_msgs/msg/nav_sat_status.hpp>

// TF2 for ROS2
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

// Geometry messages
#include <geometry_msgs/msg/vector3_stamped.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

// Eigen3 library for linear algebra
#include <eigen3/Eigen/Dense>

// Standard library headers
#include <string>
#include <fstream>
#include <cmath>

// ROS2 transform broadcaster and listener
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>

// IIR filter library
#include "Iir.h"

// Standard ROS2 message types
#include <std_msgs/msg/float64.hpp>

//Rosbag2 header files

#include <rosbag2_cpp/writer.hpp>
#include <rosbag2_storage/storage_options.hpp>
#include <rosbag2_cpp/writers/sequential_writer.hpp>


//rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr scalar_pub;
//rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_transform;



class kf_node : public rclcpp::Node
{
public:
    kf_node():Node("kf_node")
    {
        // Initialize publishers
        pose_pub = this->create_publisher<geometry_msgs::msg::PoseStamped>("pose_topic", 10);
        confidence_pub = this->create_publisher<sonar_msgs::msg::ConfScal>("confidence_topic", 10);
        k_vals_pub = this->create_publisher<sonar_msgs::msg::KfValues>("k_vals_topic", 10);

        // Initialize other ROS-related variables
        current_time = this->now();
        predict_time = this->now();
        measure_time = this->now();

        this->declare_parameter<std::string>("csv_path", "default_path.csv");
        this->get_parameter("csv_path", path_param);

        this->declare_parameter<std::string>("imu_topic", "/imu/acceleration");
        this->declare_parameter<std::string>("sonar_topic", "/sonar");
        this->declare_parameter<double>("angle", 0.0);
        this->declare_parameter<bool>("without_measurement", true);
        this->declare_parameter<bool>("bias_override", true);

        // Get parameters
        this->get_parameter("imu_topic", imu_param);
        this->get_parameter("sonar_topic", sonar_param);
        this->get_parameter("angle", angle);
        this->get_parameter("without_measurement", start);
        this->get_parameter("bias_override", override);

        angle_rad=angle*M_PI/180;

        rot_matrix<<cos(angle_rad),-sin((angle_rad)),0,sin((angle_rad)),cos((angle_rad)),0,0,0,1;


        sample_size = 10; // Define the sample size here

    // Initialize Kalman filter with the sample size
        surge = kf_v4(sample_size);
        sway = kf_v4(sample_size);
        heave = kf_v4(sample_size);
	RCLCPP_INFO(this->get_logger(), "%s", sonar_param.c_str());


        imu_subscriber_ = this->create_subscription<geometry_msgs::msg::Vector3Stamped>(
        imu_param, 1, std::bind(&kf_node::imu_callback2, this, std::placeholders::_1));
	//imu_subscriber_ = this->create_subscription<sensor_msgs::msg::Imu>(
        //imu_param, 1, std::bind(&kf_node::imu_callback, this, std::placeholders::_1));
       // sonar_subscriber_ = this->create_subscription<sonar_msgs::msg::ThreeSonarDepth>(
       // sonar_param, 1, std::bind(&kf_node::sonar_callback, this, std::placeholders::_1));
	
	sonar_subscriber_ = this->create_subscription<sonar_msgs::msg::ThreeSonarDepth>(
       sonar_param, 1, std::bind(&kf_node::sonar_callback2, this, std::placeholders::_1));

	
        // Create a bag file name using the bag_create_file function
        std::string bag_file_name = bag_create_file(path_param, this->now());

        // Set up the storage options for rosbag2
        storage_options_.uri = bag_file_name;  // The name of the bag file
        storage_options_.storage_id = "sqlite3"; // Backend storage type (e.g., SQLite)

        // Set up the converter options for rosbag2
        converter_options_.input_serialization_format = "cdr";
        converter_options_.output_serialization_format = "cdr";

        // Initialize the rosbag writer
        writer_ = std::make_shared<rosbag2_cpp::Writer>();
        writer_->open(storage_options_, converter_options_);

        expected_difference=0.05;

        RCLCPP_INFO(this->get_logger(), "Class successfully constructed, waiting for data");
        
        slope=(1-1000)/(100-0);
        intercept=1000;

    }

   void sonar_callback2(const sonar_msgs::msg::ThreeSonarDepth& msg)
{
    RCLCPP_INFO(this->get_logger(), "Callback triggered!");
    bias=false;
}

    void imu_callback2(const geometry_msgs::msg::Vector3Stamped& imu_msg) 
    
    {
        
        
        try {
        bef_rotate<<(imu_msg.vector.x),(imu_msg.vector.y),1;
        aft_rotate=rot_matrix*bef_rotate;
        predict_time_now = this->now();
        // if(!rot_bias)
        // {
        //     tf2::convert(imu_msg.orientation, q_orig);
        //     //tf2::convert(imu_msg.orientation, world_to_inertial_transform.transform.rotation);
        //     //world_to_inertial_transform.transform.rotation=tf2::toMsg(q_orig);
        //     //transformStamped.transform.rotation=tf2::toMsg(q_orig);
        //     //ROS_INFO("w: %f",transformStamped.transform.rotation.w);
        //     rot_bias=true;
        // }
        

        if (start) {
             //RCLCPP_INFO(this->get_logger(),"Hi");
            surge_accel = surge.set_accel(aft_rotate(0));
            sway_accel = sway.set_accel(aft_rotate(1));
            heave_accel = heave.set_accel(imu_msg.vector.z);
            surge.set_jerk((predict_time_now - predict_time).seconds());
            sway.set_jerk((predict_time_now - predict_time).seconds());
            heave.set_jerk((predict_time_now - predict_time).seconds());
            surge_state_p = surge.prediction((predict_time_now - predict_time).seconds());
            sway_state_p = sway.prediction((predict_time_now - predict_time).seconds());
            heave_state_p = heave.prediction((predict_time_now - predict_time).seconds());
            predict_time = predict_time_now;

            geometry_msgs::msg::Vector3Stamped vector3_msg, vel_msg;
            geometry_msgs::msg::PoseStamped pose_msg;

            vector3_msg.header.stamp = imu_msg.header.stamp;
            vector3_msg.vector.x = surge_accel;
            vector3_msg.vector.y = sway_accel;
            vector3_msg.vector.z = heave_accel;

            vel_msg.header.stamp = imu_msg.header.stamp;
            vel_msg.vector.x = surge_state_p(1);
            vel_msg.vector.y = sway_state_p(1);
            vel_msg.vector.z = heave_state_p(1);

            pose_msg.header.stamp = imu_msg.header.stamp;
            pose_msg.pose.position.x = surge_state_p(0);
            pose_msg.pose.position.y = sway_state_p(0);
            pose_msg.pose.position.z = heave_state_p(0);
            //tf2::convert(imu_msg.orientation, q_new);
            pose_msg.pose.orientation = tf2::toMsg(q_new * q_orig);

            //transformStamped.header.stamp = imu_msg.header.stamp;
            //transformStamped.transform.translation.x = surge_state_p(0);
            // transformStamped.transform.translation.y = sway_state_p(0);
           // transformStamped.transform.translation.z = heave_state_p(0);
           // transformStamped.transform.rotation = tf2::toMsg(q_new);

            writer_->write(imu_msg, "IMU_raw", predict_time_now);
            writer_->write(vector3_msg, "IMU_filtered", predict_time_now);
            writer_->write(vel_msg, "IMU_vel", predict_time_now);
            writer_->write(pose_msg, "Pose", predict_time_now);
            //tf2::doTransform(transformStamped, world_to_inertial_transform, transformStamped);
            /*

            */
            //writer_->write(transformStamped, "Transform", "std_msgs/msg/String", time_stamp);

            //bag.write("IMU_raw", predict_time_now, imu_msg);
            //bag.write("IMU_filtered", predict_time_now, vector3_msg);
            //bag.write("IMU_vel", predict_time_now, vel_msg);
            //bag.write("Pose", predict_time_now, pose_msg);
            //bag.write("Transform",predict_time_now,transformStamped);
            
           
            pose_pub->publish(pose_msg);
            //pub_transform->publish(transformStamped);
       
                 if (!bias) {

            surge.set_accel_bias(true, aft_rotate(0));
            sway.set_accel_bias(true, aft_rotate(1));
            heave.set_accel_bias(true, imu_msg.vector.z);
            
            bias = true;
        }
        }
    } catch (const std::exception& e) {
        RCLCPP_ERROR(this->get_logger(), "error in imu-callback: %s", e.what());
    }
        

        }
    void imu_callback(const sensor_msgs::msg::Imu& imu_msg) 
    
    {
        
        
        try {
        bef_rotate<<(imu_msg.linear_acceleration.x),(imu_msg.linear_acceleration.y),1;
        aft_rotate=rot_matrix*bef_rotate;
        predict_time_now = this->now();
        // if(!rot_bias)
        // {
        //     tf2::convert(imu_msg.orientation, q_orig);
        //     //tf2::convert(imu_msg.orientation, world_to_inertial_transform.transform.rotation);
        //     //world_to_inertial_transform.transform.rotation=tf2::toMsg(q_orig);
        //     //transformStamped.transform.rotation=tf2::toMsg(q_orig);
        //     //ROS_INFO("w: %f",transformStamped.transform.rotation.w);
        //     rot_bias=true;
        // }
        

        if (start) {
             RCLCPP_INFO(this->get_logger(),"Hi");
            surge_accel = surge.set_accel(aft_rotate(0));
            sway_accel = sway.set_accel(aft_rotate(1));
            heave_accel = heave.set_accel(imu_msg.linear_acceleration.z);
            
           //surge.set_jerk((predict_time_now - predict_time).seconds());
            //sway.set_jerk((predict_time_now - predict_time).seconds());
            //heave.set_jerk((predict_time_now - predict_time).seconds());
            surge_state_p = surge.prediction((predict_time_now - predict_time).seconds());
            sway_state_p = sway.prediction((predict_time_now - predict_time).seconds());
            heave_state_p = heave.prediction((predict_time_now - predict_time).seconds());
            predict_time = predict_time_now;

            geometry_msgs::msg::Vector3Stamped vector3_msg, vel_msg;
            geometry_msgs::msg::PoseStamped pose_msg;

            vector3_msg.header.stamp = imu_msg.header.stamp;
            vector3_msg.vector.x = surge_accel;
            vector3_msg.vector.y = sway_accel;
            vector3_msg.vector.z = heave_accel;

            vel_msg.header.stamp = imu_msg.header.stamp;
            vel_msg.vector.x = surge_state_p(1);
            vel_msg.vector.y = sway_state_p(1);
            vel_msg.vector.z = heave_state_p(1);

            pose_msg.header.stamp = imu_msg.header.stamp;
            pose_msg.pose.position.x = surge_state_p(0);
            pose_msg.pose.position.y = sway_state_p(0);
            pose_msg.pose.position.z = heave_state_p(0);
            //tf2::convert(imu_msg.orientation, q_new);
            pose_msg.pose.orientation = tf2::toMsg(q_new * q_orig);

            //transformStamped.header.stamp = imu_msg.header.stamp;
            //transformStamped.transform.translation.x = surge_state_p(0);
            // transformStamped.transform.translation.y = sway_state_p(0);
           // transformStamped.transform.translation.z = heave_state_p(0);
           // transformStamped.transform.rotation = tf2::toMsg(q_new);

            writer_->write(imu_msg, "IMU_raw", predict_time_now);
            writer_->write(vector3_msg, "IMU_filtered", predict_time_now);
            writer_->write(vel_msg, "IMU_vel", predict_time_now);
            writer_->write(pose_msg, "Pose", predict_time_now);
            //tf2::doTransform(transformStamped, world_to_inertial_transform, transformStamped);
            /*

            */
            //writer_->write(transformStamped, "Transform", "std_msgs/msg/String", time_stamp);

            //bag.write("IMU_raw", predict_time_now, imu_msg);
            //bag.write("IMU_filtered", predict_time_now, vector3_msg);
            //bag.write("IMU_vel", predict_time_now, vel_msg);
            //bag.write("Pose", predict_time_now, pose_msg);
            //bag.write("Transform",predict_time_now,transformStamped);
            
           
           pose_pub->publish(pose_msg);
            //pub_transform->publish(transformStamped);
       
                 if (!bias) {

            surge.set_accel_bias(true, aft_rotate(0));
            sway.set_accel_bias(true, aft_rotate(1));
            heave.set_accel_bias(true, imu_msg.linear_acceleration.z);
            
            bias = true;
        }
        }
    } catch (const std::exception& e) {
        RCLCPP_ERROR(this->get_logger(), "error in imu-callback: %s", e.what());
    }
        

        }

    void sonar_callback(const sonar_msgs::msg::ThreeSonarDepth& msg) 
    
    {
        //static tf2_ros::Buffer tfBuffer;
    //static tf2_ros::TransformBroadcaster tf_broadcaster;
    //static tf2_ros::StaticTransformBroadcaster static_broadcaster;
   

    
    try {
        //RCLCPP_INFO(this->get_logger(),"%s",start.c_str());
        measure_time_now = this->now();
        //surge.set_dist(msg.distance_1 / 1000);
        //heave.set_dist(msg.depth);
        //sway.set_dist(msg.distance_2 / 1000);
        //if (!start && rot_bias) {
        if (!start) 
        {
        surge.set_dist_init(msg.distance_1/ 1000);
        sway.set_dist_init(msg.distance_2 /1000);
        heave.set_dist_init(msg.depth / 1000);
            // /*if (msg.confidence_1 == 100.0) {
            //     //surge.set_dist_init(msg.distance_1 / 1000);
            //     world_to_inertial_transform.transform.translation.x = msg.distance_1 / 1000;
                
    
            // }
            // if (msg.confidence_2 == 100.0) {
            //     //sway.set_dist_init(msg.distance_2 / 1000);
            //     world_to_inertial_transform.transform.translation.y = msg.distance_2 / 1000;
            // } */
            // //heave.set_dist_init(msg.depth);
            // //world_to_inertial_transform.transform.translation.z = msg.depth;
            // //ROS_INFO("Child: %s", world_to_inertial_transform.child_frame_id.c_str());
            // //world_to_inertial_transform.header.stamp=measure_time_now;
            // //transformStamped.header.stamp=measure_time_now;
            
            // //tf_broadcaster.sendTransform(transformStamped);
            // //static_broadcaster.sendTransform(world_to_inertial_transform);
            measure_time = measure_time_now;
            predict_time = measure_time_now;
            start = true;
            RCLCPP_INFO(this->get_logger(), "%f",msg.distance_2/1000);
            RCLCPP_INFO(this->get_logger(), "%f",sway.get_state()(0));
            RCLCPP_INFO(this->get_logger(), "Measurements started");
        } else {

            //sbs_frame_before.transform.translation.x = msg.distance_1 / 1000;
            //sbs_frame_before.transform.translation.y = msg.distance_2 / 1000;
            //sbs_frame_before.transform.translation.z = msg.depth;

            //tf2::doTransform(sbs_frame_before,world_to_inertial_transform,sbs_frame_after);

            //sbs_frame_after.header=msg.header;
            
            //surge_dist=sbs_frame_after.transform.translation.x;
            //sway_dist=sbs_frame_after.transform.translation.y;
            //heave_dist=sbs_frame_after.transform.translation.z;
            surge_dist = surge.set_dist(msg.distance_1 / 1000);
            sway_dist = sway.set_dist(msg.distance_2 / 1000);
            heave_dist = heave.set_dist(msg.depth);
            diff_surge = surge.residual();
            diff_sway = sway.residual();
            diff_heave = heave.residual();

          //  RCLCPP_INFO(this->get_logger(),"Before: %f", sbs_frame_before.transform.translation.x);


            //ROS_INFO("Sigmas Away: %f", surge.moving_avg.debug.first);
            //ROS_INFO("Adjusted Std: %f", surge.moving_avg.debug.second);
            /*Update moving average and confidence levels
            double raw_measurement = msg.distance_1 / 1000; // Example using distance_1, apply similarly for others
            surge.moving_avg.MovingAvg(raw_measurement);
            double confidence = surge.moving_avg.output.first;
            double scalar = surge.moving_avg.output.second;

            ROS_INFO("Confidence: %f", confidence);
            ROS_INFO("Scalar: %f", scalar);

            std_msgs::Float64 confidence_msg;
            std_msgs::Float64 scalar_msg;

            confidence_msg.data = confidence;
            scalar_msg.data = scalar;

            confidence_pub->publish(confidence_msg);
            scalar_pub->publish(scalar_msg);*/
            
            auto e1=surge.moving_avg.CalculateConfidenceLevelsVariation2(expected_difference);
            auto e2=sway.moving_avg.CalculateConfidenceLevelsVariation2(expected_difference);
            auto e3=heave.moving_avg.CalculateConfidenceLevelsVariation2(expected_difference);
            c1.header.stamp = msg.header.stamp;
            c1.confidence_1 = e1.first;
            c1.scalar_1 = e1.second;
            c1.confidence_2 = e2.first;
            c1.scalar_2 = e2.second;
            c1.confidence_3 = e3.first;
            c1.scalar_3 = e3.second;
            
            
            
            covar_surge=slope*e1.first+intercept;
            covar_sway=slope*e2.first+intercept;
            covar_heave=slope*e3.first+intercept;
            
            surge_R<<covar_surge,0,0,0,covar_surge,0,0,0,0;
            sway_R<<covar_sway,0,0,0,covar_sway,0,0,0,0;
            heave_R<<covar_heave,0,0,0,covar_heave,0,0,0,0;
            
            
        //     if (e1.first> 90) {
        //         surge.set_vel((measure_time_now - measure_time).seconds());
        //         //surge_state_u = surge.update();
        //         surge_state_u = surge.update(surge_R);
        //         if(override==true)
        //         {bias=false;}
                
        //     } else {
        //         RCLCPP_INFO(this->get_logger(),"Deviate_x");
        //         surge_state_u = surge.get_state();
                
        //     }
        //         //Change < to >, 0.4 to 0.1 perhaps, avoid the use of m2 
        //     if (e2.first>90) {
        //         sway.set_vel((measure_time_now - measure_time).seconds());
        //         //sway_state_u = sway.update();
        //         sway_state_u = sway.update(sway_R);
        //         //m2=measure_time_now;
        //    } else {
        //         //RCLCPP_INFO(this->get_logger(),"Deviate");
        //         sway_state_u = sway.get_state();
        //     }

        //     if (e3.first>50) {
        //         heave.set_vel((measure_time_now - measure_time).seconds());
        //         //heave_state_u = heave.update();
        //         heave_state_u = heave.update(heave_R);
        //     } else {
        //         heave_state_u = heave.get_state();
        //     } 

                surge.set_vel((measure_time_now - measure_time).seconds());
                surge_state_u = surge.update();
                //surge_state_u = surge.update(surge_R);
            if (e1.first> 90) {

                if(override==true)
                {bias=false;}
                
            } else {
                RCLCPP_INFO(this->get_logger(),"Deviate_x");
                //surge_state_u = surge.get_state();
                
            }
            //sway.set_vel((measure_time_now - measure_time).seconds());
                //sway_state_u = sway.update();
                //sway_state_u = sway.update(sway_R);
                //Change < to >, 0.4 to 0.1 perhaps, avoid the use of m2 
            if (e2.first>70) {
                RCLCPP_INFO(this->get_logger(),"Taken_y");
                //m2=measure_time_now;
           } else {
                //RCLCPP_INFO(this->get_logger(),"Deviate");
                RCLCPP_INFO(this->get_logger(),"Deviate_y");
                sway_state_u = sway.get_state();
            }

                heave.set_vel((measure_time_now - measure_time).seconds());
                heave_state_u = heave.update();
                //heave_state_u = heave.update(heave_R);

            //if (e3.first>50) {

            //} else {
                //heave_state_u = heave.get_state();
            //} 

            k_vals.header.stamp= msg.header.stamp;
            k_vals.k_d_1=surge.K(0,0);
            k_vals.k_v_1=surge.K(1,1);
            k_vals.k_d_2=sway.K(0,0);
            k_vals.k_v_2=sway.K(1,1);
            k_vals.k_d_3=heave.K(0,0);    
            k_vals.k_v_3=heave.K(1,1);

            //e1=std::abs(1-(std::abs(diff_surge))/0.1);
            //e2=std::abs(1-(std::abs(diff_sway))/0.1);
            //e3=std::abs(1-(std::abs(diff_heave))/0.1);


            //RCLCPP_INFO(this->get_logger(),"R_sway %f", covar_sway);
            //ROS_INFO("Scalar: %f", surge.moving_avg.output.second);
            RCLCPP_INFO(this->get_logger(),"Distance: %f", sway_state_u(0));
            //RCLCPP_INFO(this->get_logger(),"Timestamp: %f",(measure_time_now - measure_time).seconds());
            geometry_msgs::msg::PoseStamped pose_msg;
            pose_msg.header.stamp = msg.header.stamp;
            pose_msg.pose.position.x = surge_state_u(0);
            pose_msg.pose.position.y = sway_state_u(0);
            pose_msg.pose.position.z = heave_state_u(0);
            pose_msg.pose.orientation = tf2::toMsg(q_new * q_orig);
            measure_time=measure_time_now;

            geometry_msgs::msg::Vector3Stamped vector3_msg, vel_msg;
            vector3_msg.header.stamp = msg.header.stamp;
            vector3_msg.vector.x = surge_dist;
            vector3_msg.vector.y = sway_dist;
            vector3_msg.vector.z = heave_dist;

            //tf2::doTransform(transformStamped, world_to_inertial_transform, transformStamped);

            //transformStamped.header.stamp=msg.header.stamp;
            //transformStamped.transform.translation.x = surge_state_u(0);
            //transformStamped.transform.translation.y = sway_state_u(0);
            //transformStamped.transform.translation.z = heave_state_u(0);

            vel_msg.header.stamp = msg.header.stamp;
            vel_msg.vector.x = surge_state_u(1);
            vel_msg.vector.y = sway_state_u(1);
            vel_msg.vector.z = heave_state_u(1);

            writer_->write(vector3_msg,"SONAR_filtered", measure_time_now);
            writer_->write(vel_msg,"SONAR_vel", measure_time_now);
            writer_->write(msg,"SONAR_raw", measure_time_now);
            writer_->write(pose_msg, "Pose",measure_time_now);
            writer_->write(c1,"Confidence_SONAR",measure_time_now);
            writer_->write(k_vals,"K_values",measure_time_now);


            /*

            //writer_->write("Transform", measure_time_now, transformStamped);

            writer_->write("Confidence_SONAR",measure_time_now,c1);
            writer_->write("K_values",measure_time_now,k_vals);
            */


            pose_pub->publish(pose_msg);
            confidence_pub->publish(c1);

        
            //pub_transform->publish(transformStamped);

            k_vals_pub->publish(k_vals);
            measure_time = measure_time_now;
            surge.set_prev_dist();
            sway.set_prev_dist();
            heave.set_prev_dist();
            
        }
    } catch (const std::exception& e) {
        RCLCPP_ERROR(this->get_logger(), "error in sonar-callback: %s", e.what());
    }
    
        }


private:
    // ROS-related variables
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pose_pub;
    rclcpp::Publisher<sonar_msgs::msg::ConfScal>::SharedPtr confidence_pub;
    rclcpp::Publisher<sonar_msgs::msg::KfValues>::SharedPtr k_vals_pub;

    rclcpp::Subscription<sonar_msgs::msg::ThreeSonarDepth>::SharedPtr sonar_subscriber_;
    rclcpp::Subscription<geometry_msgs::msg::Vector3Stamped>::SharedPtr imu_subscriber_;
    //rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscriber_;

    int sample_size;
    double expected_difference;
    
    rclcpp::Time current_time;
    rclcpp::Time predict_time, measure_time,predict_time_now,measure_time_now;

    //Rosbag 2 variables
    rosbag2_storage::StorageOptions storage_options_;
    rosbag2_cpp::ConverterOptions converter_options_;
    std::shared_ptr<rosbag2_cpp::Writer> writer_;
    std::string path_param,imu_param,sonar_param;

    sonar_msgs::msg::ConfScal c1;



    double surge_dist, sway_dist, heave_dist, diff_surge, diff_sway, diff_heave,angle,angle_rad;
    bool bias = false, start = false,rot_bias=false,override=false,flag1,flag2;




    double surge_accel, sway_accel, heave_accel;
    
    double covar_surge,covar_sway,covar_heave,slope,intercept;
    Eigen::Matrix3f surge_R, sway_R, heave_R;
    
    tf2::Quaternion q_orig, q_new;

    kf_v4 surge, sway, heave;

    Eigen::Vector3f surge_state_p, sway_state_p, heave_state_p;
    Eigen::Vector3f surge_state_u, sway_state_u, heave_state_u;
    Eigen::Vector3f bef_rotate,aft_rotate;
    Eigen::Matrix3f rot_matrix;
	
    sonar_msgs::msg::KfValues k_vals;

    //geometry_msgs::TransformStamped transformStamped, sbs_frame_before,sbs_frame_after;
    //geometry_msgs::TransformStamped world_to_inertial_transform;


};



int main(int argc, char* argv[]) {

    rclcpp::init(argc, argv);
    auto node = std::make_shared<kf_node>();

    // Subscribing to a topic in the main function


    rclcpp::spin(node);
    rclcpp::shutdown();
 
    
    //transformStamped.header.frame_id = "kf_frame";  // Parent frame (fixed frame)
    //transformStamped.child_frame_id = "kf_frame";    // Child frame (frame to be moved)
    //sbs_frame_before.header.frame_id = "sbs_frame";  // Parent frame (fixed frame)
    //sbs_frame_before.child_frame_id = "sbs_frame";    // Child frame (frame to be moved)
    
    //world_to_inertial_transform.header.stamp = ros::Time::now();
    //world_to_inertial_transform.header.frame_id = "inertial_frame";       // Parent frame (world frame)
    //world_to_inertial_transform.child_frame_id = "kf_frame";    // Child frame (inertial frame)


    return 0;
}




