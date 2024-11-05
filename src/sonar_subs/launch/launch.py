from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='adnav-driver',
            executable='adnav_driver',
            name='adnav_driver_node',
            output='screen',
            arguments=['115200', '/dev/ttyUSB0']
        ),
        Node(
            package='sonar_subs',
            executable='imu',
            name='imu_node',
            output='screen'
        ),
    ])
