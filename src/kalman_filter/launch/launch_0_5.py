from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='kalman_filter',
            executable='kf',
            name='kf',
            output='screen',
            parameters=[
                {'csv_path': '/home/nuc1/Desktop/'},
                {'imu_topic': '/imu/data_raw'},
                {'sonar_topic': '/sonar'},
                {'angle': 0.0},
                {'without_measurement': False},
                {'bias_override': False},
                {'expected_difference':0.5},
            ]
        )
    ])
