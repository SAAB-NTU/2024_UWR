#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
from geometry_msgs.msg import PoseStamped, Vector3Stamped
from std_msgs.msg import Header, Float64
from message_filters import ApproximateTimeSynchronizer, Subscriber
from sonar_msgs.msg import ThreeSonarDepth,ConfScal
from sensor_msgs.msg import Image
import pandas as pd
from scipy.spatial.transform import Rotation as R
import cv_bridge
import os
import cv2
import numpy as np

class RosbagSync(Node):
    def __init__(self):
        super().__init__('rosbag_time_sync')
        self.time="1205_ed_0_05_conf_4_Angles"
        # Define subscribers
        self.get_logger().info('Initializing subscribers...')
        self.sub1 = Subscriber(self, PoseStamped, '/Pose')
        self.sub2 = Subscriber(self, ConfScal, '/Confidence_SONAR')
        self.sub3 = Subscriber(self, Vector3Stamped, '/IMU_filtered')
        self.sub4 = Subscriber(self,ThreeSonarDepth,'/SONAR_raw')
        self.sub5=Subscriber(self,Imu,'/IMU_raw')
        
        self.ts = ApproximateTimeSynchronizer([self.sub1, self.sub2, self.sub3,self.sub4,self.sub5], 10, slop=0.002)  # Increase the queue size for stability
        self.ts.registerCallback(self.callback)

        self.ts2 = ApproximateTimeSynchronizer([self.sub2,self.sub4], 10, slop=0.002)  # Increase the queue size for stability
        self.ts2.registerCallback(self.log_sonar_data)
        #self.image_bridge=cv_bridge.CvBridge()
        self.synchronized_data = []
        self.synchronized_data_imu = []
        self.synchronized_data_sonar=[]
        self.ts3 = ApproximateTimeSynchronizer([self.sub3,self.sub5,self.sub1], 10, slop=0.002)  # Increase the queue size for stability
        self.ts3.registerCallback(self.callback_imu)
        self.get_logger().info('Subscribers and synchronizer initialized successfully!')
        self.counter=0
        #self.sub1_1 = self.create_subscription(ThreeSonarDepth, '/sonar', self.log_sonar_data,10)
        #self.sub2_1 = self.create_subscription(Vector3Stamped, '/imu/acceleration', self.log_acceleration_data,10)
        #self.sub3_1 = self.create_subscription(Vector3Stamped, '/imu/angular_velocity', self.log_angular_velocity_data,10)
    
    @staticmethod
    def quaternion_to_euler(quaternion):
        """
        Convert quaternion to Euler angles (roll, pitch, yaw).
        """
        # Quaternion input should be [x, y, z, w] for scipy
        q = [quaternion.x, quaternion.y, quaternion.z, quaternion.w]
        r = R.from_quat(q)  # Create a rotation object
        euler = r.as_euler('xyz', degrees=False)  # Convert to Euler angles (ZYX convention)
        return euler
    
    def log_sonar_data(self, data2,data1):
        timestamp = data1.header.stamp
        self.synchronized_data_sonar.append({
            'Timestamp': timestamp.sec + timestamp.nanosec * 1e-9,
            'Sonar_distance_1': data1.distance_1,
            'Confidence_1_dev': data1.confidence_1,
            'Confidence_1': data2.confidence_1,
            'Sonar_distance_2': data1.distance_2,
            'Confidence_2_dev': data1.confidence_2,
            'Confidence_2': data2.confidence_2,
            'Sonar_distance_3': data1.distance_3,
            'Confidence_3_dev': data1.confidence_3,
            'Confidence_3': data2.confidence_3})
        synchronized_df = pd.DataFrame(self.synchronized_data_sonar)
        synchronized_df.to_csv('/home/saab/Desktop/2024_UWR/Analysis/CSVs/output_6_Nov_confidence_case_'+self.time+'.csv', index=False)

    #def log_acceleration_data(self, data):
    #    self.get_logger().info(f"Received IMU acceleration data: x: {data.vector.x}")

    #def log_angular_velocity_data(self, data):
    #    self.get_logger().info(f"Received IMU angular velocity data: x: {data.vector.x}")


    def callback(self, data1, data2, data3,data4,data5):
        # Log entry into the callback
        self.get_logger().info("Callback triggered with synchronized messages")

        # Log the received data for debugging
        #self.get_logger().info(f"Sonar Data: Distance 1: {data1.distance_1}, Confidence 1: {data1.confidence_1}")
        #self.get_logger().info(f"IMU Acceleration: x: {data2.vector.x}, y: {data2.vector.y}, z: {data2.vector.z}")
        #self.get_logger().info(f"IMU Angular Velocity: x: {data3.vector.x}, y: {data3.vector.y}, z: {data3.vector.z}")
        quaternion = data5.orientation
        euler_angles = self.quaternion_to_euler(quaternion)
        # Synchronization logic
        timestamp = data1.header.stamp
        self.synchronized_data.append({
            'Timestamp': timestamp.sec + timestamp.nanosec * 1e-9,
            'Pose_X': data1.pose.position.x,
            'Confidence_1': data2.confidence_1,
            'Confidence_1_dev':data4.confidence_1,
            'Pose_Y': data1.pose.position.y,
            'Confidence_2': data2.confidence_2,
            'Confidence_2_dev':data4.confidence_2,
            'Pose_Z': data1.pose.position.z,
            'Confidence_3':data2.confidence_3,
            'Confidence_3_dev':data4.confidence_3,
            'IMU_Linear_Acc_X': data3.vector.x,
            'IMU_Linear_Acc_Y': data3.vector.y,
            'IMU_Linear_Acc_Z': data3.vector.z,
            'Sonar_distance_1': data4.distance_1,
            'Sonar_distance_2': data4.distance_2,
            'Sonar_distance_3': data4.distance_3,
            'Angle_X':np.rad2deg(euler_angles[0]),
            'Angle_Y':np.rad2deg(euler_angles[1]),
            'Angle_Z':np.rad2deg(euler_angles[2])
        })
        
        # Log synchronized data size
        # self.get_logger().info(f"Synchronized data size: {len(self.synchronized_data)}")
        
        # img=self.image_bridge.imgmsg_to_cv2(data4)
        # img=cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
        # #cv2.imwrite("/home/uwr/Desktop/output/"+str(timestamp.sec + timestamp.nanosec * 1e-9)+".png",img)
        # cv2.imwrite("/home/uwr/Desktop/output/"+f"{self.counter:03d}"+".png",cv2.flip(img, 0) )
        # self.counter+=1
        # # Save to CSV file
        synchronized_df = pd.DataFrame(self.synchronized_data)
        synchronized_df.to_csv('/home/saab/Desktop/2024_UWR/Analysis/CSVs/output_6_Nov_case_'+self.time+'.csv', index=False)
        self.get_logger().info('Data written to CSV file!')
    '''
    def callback_pred(self, data1):
        # Log entry into the callback
        self.get_logger().info("Callback triggered with synchronized messages")

        # Log the received data for debugging
        #self.get_logger().info(f"Sonar Data: Distance 1: {data1.distance_1}, Confidence 1: {data1.confidence_1}")
        #self.get_logger().info(f"IMU Acceleration: x: {data2.vector.x}, y: {data2.vector.y}, z: {data2.vector.z}")
        #self.get_logger().info(f"IMU Angular Velocity: x: {data3.vector.x}, y: {data3.vector.y}, z: {data3.vector.z}")

        # Synchronization logic
        timestamp = data1.header.stamp
        self.synchronized_data.append({
            'Timestamp': timestamp.sec + timestamp.nanosec * 1e-9,
            'Pose_X': data1.pose.position.x,
            'Pose_Y': data1.pose.position.y,
            'Pose_Z': data1.pose.position.z,
        })
        
        # Log synchronized data size
        # self.get_logger().info(f"Synchronized data size: {len(self.synchronized_data)}")
        
        # img=self.image_bridge.imgmsg_to_cv2(data4)
        # img=cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
        # #cv2.imwrite("/home/uwr/Desktop/output/"+str(timestamp.sec + timestamp.nanosec * 1e-9)+".png",img)
        # cv2.imwrite("/home/uwr/Desktop/output/"+f"{self.counter:03d}"+".png",cv2.flip(img, 0) )
        # self.counter+=1
        # # Save to CSV file
        synchronized_df = pd.DataFrame(self.synchronized_data)
        synchronized_df.to_csv('/home/uwr/Desktop/output.csv', index=False)
        self.get_logger().info('Data written to CSV file!')
        
'''
    def callback_imu(self, data1,data2,data3):
        # Log entry into the callback
        self.get_logger().info("Callback triggered with synchronized messages")

        # Log the received data for debugging
        #self.get_logger().info(f"Sonar Data: Distance 1: {data1.distance_1}, Confidence 1: {data1.confidence_1}")
        #self.get_logger().info(f"IMU Acceleration: x: {data2.vector.x}, y: {data2.vector.y}, z: {data2.vector.z}")
        #self.get_logger().info(f"IMU Angular Velocity: x: {data3.vector.x}, y: {data3.vector.y}, z: {data3.vector.z}")

        # Synchronization logic
        timestamp = data1.header.stamp
        self.synchronized_data_imu.append({
            'Timestamp': timestamp.sec + timestamp.nanosec * 1e-9,
            'IMU_Linear_Acc_X': data2.linear_acceleration.x,
            'IMU_Linear_Acc_Y': data2.linear_acceleration.y,
            'IMU_Linear_Acc_Z': data2.linear_acceleration.z,
            'Filtered_X': data1.vector.x,
            'Filtered_Y': data1.vector.y,
            'Filtered_Z': data1.vector.z,
            'Pose_X': data3.pose.position.x,
            'Pose_Y': data3.pose.position.y,
            'Pose_Z': data3.pose.position.z,
        })
        
        # Log synchronized data size
        # self.get_logger().info(f"Synchronized data size: {len(self.synchronized_data)}")
        
        # img=self.image_bridge.imgmsg_to_cv2(data4)
        # img=cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
        # #cv2.imwrite("/home/uwr/Desktop/output/"+str(timestamp.sec + timestamp.nanosec * 1e-9)+".png",img)
        # cv2.imwrite("/home/uwr/Desktop/output/"+f"{self.counter:03d}"+".png",cv2.flip(img, 0) )
        # self.counter+=1
        # # Save to CSV file
        synchronized_df = pd.DataFrame(self.synchronized_data_imu)
        synchronized_df.to_csv('/home/saab/Desktop/2024_UWR/Analysis/CSVs/output_6_Nov_IMU_case_'+self.time+'.csv', index=False)
        self.get_logger().info('Data written to CSV file!')

def main(args=None):
    rclpy.init(args=args)
    #os.makedirs("/home/uwr/Desktop/output",exist_ok=True)
    node = RosbagSync()
    
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    try:
        main()
    except rclpy.exceptions.ROSInterruptException:
        pass
