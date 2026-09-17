import math

import rclpy
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from sensor_msgs.msg import LaserScan


class LidarPublisher(Node):
    def __init__(self):
        super().__init__('lidar_publisher')

        self.publisher_ = self.create_publisher(
            LaserScan,
            '/scan',
            qos_profile_sensor_data
        )

        timer_period = 0.1
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def build_scan_message(self):
        msg = LaserScan()

        msg.angle_min = -math.pi / 2
        msg.angle_max = math.pi / 2
        msg.angle_increment = math.pi / 180

        msg.range_min = 0.1
        msg.range_max = 10.0
        msg.scan_time = 0.1
        msg.time_increment = 0.1 / 181

        msg.ranges = [3.0] * 181

        msg.header.frame_id = 'lidar_link'
        msg.header.stamp = self.get_clock().now().to_msg()

        return msg

    def timer_callback(self):
        msg = self.build_scan_message()
        self.publisher_.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = LidarPublisher()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.try_shutdown()


if __name__ == '__main__':
    main()
