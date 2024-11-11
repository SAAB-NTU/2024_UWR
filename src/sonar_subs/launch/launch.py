from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
     
        Node(
            package='sonar_subs',
            executable='imu_i2c',
            name='imu_node',
            output='screen'
        ),
           Node(
            package='sonar_subs',
            executable='sonar_reader',
            name='sonar_node',
            output='screen'
        ),
    ])
