import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseStamped
from sensor_msgs.msg import Image
import os
import math
from cv_bridge import CvBridge
import cv2
import numpy as np


class imgpub(Node):
    def __init__(self):
        super().__init__('img_pub')
        self.image_path = '/home/saab/Desktop/test_4.png'  # Change this to your actual image path
        self.publisher_ = self.create_publisher(Image, '/oculus_sonar/ping_image', 10)
        self.bridge = CvBridge()
        self.timer = self.create_timer(0.0667, self.publish_image)  # Publish every 1 second
        
    def publish_image(self):
		# Read image
        image = cv2.imread(self.image_path,0)
        # image=np.uint16(image) * 256
        if image is None:
            self.get_logger().error(f"Failed to load image from {self.image_path}")
            return

        # Convert to ROS2 Image message
        image_msg = self.bridge.cv2_to_imgmsg(image, encoding='mono8')

        # Publish image
        self.publisher_.publish(image_msg)
        self.get_logger().info(f"Published image from {self.image_path}")


def main(args=None):
    rclpy.init(args=args)
    node = imgpub()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
