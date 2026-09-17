#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/static_transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include <memory>

class StaticTFPublisher : public rclcpp::Node
{

public:
  StaticTFPublisher()
  : Node("static_tf_publisher")
  {
    //Initialiize the static transform broadcaster
    tf_static_broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);

    geometry_msgs::msg::TransformStamped camera_transform;
    camera_transform.header.frame_id = "base_link";
    camera_transform.child_frame_id = "camera_link";

    camera_transform.header.stamp = this->get_clock()->now();

    camera_transform.transform.translation.x = 0.20;
    camera_transform.transform.translation.y = 0.00;
    camera_transform.transform.translation.z = 0.20;

    //Telling tf2 how camera is rotated
    camera_transform.transform.rotation.x = 0;
    camera_transform.transform.rotation.y = 0;
    camera_transform.transform.rotation.z = 0;
    camera_transform.transform.rotation.w = 1;

    //Hands completed transform to the static TF broadcaster
    tf_static_broadcaster_->sendTransform(camera_transform);


    geometry_msgs::msg::TransformStamped lidar_transform;
    lidar_transform.header.frame_id = "base_link";
    lidar_transform.child_frame_id = "lidar_link";

    lidar_transform.header.stamp = this->get_clock()->now();

    //Mounting the lidar
    lidar_transform.transform.translation.x = 0.00;
    lidar_transform.transform.translation.y = 0.00;
    lidar_transform.transform.translation.z = 0.10;


    //Lidar has no rotation relative to base_link
    lidar_transform.transform.rotation.x = 0;
    lidar_transform.transform.rotation.y = 0;
    lidar_transform.transform.rotation.z = 0;
    lidar_transform.transform.rotation.w = 1;

    //Hands completed transform to the static TF broadcaster
    tf_static_broadcaster_->sendTransform(lidar_transform);

    geometry_msgs::msg::TransformStamped map_transform;
    map_transform.header.frame_id = "map";
    map_transform.child_frame_id = "odom";

    map_transform.header.stamp = this->get_clock()->now();

    //Mounting the lidar
    map_transform.transform.translation.x = 0.0;
    map_transform.transform.translation.y = 0.0;
    map_transform.transform.translation.z = 0.0;


    //map has no rotation relative to base_link
    map_transform.transform.rotation.x = 0;
    map_transform.transform.rotation.y = 0;
    map_transform.transform.rotation.z = 0;
    map_transform.transform.rotation.w = 1;

    tf_static_broadcaster_->sendTransform(map_transform);


  }

private:
  std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_static_broadcaster_;

};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<StaticTFPublisher>());
  rclcpp::shutdown();
  return 0;
}
