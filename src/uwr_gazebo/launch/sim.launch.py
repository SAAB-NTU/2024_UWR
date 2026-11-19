from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import Command, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    world = PathJoinSubstitution([FindPackageShare('uwr_gazebo'), 'worlds', 'tank.sdf'])
    xacro_file = PathJoinSubstitution(
        [FindPackageShare('uwr_description'), 'urdf', 'uwr.urdf.xacro'])
    robot_description = ParameterValue(Command(['xacro ', xacro_file]), value_type=str)
    bridge_config = PathJoinSubstitution([FindPackageShare('uwr_gazebo'), 'config', 'bridge.yaml'])


    # 1. Gazebo itself, via ros_gz_sim's ready-made launch file
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([FindPackageShare('ros_gz_sim'), 'launch', 'gz_sim.launch.py'])),
        launch_arguments={'gz_args': ['-r ', world]}.items())

    # 2. publishes the URDF on /robot_description (and TF), same as Step 5
    rsp = Node(package='robot_state_publisher', executable='robot_state_publisher',
               parameters=[{'robot_description': robot_description, 'use_sim_time': True}])

    # 3. reads /robot_description and creates the robot inside Gazebo
    spawn = Node(package='ros_gz_sim', executable='create', output='screen',
                 arguments=['-topic', 'robot_description', '-name', 'uwr',
                            '-z', '0', '-Y', '1.5708'])
    
    bridge = Node(package='ros_gz_bridge', executable='parameter_bridge', output='screen',
              parameters=[{'config_file': bridge_config, 'use_sim_time': True}])

    return LaunchDescription([gazebo, rsp, spawn, bridge])
