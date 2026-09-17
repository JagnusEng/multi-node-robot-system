from setuptools import find_packages, setup

package_name = 'robot_sensors'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Jean Agnus',
    maintainer_email='jeanagnus457@gmail.com',
    description='Python camera and LiDAR sensor publishers for the ROS 2 multi-node robot system',
    license='MIT',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            "camera_publisher = robot_sensors.camera_publisher:main",
            "lidar_publisher = robot_sensors.lidar_publisher:main"
        ],
    },
)
