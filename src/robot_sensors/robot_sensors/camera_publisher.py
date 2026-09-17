import rclpy
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from sensor_msgs.msg import Image


class CameraPublisher(Node):
    def __init__(self):
        super().__init__('camera_publisher')

        self.publisher_ = self.create_publisher(
            Image,
            '/camera/image_raw',
            qos_profile_sensor_data
        )

        timer_period = 0.1
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def build_image_message(self):
        msg = Image()

        msg.height = 48
        msg.width = 64
        msg.encoding = 'rgb8'
        msg.is_bigendian = 0

        msg.step = msg.width * 3
        msg.data = bytes(msg.step * msg.height)

        msg.header.frame_id = 'camera_link'
        msg.header.stamp = self.get_clock().now().to_msg()

        return msg

    def timer_callback(self):
        msg = self.build_image_message()
        self.publisher_.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = CameraPublisher()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.try_shutdown()


if __name__ == '__main__':
    main()
