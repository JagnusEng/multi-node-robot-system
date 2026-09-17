from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    camera_node = Node(
        package = "robot_sensors",
        executable = "camera_publisher",
        name = "camera_publisher")

    lidar_node = Node(
        package = "robot_sensors",
        executable = "lidar_publisher",
        name = "lidar_publisher")

    odometry_node = Node(
        package = "robot_localization",
        executable = "odometry_publisher",
        name = "odometry_publisher")

    static_tf_node = Node(
            package = "robot_localization",
            executable = "static_tf_publisher",
            name = "static_tf_publisher")

    return LaunchDescription([
        camera_node,
        lidar_node,
        odometry_node,
        static_tf_node
    ])


    