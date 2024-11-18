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
                {'csv_path': '/home/saab/Desktop/2024_UWR/Analysis/CSVs/case_13thNov_13_07_normal_'},
                {'imu_topic': '/imu/data_raw'},
                {'sonar_topic': '/sonar'},
                {'angle': 0.0},
                {'without_measurement': False},
                {'bias_override': True},
                {'expected_difference':0.1},
            ]
        )
    ])
#Angle hard coded, since x is correct, y is flipped