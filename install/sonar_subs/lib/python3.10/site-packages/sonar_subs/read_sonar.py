#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sonar_msgs.msg import ThreeSonarDepth
from brping import Ping1D
from rclpy.qos import QoSProfile, ReliabilityPolicy, DurabilityPolicy

def main():
    # Initialize ROS 2
    rclpy.init()
    node = rclpy.create_node("single_beam_sonar_node")
    rclpy.logging.get_logger("single_beam_sonar_node").info("Init")
    qos_profile = QoSProfile(
        depth=1,  # Keep only the latest message
        reliability=ReliabilityPolicy.BEST_EFFORT,  # Fast, but may drop messages
        durability=DurabilityPolicy.VOLATILE  # Do not persist messages
    )
    # Create a publisher for the custom message type
    pub_sonar = node.create_publisher(ThreeSonarDepth, "sonar", qos_profile=qos_profile)
    
    # Declare parameters with default values
    sonar_port1 = node.declare_parameter("sonar0/sonar_port", "/dev/ttyACM0").value
    ping_interval = node.declare_parameter("sonar/ping_interval", 250).value
    
    assert isinstance(sonar_port1, str), 'port parameter must be a str'
    assert isinstance(ping_interval, int), 'ping_interval parameter must be an integer'
    
    # Initialize sonar drivers
    sonar_driver1 = Ping1D()
    sonar_driver1.connect_serial(device_name=sonar_port1)
    sonar_driver1.set_ping_interval(ping_interval)
    #sonar_driver1.set_range(0,10000) #In mm
    sonar_port2 = node.declare_parameter("sonar1/sonar_port", "/dev/ttyACM1").value
    sonar_driver2 = Ping1D()
    sonar_driver2.connect_serial(device_name=sonar_port2)
    #sonar_driver2.set_range(0,10000) #In mm
    sonar_driver2.set_ping_interval(ping_interval)

    sonar_port3 = node.declare_parameter("sonar2/sonar_port", "/dev/ttyUSB0").value
    sonar_driver3 = Ping1D()
    sonar_driver3.connect_serial(device_name=sonar_port3)
    sonar_driver3.set_ping_interval(ping_interval)
    
    while rclpy.ok():
        sonar_msg = ThreeSonarDepth()
        
        # Retrieve distance and confidence from each sonar
        data_1 = sonar_driver1.get_distance_simple()
        data_2 = sonar_driver2.get_distance_simple()
        data_3 = sonar_driver3.get_distance_simple()

        # Ensure the data is not None before accessing
        if data_1 is not None:
            sonar_msg.header.stamp = node.get_clock().now().to_msg()
            sonar_msg.distance_1 = float(data_1["distance"])
            sonar_msg.confidence_1 = float(data_1["confidence"])
        
        if data_2 is not None:
            sonar_msg.distance_2 = float(data_2["distance"])
            sonar_msg.confidence_2 = float(data_2["confidence"])

        sonar_msg.distance_3 = float(data_3["distance"])
        sonar_msg.confidence_3 = float(data_3["confidence"])

        # Publish the message
        pub_sonar.publish(sonar_msg)
        #rclpy.logging.get_logger("single_beam_sonar_node").info(f"Published sonar data: {sonar_msg}")

        # Sleep to control the publishing rate
        rclpy.spin_once(node, timeout_sec=0.01)
    
    # Cleanup and shutdown
    node.destroy_node()
    rclpy.shutdown()



if __name__ == "__main__":
    try:
        main()
    except rclpy.exceptions.ROSInterruptException:
        pass

#Summary of Changes
#Addition of None Check:

#In the newest version, before accessing data_1 and data_2, the code now checks if these variables are None. If they are not None, the script proceeds to extract and process the data. This change prevents errors when the sonar data might not be available.
#Error Prevention:

#The primary change is the inclusion of checks to ensure the script doesn't attempt to access a NoneType object, which would result in a runtime error. This improves the robustness of the code, especially in scenarios where the sonar data might not be consistently available.


        

        
