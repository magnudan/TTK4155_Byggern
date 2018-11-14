import serial
from time import sleep
import socket


# Creating UDP recieveing socket
UDP_IP = "127.0.0.1"
UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))
print("> Opened socket on:", UDP_PORT)

# Creating Serial port for chip
ser = serial.Serial('/dev/ttyUSB0', stopbits=2, bytesize=8, baudrate=9600)
print("> Opened serial on:", ser.name)


while True:
    data, ip_data = sock.recvfrom(256)
    print(data)
    sleep(0.1)
    ser.write(data)
    response = ser.readline()
    print(response.decode("utf-8"), end='')
    sleep(1)
