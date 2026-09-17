#ifndef ROBOT_LOCALIZATION__ODOMETRY_PUBLISHER_HPP_
#define ROBOT_LOCALIZATION__ODOMETRY_PUBLISHER_HPP_

#include <memory>

#include "nav_msgs/msg/odometry.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"


class OdometryPublisher : public rclcpp::Node
{
public:
  OdometryPublisher();

  nav_msgs::msg::Odometry build_odometry_message();

  void advance_position();

private:
  void timer_callback();

  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;

  double x_position_;
};

#endif  // ROBOT_LOCALIZATION__ODOMETRY_PUBLISHER_HPP_
