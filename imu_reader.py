import smbus
import time
import math

# MPU6050 I2C address
MPU6050_ADDR = 0x68

# Registers for MPU6050
PWR_MGMT_1 = 0x6B  # Power management register
ACCEL_XOUT_H = 0x3B  # Accelerometer data registers
ACCEL_XOUT_L = 0x3C
ACCEL_YOUT_H = 0x3D
ACCEL_YOUT_L = 0x3E
ACCEL_ZOUT_H = 0x3F
ACCEL_ZOUT_L = 0x40
GYRO_XOUT_H = 0x43  # Gyroscope data registers
GYRO_XOUT_L = 0x44
GYRO_YOUT_H = 0x45
GYRO_YOUT_L = 0x46
GYRO_ZOUT_H = 0x47
GYRO_ZOUT_L = 0x48

# Create an I2C bus object
bus = smbus.SMBus(0)  # Bus 1 for most Raspberry Pi / Linux systems

# Function to initialize MPU6050
def init_mpu6050():
    # Wake up the MPU6050 (default is sleep mode)
    bus.write_byte_data(MPU6050_ADDR, PWR_MGMT_1, 0)
    time.sleep(0.1)  # Wait a moment for it to wake up

# Function to read a 16-bit value from two 8-bit registers
def read_word(reg):
    high = bus.read_byte_data(MPU6050_ADDR, reg)
    low = bus.read_byte_data(MPU6050_ADDR, reg + 1)
    value = (high << 8) + low
    if value >= 0x8000:  # If the value is negative
        value -= 65536
    return value

# Function to read accelerometer and gyroscope data and convert to SI units
def read_sensor_data():
    # Read accelerometer data
    accel_x = read_word(ACCEL_XOUT_H)
    accel_y = read_word(ACCEL_YOUT_H)
    accel_z = read_word(ACCEL_ZOUT_H)

    # Read gyroscope data
    gyro_x = read_word(GYRO_XOUT_H)
    gyro_y = read_word(GYRO_YOUT_H)
    gyro_z = read_word(GYRO_ZOUT_H)

    # Convert accelerometer raw values to m/s² (±2g range)
    accel_x_ms2 = accel_x / 16384.0 * 9.81
    accel_y_ms2 = accel_y / 16384.0 * 9.81
    accel_z_ms2 = accel_z / 16384.0 * 9.81

    # Convert gyroscope raw values to rad/s (±250°/s range)
    gyro_x_rad_s = gyro_x / 131.0 * math.pi / 180.0
    gyro_y_rad_s = gyro_y / 131.0 * math.pi / 180.0
    gyro_z_rad_s = gyro_z / 131.0 * math.pi / 180.0

    return accel_x_ms2, accel_y_ms2, accel_z_ms2, gyro_x_rad_s, gyro_y_rad_s, gyro_z_rad_s

# Initialize the MPU6050
init_mpu6050()

# Loop to continuously read and display data
while True:
    accel_x_ms2, accel_y_ms2, accel_z_ms2, gyro_x_rad_s, gyro_y_rad_s, gyro_z_rad_s = read_sensor_data()

    # Print out the data in SI units
    print(f"Accelerometer X: {accel_x_ms2:.3f} m/s²")
    print(f"Accelerometer Y: {accel_y_ms2:.3f} m/s²")
    print(f"Accelerometer Z: {accel_z_ms2:.3f} m/s²")
    print(f"Gyroscope X: {gyro_x_rad_s:.3f} rad/s")
    print(f"Gyroscope Y: {gyro_y_rad_s:.3f} rad/s")
    print(f"Gyroscope Z: {gyro_z_rad_s:.3f} rad/s")

    #time.sleep(0.005)  # Delay between readings

