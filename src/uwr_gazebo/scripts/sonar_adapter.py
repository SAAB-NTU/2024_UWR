#!/usr/bin/env python3
"""Turn the three simulated sonar LaserScans into one ThreeSonarDepth on /sbs."""
import math

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
from sonar_msgs.msg import ThreeSonarDepth

SONARS = {1: 'sonar_surge', 2: 'sonar_sway', 3: 'sonar_heave'}

class SonarAdapter(Node):
    def __init__(self):
        super().__init__('sonar_adapter')
        self.latest = {i: None for i in SONARS}   # creates a dictionary that stores the latest reading from each sonar

        for i, name in SONARS.items():
            self.create_subscription(
                LaserScan, f'/sonar/{name}',
                lambda msg, i=i: self.on_sonar_callback(i, msg), 10)

        self.pub = self.create_publisher(ThreeSonarDepth, '/sbs', 10)
        self.create_timer(1.0 / 20.0, self.publish)   # 20 Hz, same as the sonars

    def on_sonar_callback(self, i, msg):
        self.latest[i] = shortest_range(msg)

    def publish(self):
        out = ThreeSonarDepth()
        out.header.stamp = self.get_clock().now().to_msg()
        for i, r in self.latest.items():
            if r is None:                          # no reading, tell the KF not to trust it
                distance_mm, confidence = 0.0, 0.0
            else:
                distance_mm, confidence = r * 1000.0, 100.0
            setattr(out, f'distance_{i}', distance_mm)
            setattr(out, f'confidence_{i}', confidence)            
        self.pub.publish(out)

def shortest_range(msg):
    """Smallest real hit in the scan, in metres, or None if nothing was hit."""
    shortest = None
    for r in msg.ranges:
        if not math.isfinite(r) or r < msg.range_min or r > msg.range_max:
            continue                      # if reading is outside range, skip
        if shortest is None or r < shortest:
            shortest = r
    return shortest

def main():
    rclpy.init()
    rclpy.spin(SonarAdapter())
    rclpy.shutdown()

if __name__ == '__main__':
    main()