from setuptools import find_packages, setup

package_name = 'sonar_subs'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='uwr',
    maintainer_email='abubakr002@e.ntu.edu.sg',
    description='Basic ROS2 interfacing with AUV sensors',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': ['sonar_reader = sonar_subs.read_sonar:main2','sync_readings=sonar_subs.sync_ros2:main',
        ],
    },
)
