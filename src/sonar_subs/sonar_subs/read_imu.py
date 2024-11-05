import rclpy
from rclpy.node import Node
import serial
from sensor_msgs.msg import Imu
from std_msgs.msg import Header

class IMUSerialNode(Node):
    def __init__(self):
        super().__init__('imu_serial_node')
        self.publisher = self.create_publisher(Imu, 'lcimu/data', 10)
        
        # Change '/dev/ttyUSB0' and '115200' to match your setup
        try:
            self.serial_port = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
        except serial.SerialException as e:
            self.get_logger().error(f"Failed to open serial port: {e}")
            raise SystemExit(1)
        
        self.timer = self.create_timer(0.1, self.read_serial_data)

    def read_serial_data(self):
        try:
            # Read line from serial port
            raw_data = self.serial_port.readline()
            line = raw_data.decode('utf-8', errors='ignore').strip()  # Handle non-UTF-8 gracefully
            
            if line:  # Ensure the line is not empty
                # Debug print for raw data received
                self.get_logger().info(f"Raw data: {line}")
                
                # Split the data assuming format: ax,ay,az,gx,gy,gz
                data = line.split(',')
                if len(data) == 6:
                    ax, ay, az, gx, gy, gz = [int(val) for val in data]

                    # Create and populate the IMU message
                    imu_msg = Imu()
                    imu_msg.header = Header()
                    imu_msg.header.stamp = self.get_clock().now().to_msg()
                    imu_msg.header.frame_id = 'imu_link'

                    # Populate linear acceleration (adjust scaling as necessary)
                    imu_msg.linear_acceleration.x = ax / 1638.40
                    imu_msg.linear_acceleration.y = ay / 1638.40
                    imu_msg.linear_acceleration.z = az / 1638.40

                    # Populate angular velocity (adjust scaling as necessary)
                    imu_msg.angular_velocity.x = gx / 131.0
                    imu_msg.angular_velocity.y = gy / 131.0
                    imu_msg.angular_velocity.z = gz / 131.0

                    # Publish the IMU data
                    self.publisher.publish(imu_msg)
                else:
                    self.get_logger().warn('Invalid data format received: ' + line)
        except UnicodeDecodeError:
            self.get_logger().warn('Received non-UTF-8 data, ignoring it.')

def main(args=None):
    rclpy.init(args=args)
    node = IMUSerialNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
