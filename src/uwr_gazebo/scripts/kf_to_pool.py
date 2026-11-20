#!/usr/bin/env python3
"""Convert the KF's wall-distance pose (/pose_topic) into pool coordinates (origin is centre of pool, following ENU).

The KF state is distances from the sonars to the front wall, left wall and floor.
Valid while the robot keeps its spawn yaw (90 deg, facing pool +y) and does not rotate.
"""
import math

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseStamped, TransformStamped
from tf2_ros import TransformBroadcaster


class KfToPool(Node):
    def __init__(self):
        super().__init__('kf_to_pool')
        # tank geometry: where the surfaces the sonars point at are, in the world frame
        self.front_wall_y = self.declare_parameter('front_wall_y', 5.0).value
        self.left_wall_x = self.declare_parameter('left_wall_x', -2.5).value
        self.floor_z = self.declare_parameter('floor_z', -2.0).value
        self.sonar_drop = self.declare_parameter('sonar_drop', 1.0).value   # sonars below base_link
        yaw = self.declare_parameter('yaw', math.pi / 2).value

        # robot orientation is fixed (see docstring): yaw-only quaternion
        self.qz, self.qw = math.sin(yaw / 2), math.cos(yaw / 2)

        self.create_subscription(PoseStamped, '/pose_topic', self.on_kf_pose, 10)
        self.pub = self.create_publisher(PoseStamped, '/kf/pool_pose', 10)
        self.tf = TransformBroadcaster(self)

    def on_kf_pose(self, msg):
        surge = msg.pose.position.x
        sway = msg.pose.position.y
        heave = msg.pose.position.z

        # x, y, z of base_link in the world frame (+x right, +y forward, +z up)
        x = self.left_wall_x + sway 
        y = self.front_wall_y - surge
        z = self.floor_z + self.sonar_drop + heave

        out = PoseStamped()
        out.header.stamp = msg.header.stamp        # keep the KF's (sim) time
        out.header.frame_id = 'world'
        out.pose.position.x, out.pose.position.y, out.pose.position.z = x, y, z
        out.pose.orientation.z, out.pose.orientation.w = self.qz, self.qw
        self.pub.publish(out)

        # you write: publish the same pose as TF world -> base_link_kf
        t = TransformStamped()
        t.header.stamp = msg.header.stamp
        t.header.frame_id = 'world'
        t.child_frame_id = 'base_link_kf'
        t.transform.translation.x, t.transform.translation.y, t.transform.translation.z = x, y, z
        t.transform.rotation.z, t.transform.rotation.w = self.qz, self.qw
        self.tf.sendTransform(t)

def main():
    rclpy.init()
    rclpy.spin(KfToPool())
    rclpy.shutdown()


if __name__ == '__main__':
    main()
