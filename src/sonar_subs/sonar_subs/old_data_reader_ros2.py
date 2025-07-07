#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
from sonar_msgs.msg import ThreeSonarDepth
from std_msgs.msg import Header, Float64
import pandas as pd
import numpy as np
from glob import glob

class DataPublisher(Node):
    def __init__(self, csv_path_idx=6):
        super().__init__('data_publisher')
        self.i = 0
        self.paths = sorted(glob("/home/saab/SAAB-Experiment/exp7/data/*.csv"))
        self.path = self.paths[csv_path_idx]
        self.imu_pub = self.create_publisher(Imu, '/imu/data_raw', 10)
        self.sonar_pub = self.create_publisher(ThreeSonarDepth, '/sbs', 10)
        #self.depth_pub = self.create_publisher(Float64, '/depth_msg', 10)
        self.df = pd.read_csv(self.path)
        self.get_logger().info(str(self.df["sonar_distance_1"][:5]))
        self.df["time"] -= self.df.iloc[0]["time"]
        sec, nsec = self.get_clock().now().seconds_nanoseconds()
        self.start_time = sec + nsec * 1e-9
        self.timer = self.create_timer(0.001, self.timer_callback)

    def imu_data_publisher(self, row):
        imu_msg = Imu()
        imu_msg.header.stamp = self.get_clock().now().to_msg()
        imu_msg.linear_acceleration.x = row["accel x"]
        imu_msg.linear_acceleration.y = row["accel y"]
        imu_msg.linear_acceleration.z = row["accel z"]
        imu_msg.angular_velocity.x = row["angular_vel x"]
        imu_msg.angular_velocity.y = row["angular_vel y"]
        imu_msg.angular_velocity.z = row["angular_vel z"]
        self.imu_pub.publish(imu_msg)

    def sonar_data_publisher(self, row):
        sonar_msg = ThreeSonarDepth()
        sonar_msg.header.stamp = self.get_clock().now().to_msg()
        sonar_msg.distance_1 = row["sonar_distance_1"] * 1000
        sonar_msg.confidence_1 = 100.0
        sonar_msg.distance_2 = row["sonar_distance_2"] * 1000
        try:
            sonar_msg.distance_3 = row["depth"] #To be similar to other experiments
        except Exception:
            sonar_msg.depth = 0.0
        sonar_msg.confidence_2 = 100.0
        self.sonar_pub.publish(sonar_msg)

    def timer_callback(self):
        if self.i < len(self.df):
            sec, nsec = self.get_clock().now().seconds_nanoseconds()
            now = sec + nsec * 1e-9
            elapsed_time = now - self.start_time
            if elapsed_time >= self.df.iloc[self.i]["time"]:
                if self.df.iloc[self.i]["sensor"] == "imu":
                    self.imu_data_publisher(self.df.iloc[self.i])
                else:
                    self.sonar_data_publisher(self.df.iloc[self.i])
                self.i += 1
        else:
            self.get_logger().info('Done publishing all data.')
            rclpy.shutdown()

def main(args=None):
    rclpy.init(args=args)
    csv_path_idx = 2  # Default index, can be changed as needed
    node = DataPublisher(csv_path_idx=csv_path_idx)
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
