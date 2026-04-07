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
                {'csv_path': '/home/saab/Desktop/2024_UWR/Analysis/SBS_orientations/expt7_not_straight_wall_3_raw-2_'},
                {'imu_topic': '/imu/data'},
                {'sonar_topic': '/sbs'},
                {'angle': 0.0},
                {'without_measurement': False},
                {'bias_override': False},
                {'expected_difference_x':0.1},
                {'expected_difference_y':0.05},
                {'expected_difference_z':0.05},
                {'tolerance_x':80.0},
                {'tolerance_y':80.0},
                {'tolerance_z':80.0},
                {'covar_low_x':10.0}, #0.01,0.001,0.0001
                {'covar_low_y':10.0}, #0.01,0.001,0.0001
                {'covar_low_z':10.0}, #0.01,0.001,0.0001
                {'covar_high_x':1000000.0},
                {'covar_high_y':1000000.0},
                {'covar_high_z':1000000.0},
                {'persist_x':20}, #10,20,30
                {'persist_y':20}, #10,20,30
                {'persist_z':20}, #10,20,30
                {'discard_x':False},
                {'discard_y':False},
                {'discard_z':False}

            ]
        )
    ])
