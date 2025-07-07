import rclpy
import os
from rclpy.node import Node
from sonar_msgs.msg import ThreeSonarDepth  # Change this to match your message type
from sensor_msgs.msg import Image  # Example message type (update this)
import time
import pandas as pd

# --- Configuration ---
TOPIC_NAME = "/sbs"  # Change to your topic
IMAGE_FOLDER = "/media/saab/f7ee81f1-4052-4c44-b470-0a4a650ee479/cfar_cpp/Analysis/Oculus_reader/20250219_201133/polar/"  # Folder with images
TIME_TOLERANCE = 25  # Max time difference (seconds) for a match

class ImageMatcher(Node):
    def __init__(self):
        super().__init__("image_matcher")
        self.synchronized_data = []
        # Subscribe to the topic
        self.subscription = self.create_subscription(
            ThreeSonarDepth,  # Change this to your actual message type
            TOPIC_NAME,
            self.callback,
            10
        )
        self.subscription  # Prevent unused variable warning

        # Load image timestamps
        self.images, self.image_timestamps = self.get_image_timestamps(IMAGE_FOLDER)
        self.image_idx = 0  # Index of the next image to match

        self.get_logger().info(f"Loaded {len(self.image_timestamps)} images. Waiting for topic messages...")

    def get_image_timestamps(self, folder):
        """Extracts timestamps from image filenames."""
        images = sorted(os.listdir(folder))  # Sort images by timestamp
        timestamps = [float(os.path.splitext(img)[0]) for img in images]  # Convert filenames to float timestamps
        return images, timestamps

    def callback(self, msg):
        
        """Matches incoming messages to the closest image timestamp."""
        if self.image_idx >= len(self.image_timestamps):
            self.get_logger().info("All images processed.")
            return

        # Get message timestamp
        msg_time = msg.header.stamp.sec + msg.header.stamp.nanosec * 1e-9

        # Get next image timestamp
        img_time = self.image_timestamps[self.image_idx]
        time_diff = abs(msg_time+28800 - img_time)
        self.get_logger().info(f"{msg_time+28800} and {img_time}")
        if time_diff <= TIME_TOLERANCE:
            matched_image = self.images[self.image_idx]
            self.get_logger().info(f"Matched: {matched_image} -> ROS Time: {msg_time:.6f}")
            self.image_idx += 1  # Move to the next image
            '''
            timestamp = msg.header.stamp
            self.synchronized_data.append({
                'Timestamp': timestamp.sec + timestamp.nanosec * 1e-9,
                'Sonar_Distance_1': msg.distance_1,
                'Confidence_1': msg.confidence_1,
                'Sonar_Distance_2': msg.distance_2,
                'Confidence_2': msg.confidence_2,
                'Sonar_Distance_3': msg.distance_3,})
            synchronized_df = pd.DataFrame(self.synchronized_data)
            synchronized_df.to_csv('/home/saab/Desktop/20250219_201133.csv', index=False)'
            '''

def main():
    rclpy.init()
    node = ImageMatcher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
