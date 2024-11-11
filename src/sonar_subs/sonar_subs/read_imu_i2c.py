#https://github.com/allanbian1017/i2c-ch341-usb.git
import rclpy
from rclpy.node import Node
import smbus
from sensor_msgs.msg import Imu
from std_msgs.msg import Header
import time

class IMUI2CNode(Node):
    def __init__(self):
        super().__init__('imu_i2c_node')
        self.publisher = self.create_publisher(Imu, 'lcimu/data', 10)

        # I2C bus initialization
        self.bus = smbus.SMBus(7)  # 1 is the I2C bus number (use 0 for Raspberry Pi)
        self.device_address = 0x68  # MPU6050 I2C address

        # Initialize the MPU6050
        self.init_mpu6050()
        self.get_logger().info(f"Initialized")
        # Timer to read data at 10Hz
        self.timer = self.create_timer(0.001, self.read_i2c_data)

    def init_mpu6050(self):
        # Wake up the MPU6050 (it starts in sleep mode)
        self.bus.write_byte_data(self.device_address, 0x6B, 0)  # 0x6B is the Power Management 1 register

    def read_i2c_data(self):
        try:
            # Read accelerometer and gyroscope data from MPU6050
            ax = self.read_signed_word(0x3B)  # Accelerometer X-axis
            ay = self.read_signed_word(0x3D)  # Accelerometer Y-axis
            az = self.read_signed_word(0x3F)  # Accelerometer Z-axis

            gx = self.read_signed_word(0x43)  # Gyroscope X-axis
            gy = self.read_signed_word(0x45)  # Gyroscope Y-axis
            gz = self.read_signed_word(0x47)  # Gyroscope Z-axis

            # Debug print for raw data received
            #self.get_logger().info(f"Raw data: ax={ax/1638.4}, ay={ay/1638.4}, az={az/1638.4}, gx={gx/131}, gy={gy/131}, gz={gz/131}")

            # Create and populate the IMU message
            imu_msg = Imu()
            imu_msg.header = Header()
            imu_msg.header.stamp = self.get_clock().now().to_msg()
            imu_msg.header.frame_id = 'imu_link'

            # Populate linear acceleration (adjust scaling as necessary)
            imu_msg.linear_acceleration.x = ax / 1638.40  # Convert to m/s², assuming ±2g scale
            imu_msg.linear_acceleration.y = ay / 1638.40
            imu_msg.linear_acceleration.z = az / 1638.40

            # Populate angular velocity (adjust scaling as necessary)
            imu_msg.angular_velocity.x = gx / 131.0  # Convert to rad/s, assuming ±250°/s scale
            imu_msg.angular_velocity.y = gy / 131.0
            imu_msg.angular_velocity.z = gz / 131.0

            # Publish the IMU data
            self.publisher.publish(imu_msg)
        except Exception as e:
            self.get_logger().error(f"Error reading I2C data: {e}")

    def read_signed_word(self, reg):
        # Read two bytes and combine them into a 16-bit signed value
        high = self.bus.read_byte_data(self.device_address, reg)
        low = self.bus.read_byte_data(self.device_address, reg + 1)
        value = (high << 8) + low

        # Convert to signed 16-bit value
        if value >= 32768:
            value -= 65536
        return value

def main(args=None):
    rclpy.init(args=args)
    node = IMUI2CNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
