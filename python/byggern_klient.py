import socket
import time

UDP_IP = "10.24.37.28"
UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:
    message = b'd'
    sock.sendto(message, (UDP_IP, UDP_PORT))
    print("sent message", message, "to", UDP_IP+":"+str(UDP_PORT))
    time.sleep(1)


