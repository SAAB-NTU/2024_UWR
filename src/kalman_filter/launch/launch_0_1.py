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
                {'csv_path': '/home/saab/Desktop/2024_UWR/Analysis/CSVs/case_6thNov_12_05_conf_4_'},
                {'imu_topic': '/imu/data'},
                {'sonar_topic': '/sonar'},
                {'angle': 0.0},
                {'without_measurement': False},
                {'bias_override': True},
                {'expected_difference':0.05},
                {'sample_size':15}
            ]
        )
    ])
#Angle hard coded, since x is correct, y is flipped