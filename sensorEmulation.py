import serial
import struct
import time
import hashlib

# Configure serial port
SERIAL_PORT = "/dev/ttyACM0"
BAUD_RATE = 115200

# Function to get CPU temperature
def get_cpu_temperature():
    try:
        with open("/sys/class/thermal/thermal_zone0/temp", "r") as f:
            temp_milli = int(f.read().strip())
        return temp_milli / 1000.0  # Convert to Celsius
    except FileNotFoundError:
        return 50.0  # Return a default value if not available

# Function to calculate CRC (simple checksum)
def calculate_crc(data):
    return sum(data) & 0xFF

# Open serial port
with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
    print(f"Sensor emulator running on {SERIAL_PORT} at {BAUD_RATE} baud...")
    
    while True:
        if ser.in_waiting > 0:
            request_byte = ser.read(1)
            
            if request_byte == b'\xAA':  # Check for request byte
                cpu_temp = get_cpu_temperature()
                response = struct.pack("<f", cpu_temp)  # Serialize float as 4 bytes (little-endian)
                crc = calculate_crc(response)  # Compute CRC
                ser.write(response + bytes([crc]))  # Send response with CRC
                print(f"Sent temperature: {cpu_temp:.2f}°C, CRC: {crc:#04x}")
            
        time.sleep(0.1)  # Avoid busy-waiting