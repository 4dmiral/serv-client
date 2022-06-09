import socket
import sys
import time

HOST, PORT = '127.0.0.1', 1984


def connect_to_server():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    counter = 1
    while True:
        print("\n")
        print("--- Message "+str(counter)+" ---")
        message = input("Input: ")
        s.send(bytes(message, 'utf-8'))
        data = s.recv(40)
        if data:
            try:
                print(data.decode("utf-8"))
            except UnicodeDecodeError:
                print("A server-end error likely occurred")
            counter += 1
        else:
            break

