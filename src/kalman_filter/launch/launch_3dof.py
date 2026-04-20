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
                {'csv_path': '/home/saab/2024_UWR/Analysis/2026_article/Stepper_not_aligned/Condition_1_'},
                {'imu_topic': '/imu/data'},
                {'sonar_topic': '/sonar'},
                {'angle': 0.0},
                {'without_measurement': False},
                {'bias_override': True},
                {'expected_difference_x':0.1},
                {'expected_difference_y':0.1},
                {'expected_difference_z':0.1},
                {'tolerance_x':50.0},
                {'tolerance_y':50.0},
                {'tolerance_z':50.0},
                {'covar_low_x':1.0}, #0.01,0.001,0.0001
                {'covar_low_y':1.0}, #0.01,0.001,0.0001
                {'covar_low_z':1.0}, #0.01,0.001,0.0001
                {'covar_high_x':10000000.0},
                {'covar_high_y':10000000.0},
                {'covar_high_z':10000000.0},
                {'persist_x':40}, #10,20,30
                {'persist_y':40}, #10,20,30
                {'persist_z':40}, #10,20,30
                {'discard_x':False},
                {'discard_y':False},
                {'discard_z':False}

            ]
        )
    ])
