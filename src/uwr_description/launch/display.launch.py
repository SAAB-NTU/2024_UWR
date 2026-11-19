from launch import LaunchDescription
from launch.substitutions import Command, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    xacro_file = PathJoinSubstitution(
        [FindPackageShare('uwr_description'), 'urdf', 'uwr.urdf.xacro'])
    rviz_config = PathJoinSubstitution(
        [FindPackageShare('uwr_description'), 'rviz', 'uwr.rviz'])

    # run xacro at launch time and pass the resulting URDF text as a parameter
    robot_description = ParameterValue(Command(['xacro ', xacro_file]), value_type=str)

    return LaunchDescription([
        Node(package='robot_state_publisher', executable='robot_state_publisher',
             parameters=[{'robot_description': robot_description}]),
        Node(package='rviz2', executable='rviz2', arguments=['-d', rviz_config]),
    ])
