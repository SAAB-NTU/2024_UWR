import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseStamped
from sensor_msgs.msg import Image
from sonar_msgs.msg import ThreeSonarDepth
import os
import math
from cv_bridge import CvBridge
import cv2


class PoseImageSaver(Node):
    def __init__(self):
        super().__init__('pose_image_saver')

        # Parameters
        self.save_distance = 0 # Distance threshold to save images
        self.image_save_folder = '/home/saab/Desktop/saved_images_1302_'+str(self.save_distance)
        os.makedirs(self.image_save_folder,exist_ok=True)
        # Subscribers
        #self.pose_sub = self.create_subscription(
        #    PoseStamped,
        #    '/Pose',
        #    self.pose_callback,
        #    10
        #)
        self.pose_sub = self.create_subscription(
            ThreeSonarDepth,
            '/sonar',
            self.pose_callback,
            10
        )
        self.image_sub = self.create_subscription(
            Image,
            '/camera/realsense2_camera/color/image_raw',
            self.image_callback,
            10
        )

        # Variables
        self.last_pose = None
        self.bridge = CvBridge()
        self.image_to_save = None
        self.image_count = 0

        # Create save folder if it doesn't exist
        os.makedirs(self.image_save_folder, exist_ok=True)

    def pose_callback(self, msg: PoseStamped):
        current_pose = msg
        self.save_distance=msg.distance_2
        if self.last_pose is not None:
            distance = self.calculate_distance(self.last_pose, current_pose)

            if distance >= self.save_distance:
                self.last_pose = current_pose
                #self.save_image(distance)
        else:
            # Initialize last_pose
            self.last_pose = current_pose

    def image_callback(self, msg: Image):
        # Store the latest image
        self.image_to_save = msg
        self.save_image(self.save_distance)
    def save_image(self,distance):
        if self.image_to_save is not None:
            try:
                # Convert ROS Image to OpenCV Image
                cv_image = self.bridge.imgmsg_to_cv2(self.image_to_save, desired_encoding='bgr8')

                # Generate a filename
                #image_path = os.path.join(self.image_save_folder, f'image_{self.image_count:04d}.jpg')
                image_path = os.path.join(self.image_save_folder, f'image_{self.image_count:04d}_{distance:04f}.jpg')
                # Save the image
                cv2.imwrite(image_path, cv_image)
                self.image_count += 1
                self.get_logger().info(f'Image saved at: {image_path}')
            except Exception as e:
                self.get_logger().error(f'Failed to save image: {str(e)}')

    @staticmethod
    def calculate_distance(pose1, pose2):
        """Calculate the Euclidean distance between two poses."""
        #dx = pose2.position.x - pose1.position.x
        #dy = pose2.position.y - pose1.position.y
        dx = pose2.distance_1 - pose1.distance_1
        dy = pose2.distance_2 - pose1.distance_2
        #dx=dx/1000
        #dy=dy/1000
        #dz = pose2.position.z - pose1.position.z
        #return math.sqrt(dx ** 2 + dy ** 2 )
        return pose1.distance_2

def main(args=None):
    rclpy.init(args=args)
    node = PoseImageSaver()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
