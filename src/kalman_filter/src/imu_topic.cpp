#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/synchronizer.h>

class imu_node : public rclcpp::Node
{
public:
    imu_node() : Node("imu_node")
    {
        // Initialize publishers
        pose_pub = this->create_publisher<sensor_msgs::msg::Imu>("/imu/data_raw", 10);

        // Declare parameters
        this->declare_parameter<std::string>("imu_topic_1", "/lcimu/data");
        this->declare_parameter<std::string>("imu_topic_2", "/camera/realsense2_camera/gyro/sample");
        this->declare_parameter<int>("imu_topics", 1);

        // Get parameters
        this->get_parameter("imu_topic_1", imu_param_1);
        this->get_parameter("imu_topic_2", imu_param_2);
        this->get_parameter("imu_topics", imu_topics);

        // Choose behavior based on imu_topics
        if (imu_topics == 1)
        {
            lcimu_subscriber = this->create_subscription<sensor_msgs::msg::Imu>(
                imu_param_1, 1, std::bind(&imu_node::imu_callback, this, std::placeholders::_1));
        }
        else if (imu_topics == 2)
        {
            accel_sub_.subscribe(this, imu_param_1);
            gyro_sub_.subscribe(this, imu_param_2);
            sync_ = std::make_shared<message_filters::Synchronizer<SyncPolicy>>(SyncPolicy(10), accel_sub_, gyro_sub_);
            sync_->registerCallback(std::bind(&imu_node::sync_callback, this, std::placeholders::_1, std::placeholders::_2));
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Invalid value for imu_topics. Must be 1 or 2.");
            rclcpp::shutdown();
        }

        RCLCPP_INFO(this->get_logger(), "Class successfully constructed, waiting for %d topic(s)",imu_topics);
    }

private:
    void sync_callback(const sensor_msgs::msg::Imu::ConstSharedPtr & accel_msg,
                       const sensor_msgs::msg::Imu::ConstSharedPtr & gyro_msg)
    {
        auto imu_msg = sensor_msgs::msg::Imu();
        imu_msg.header.stamp = accel_msg->header.stamp;
        imu_msg.header.frame_id = "imu_combined_frame";

        imu_msg.linear_acceleration = accel_msg->linear_acceleration;
        imu_msg.angular_velocity = gyro_msg->angular_velocity;

        pose_pub->publish(imu_msg);
    }

    void imu_callback(const sensor_msgs::msg::Imu::SharedPtr imu_msg)
    {
        try
        {
            pose_pub->publish(*imu_msg);
        }
        catch (const std::exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "Error in imu_callback: %s", e.what());
        }
    }

    // ROS-related variables
    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr pose_pub;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr lcimu_subscriber;

    message_filters::Subscriber<sensor_msgs::msg::Imu> accel_sub_;
    message_filters::Subscriber<sensor_msgs::msg::Imu> gyro_sub_;


    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::msg::Imu, sensor_msgs::msg::Imu> SyncPolicy;
    std::shared_ptr<message_filters::Synchronizer<SyncPolicy>> sync_;

    // Parameters
    std::string imu_param_1, imu_param_2;
    int imu_topics;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<imu_node>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
