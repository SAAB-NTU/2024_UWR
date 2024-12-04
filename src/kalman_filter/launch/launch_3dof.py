from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='kalman_filter',
            executable='kf_3dof',
            name='kf',
            output='screen',
            parameters=[
                {'csv_path': '/home/saab/Desktop/2024_UWR/Analysis/case_1205_t14_'},
                {'imu_topic': '/imu/data'},
                {'sonar_topic': '/sonar'},
                {'angle': 0.0},
                {'without_measurement': False},
                {'bias_override': True},
                {'expected_difference_x':0.01},
                {'expected_difference_y':0.1},
                {'expected_difference_z':0.01},
                {'tolerance_x':80.0},
                {'tolerance_y':80.0},
                {'tolerance_z':80.0},
                {'covar_low_x':0.0001},
                {'covar_low_y':0.0001},
                {'covar_low_z':0.0001},
                {'covar_high_x':100.0},
                {'covar_high_y':1000000.0},
                {'covar_high_z':100.0},
                {'persist_x':20},
                {'persist_y':20},
                {'persist_z':20}

            ]
        )
    ])
