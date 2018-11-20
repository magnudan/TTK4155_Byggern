IP = "10.100.23.213"
SOCKET = 6789

import socket
import keyboard

keymap = {
	('down', 'a'): 		'a',
	('up',	 'a'): 		'b',
	('down', 'd'): 		'c',
	('up',	 'd'): 		'd',
	('down', 'j'): 		'e',
	('up',	 'j'): 		'f',
	('down', 'l'): 		'g',
	('up',	 'l'): 		'h',
	('down', 'space'): 	'i',
	('up',	 'space'): 	'j',
}

from time import sleep
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
keys_down = []

while True:
	event = keyboard.read_event()
	key = event.name
	key_type = event.event_type
	if key_type == "down" and key not in keys_down:
		keys_down.append(key)
		message = keymap[(key_type, key)]
		sock.sendto(bytes(message, 'utf-8'), (IP, SOCKET))
		print("->", key, key_type)
	if key_type == "up" and key in keys_down:
		keys_down.remove(key)
		message = keymap[(key_type, key)]
		sock.sendto(bytes(message, 'utf-8'), (IP, SOCKET))
		print("->", key, key_type)

