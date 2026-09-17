import rclpy

from robot_sensors.camera_publisher import CameraPublisher


def test_camera_message():
    rclpy.init()
    node = CameraPublisher()

    try:
        msg = node.build_image_message()

        assert msg.header.frame_id == 'camera_link'
        assert msg.encoding == 'rgb8'
        assert msg.width == 64
        assert msg.height == 48

        assert msg.step == msg.width * 3
        assert len(msg.data) == msg.step * msg.height

    finally:
        node.destroy_node()
        rclpy.try_shutdown()
