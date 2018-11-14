import socket
from time import sleep

HOST = 'localhost'
PORT = 65433

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect((HOST, PORT))
    print("connected to", HOST, PORT)
    while True:
        message = b'c'
        sock.send(message)
        print("sent message", message)
        sleep(1)
