import rclpy
from robot_sensors.lidar_publisher import LidarPublisher


def test_lidar_message():
    rclpy.init()
    node = LidarPublisher()

    try:
        msg = node.build_scan_message()

        expected_count = round(
            (msg.angle_max - msg.angle_min) / msg.angle_increment
        ) + 1

        assert len(msg.ranges) == expected_count

        assert msg.header.frame_id == "lidar_link"
        assert msg.range_min == 0.1
        assert msg.range_max == 10.0
        assert len(msg.ranges) == 181

    finally:
        node.destroy_node()
        rclpy.try_shutdown()
