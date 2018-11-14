import socket
import time

UDP_IP = "127.0.0.1"
UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:
    message = b'd'
    sock.sendto(message, (UDP_IP, UDP_PORT))
    print("sent message", message)
    time.sleep(1)


