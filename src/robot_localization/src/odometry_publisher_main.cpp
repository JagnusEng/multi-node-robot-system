#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "robot_localization/odometry_publisher.hpp"


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  rclcpp::spin(
    std::make_shared<OdometryPublisher>());

  rclcpp::shutdown();

  return 0;
}
