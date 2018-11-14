import serial
from time import sleep

ser = serial.Serial('/dev/ttyUSB0', stopbits=2, bytesize=8, baudrate=9600)
print(50*"-"+"\nOpening serial on:", ser.name,'\n', 50*"-", sep='')
while True:
    # ser.write(b'echo\r\n')
    sleep(0.1)
    response = ser.readline()
    print(response.decode("utf-8"), end='')
    sleep(1)
