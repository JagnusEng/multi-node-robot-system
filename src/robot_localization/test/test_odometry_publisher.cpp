#include <gtest/gtest.h>

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "robot_localization/odometry_publisher.hpp"


TEST(OdometryPublisherTest, InitialPositionIsZero)
{
  rclcpp::init(0, nullptr);

  auto node = std::make_shared<OdometryPublisher>();

  auto msg = node->build_odometry_message();

  EXPECT_DOUBLE_EQ(msg.pose.pose.position.x, 0.0);

  node.reset();
  rclcpp::shutdown();
}

TEST(OdometryPublisherTest, UsesCorrectFrames)
{
  rclcpp::init(0, nullptr);

  auto node = std::make_shared<OdometryPublisher>();

  auto msg = node->build_odometry_message();

  EXPECT_EQ(msg.header.frame_id, "odom");
  EXPECT_EQ(msg.child_frame_id, "base_link");

  node.reset();
  rclcpp::shutdown();
}


TEST(OdometryPublisherTest, PositionAdvancesCorrectly)
{
  rclcpp::init(0, nullptr);

  auto node = std::make_shared<OdometryPublisher>();

  auto initial_msg = node->build_odometry_message();
  EXPECT_DOUBLE_EQ(initial_msg.pose.pose.position.x, 0.0);

  node->advance_position();

  auto first_msg = node->build_odometry_message();
  EXPECT_DOUBLE_EQ(first_msg.pose.pose.position.x, 0.05);

  node->advance_position();

  auto second_msg = node->build_odometry_message();
  EXPECT_DOUBLE_EQ(second_msg.pose.pose.position.x, 0.10);

  node.reset();
  rclcpp::shutdown();
}
