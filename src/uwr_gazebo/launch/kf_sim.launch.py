from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import SetParameter
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    return LaunchDescription([
        # applies to every node launched after it, including ones in included files
        SetParameter(name='use_sim_time', value=True),
        IncludeLaunchDescription(PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare('kalman_filter'), 'launch', 'launch_3dof.py']))),
    ])
