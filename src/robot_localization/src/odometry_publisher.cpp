#include <chrono>
#include <memory>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "robot_localization/odometry_publisher.hpp"

using namespace std::chrono_literals;


OdometryPublisher::OdometryPublisher()
: Node("odometry_publisher"), x_position_(0.0)
{
  publisher_ = this->create_publisher<nav_msgs::msg::Odometry>(
    "/odom", 10);

  tf_broadcaster_ =
    std::make_shared<tf2_ros::TransformBroadcaster>(this);

  timer_ = this->create_wall_timer(
    100ms,
    std::bind(&OdometryPublisher::timer_callback, this));
}


nav_msgs::msg::Odometry OdometryPublisher::build_odometry_message()
{
  nav_msgs::msg::Odometry msg;

  msg.header.stamp = this->get_clock()->now();
  msg.header.frame_id = "odom";
  msg.child_frame_id = "base_link";

  msg.pose.pose.position.x = x_position_;
  msg.pose.pose.position.y = 0.0;
  msg.pose.pose.position.z = 0.0;

  msg.pose.pose.orientation.x = 0.0;
  msg.pose.pose.orientation.y = 0.0;
  msg.pose.pose.orientation.z = 0.0;
  msg.pose.pose.orientation.w = 1.0;

  msg.twist.twist.linear.x = 0.5;

  return msg;
}

void OdometryPublisher::advance_position()
{
  x_position_ += 0.05;
}


void OdometryPublisher::timer_callback()
{
  auto msg = build_odometry_message();

  publisher_->publish(msg);

  geometry_msgs::msg::TransformStamped odom_transform;

  odom_transform.header.stamp = msg.header.stamp;
  odom_transform.header.frame_id = "odom";
  odom_transform.child_frame_id = "base_link";

  odom_transform.transform.translation.x = x_position_;
  odom_transform.transform.translation.y = 0.0;
  odom_transform.transform.translation.z = 0.0;

  odom_transform.transform.rotation.x = 0.0;
  odom_transform.transform.rotation.y = 0.0;
  odom_transform.transform.rotation.z = 0.0;
  odom_transform.transform.rotation.w = 1.0;

  tf_broadcaster_->sendTransform(odom_transform);

  advance_position();
}
