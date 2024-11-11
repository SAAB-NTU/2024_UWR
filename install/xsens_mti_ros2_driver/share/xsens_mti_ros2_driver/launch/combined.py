from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    return LaunchDescription([
        # Declare the arguments you want to pass to the launch files
        DeclareLaunchArgument('initial_reset', default_value='true'),
        DeclareLaunchArgument('enable_depth', default_value='false'),
        DeclareLaunchArgument('rgb_camera_color_profile', default_value='960,540,60'),
        
      # Launch the realsense2_camera node
        Node(
            package='realsense2_camera',
            executable='realsense2_camera_node',
            name='realsense2_camera',
            output='screen',
            parameters=[{
                'initial_reset': LaunchConfiguration('initial_reset'),
                'enable_depth': LaunchConfiguration('enable_depth'),
                'rgb_camera.color_profile': LaunchConfiguration('rgb_camera_color_profile')
            }]
        ),
        # Launch the xsens_mti_ros2_driver node
        Node(
            package='xsens_mti_ros2_driver',
            executable='xsens_mti_node',
            name='xsens_mti',
            output='screen'
        ),
        
                Node(
            package='sonar_subs',
            executable='sonar_reader',
            name='sbs',
            output='screen'
        ),
    ])
    
    

