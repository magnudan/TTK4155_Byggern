import socket
import serial

IP = ""
PORT = 6789

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((IP, PORT))

ser = serial.Serial('/dev/ttyUSB0', baudrate=9600, stopbits=2)

while True:
	data, addr = sock.recvfrom(1024)
	print("got:", data, "\t", "from", addr)
	ser.write(data)
	print(ser.readline())
