Multi-Node Robot System

A ROS 2 Humble skills-demonstration project that simulates a small multi-node robotic software system using C++ and Python. The project demonstrates ROS 2 package organization, sensor publishing, odometry, TF2 coordinate-frame management, launch files, QoS configuration, automated testing, and command-line debugging. It is a portfolio project designed to demonstrate robotics software engineering fundamentals rather than control a physical robot.
Architecture Overview

The workspace is divided into three ROS 2 packages:

    robot_sensors — Python package responsible for simulated camera and LiDAR sensor publishers.

    robot_localization — C++ package responsible for odometry publishing and TF2 transform broadcasting.

    robot_bringup — Launch package responsible for starting the complete multi-node system from a single launch file.

The system launches four primary nodes:

camera_publisher
lidar_publisher
odometry_publisher
static_tf_publisher

System Architecture

                    robot_bringup
                         |
                         |
          robot_system.launch.py
                         |
          +--------------+--------------+
          |              |              |
          v              v              v
   robot_sensors   robot_localization   TF2
          |              |
     +----+----+     +----+----+
     |         |     |         |
     v         v     v         v
   Camera    LiDAR  Odometry  Transforms
     |         |      |
     v         v      v
/camera/     /scan   /odom
image_raw

TF Tree

The system maintains the following coordinate-frame hierarchy:

map
 |
 | static
 v
odom
 |
 | dynamic
 v
base_link
 |\
 | \
 |  +----------> camera_link
 |
 +-------------> lidar_link

Transform responsibilities:

    map -> odom — static identity transform for this simulated system.

    odom -> base_link — dynamic transform generated from simulated odometry.

    base_link -> camera_link — static camera mounting transform.

    base_link -> lidar_link — static LiDAR mounting transform.

The TF tree can also be inspected using:

ros2 run tf2_tools view_frames

or:

ros2 run tf2_ros tf2_echo map lidar_link

Topics
Topic	Message Type	Publisher	Purpose
/camera/image_raw	sensor_msgs/msg/Image	camera_publisher	Simulated RGB camera images
/scan	sensor_msgs/msg/LaserScan	lidar_publisher	Simulated LiDAR scans
/odom	nav_msgs/msg/Odometry	odometry_publisher	Simulated robot odometry
/tf	TF2 transforms	odometry_publisher	Dynamic odom -> base_link transform
/tf_static	TF2 transforms	static_tf_publisher	Static robot transforms

The simulated camera, LiDAR, and odometry data are published at approximately 10 Hz.
Build
Requirements

    Ubuntu 22.04

    ROS 2 Humble

    Python 3

    C++

    colcon

Clone the repository and enter the workspace:

cd multi_node_robot_system_ws

Build the workspace:

colcon build

Source the workspace:

source install/setup.bash

Run

Launch the complete robot system:

ros2 launch robot_bringup robot_system.launch.py

Verify the running nodes:

ros2 node list

Expected nodes:

/camera_publisher
/lidar_publisher
/odometry_publisher
/static_tf_publisher

Inspect the primary topics:

ros2 topic list

Example topic inspection:

ros2 topic echo /scan --once
ros2 topic echo /odom --once
ros2 topic echo /camera/image_raw --once

Check publishing rates:

ros2 topic hz /scan
ros2 topic hz /odom
ros2 topic hz /camera/image_raw

Testing

The project contains automated tests for both the Python sensor nodes and the C++ odometry node.

Run all tests:

colcon test

View detailed test results:

colcon test-result --verbose

The test suite includes validation of:

    Camera message construction and metadata

    LiDAR scan configuration and sample count

    Odometry frame IDs and initial position

    Odometry position advancement

    Package linting and ROS 2 build checks

Python sensor nodes are tested with pytest, while the C++ odometry functionality is tested with GoogleTest.
Notable Design Decisions
Sensor QoS

The camera and LiDAR publishers use BEST_EFFORT reliability because they produce continuous sensor streams. If an individual sensor message is lost, receiving the newest measurement is generally more useful than waiting for an older measurement to be retransmitted.

Odometry uses RELIABLE reliability because robot pose and motion information is treated as important state information within this project.
Static map -> odom

The map -> odom transform is an identity transform and remains static because this project does not implement SLAM or a localization system that corrects the robot's estimated position in the map.

The simulated robot's movement is represented by the dynamic:

odom -> base_link

transform.
Testability Refactor

The C++ odometry node was refactored so message construction and state advancement could be tested independently from the ROS 2 timer callback.

The node exposes separate functionality for:

build_odometry_message()
advance_position()

This allows GoogleTest to verify odometry behavior deterministically without depending on timer timing during the unit tests.
Debugging and Integration Verification

The complete system was integration-tested using ROS 2 command-line tools including:

ros2 node list
ros2 topic list
ros2 topic echo
ros2 topic hz
ros2 topic info -v
ros2 run tf2_ros tf2_echo
ros2 run tf2_tools view_frames
ros2 doctor

As part of the debugging exercise, a deliberate case-sensitive TF frame mismatch (lidar_Link instead of lidar_link) was introduced into the LiDAR publisher.

The system still compiled, launched, and published /scan, but TF2 could not resolve the sensor frame. The issue was diagnosed using /scan message inspection, tf2_echo, and view_frames, then corrected and verified through another full integration test.

This demonstrated an important ROS 2 debugging principle: a successful build and launch do not guarantee that all runtime integrations are correct.