from setuptools import find_packages
from setuptools import setup

setup(
    name='sonar_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('sonar_msgs', 'sonar_msgs.*')),
)
