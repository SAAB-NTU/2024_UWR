#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
from geometry_msgs.msg import PoseStamped, Vector3Stamped
from std_msgs.msg import Header, Float64
from message_filters import ApproximateTimeSynchronizer, Subscriber
from sonar_msgs.msg import ThreeSonarDepth
from sensor_msgs.msg import Image
import pandas as pd
import cv_bridge
import os
import cv2

class RosbagSync(Node):
    def __init__(self):
        super().__init__('rosbag_time_sync')

        # Define subscribers
        self.get_logger().info('Initializing subscribers...')
        self.sub1 = Subscriber(self, ThreeSonarDepth, '/sonar')
        self.sub2 = Subscriber(self, Vector3Stamped, '/imu/acceleration')
        self.sub3 = Subscriber(self, Vector3Stamped, '/imu/angular_velocity')
        self.sub4 = Subscriber(self,Image,'/camera/realsense2_camera/color/image_raw')
        
        self.ts = ApproximateTimeSynchronizer([self.sub1, self.sub2, self.sub3,self.sub4], 10, slop=0.002)  # Increase the queue size for stability
        self.ts.registerCallback(self.callback)
        self.image_bridge=cv_bridge.CvBridge()
        self.synchronized_data = []
        self.get_logger().info('Subscribers and synchronizer initialized successfully!')
        self.counter=0
        #self.sub1_1 = self.create_subscription(ThreeSonarDepth, '/sonar', self.log_sonar_data,10)
        #self.sub2_1 = self.create_subscription(Vector3Stamped, '/imu/acceleration', self.log_acceleration_data,10)
        #self.sub3_1 = self.create_subscription(Vector3Stamped, '/imu/angular_velocity', self.log_angular_velocity_data,10)


    def log_sonar_data(self, data):
        timestamp = data.header.stamp
        self.synchronized_data.append({
            'Timestamp': timestamp.sec + timestamp.nanosec * 1e-9,
            'Sonar_Distance_1': data.distance_1,
            'Confidence_1': data.confidence_1,
            'Sonar_Distance_2': data.distance_2,
            'Confidence_2': data.confidence_2,
            'Sonar_Distance_3': data.distance_3,})
        synchronized_df = pd.DataFrame(self.synchronized_data)
        synchronized_df.to_csv('/home/uwr/Desktop/output.csv', index=False)

    #def log_acceleration_data(self, data):
    #    self.get_logger().info(f"Received IMU acceleration data: x: {data.vector.x}")

    #def log_angular_velocity_data(self, data):
    #    self.get_logger().info(f"Received IMU angular velocity data: x: {data.vector.x}")


    def callback(self, data1, data2, data3,data4):
        # Log entry into the callback
        self.get_logger().info("Callback triggered with synchronized messages")

        # Log the received data for debugging
        self.get_logger().info(f"Sonar Data: Distance 1: {data1.distance_1}, Confidence 1: {data1.confidence_1}")
        self.get_logger().info(f"IMU Acceleration: x: {data2.vector.x}, y: {data2.vector.y}, z: {data2.vector.z}")
        self.get_logger().info(f"IMU Angular Velocity: x: {data3.vector.x}, y: {data3.vector.y}, z: {data3.vector.z}")

        # Synchronization logic
        timestamp = data1.header.stamp
        self.synchronized_data.append({
            'Timestamp': timestamp.sec + timestamp.nanosec * 1e-9,
            'Sonar_Distance_1': data1.distance_1,
            'Confidence_1': data1.confidence_1,
            'Sonar_Distance_2': data1.distance_2,
            'Confidence_2': data1.confidence_2,
            'Sonar_Distance_3': data1.distance_3,
            'Confidence_3': data1.confidence_3,
            'IMU_Linear_Acc_X': data2.vector.x,
            'IMU_Linear_Acc_Y': data2.vector.y,
            'IMU_Linear_Acc_Z': data2.vector.z,
            'IMU_Angular_Vel_X': data3.vector.x,
            'IMU_Angular_Vel_Y': data3.vector.y,
            'IMU_Angular_Vel_Z': data3.vector.z,
        })
        
        # Log synchronized data size
        self.get_logger().info(f"Synchronized data size: {len(self.synchronized_data)}")
        
        img=self.image_bridge.imgmsg_to_cv2(data4)
        img=cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
        #cv2.imwrite("/home/uwr/Desktop/output/"+str(timestamp.sec + timestamp.nanosec * 1e-9)+".png",img)
        cv2.imwrite("/home/uwr/Desktop/output/"+f"{self.counter:03d}"+".png",img)
        self.counter+=1
        # Save to CSV file
        synchronized_df = pd.DataFrame(self.synchronized_data)
        synchronized_df.to_csv('/home/uwr/Desktop/output.csv', index=False)
        self.get_logger().info('Data written to CSV file!')
        

def main(args=None):
    rclpy.init(args=args)
    os.makedirs("/home/uwr/Desktop/output",exist_ok=True)
    node = RosbagSync()
    
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    try:
        main()
    except rclpy.exceptions.ROSInterruptException:
        pass
