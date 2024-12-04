from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='kalman_filter',
            executable='imu_topic',
            name='imu',
            output='screen',
            parameters=[
                {'imu_topic_1': '/lcimu/data'},
                #{'imu_topic_1': '/camera/realsense2_camera/accel/sample'},
                #{'imu_topic_2': '/camera/realsense2_camera/gyro/sample'},
                {'imu_topics': 1}
            ]
        )
    ])
#Angle hard coded, since x is correct, y is flipped