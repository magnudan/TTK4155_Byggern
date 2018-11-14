import socket
import serial
from time import sleep

HOST = 'localhost'
PORT = 65433

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind((HOST, PORT))
print("listening to port", PORT)
sock.listen()
conn, addr = sock.accept()
print("connected to", addr)

ser = serial.Serial('/dev/ttyUSB0', bytesize=8, stopbits=2, baudrate=9600)
print("opened serial connection")
while True:
    data = conn.recv(1024)
    print("recieved data from client", data)
    ser.write(data)
    sleep(1)
    print("relayed data to MCU", data)
