from pynput import keyboard
import socket
import json

UDP_IP = "192.168.43.235"
UDP_PORT = 4320
btn_l = False
btn_r = False
btn_b = False
btn_f = False
MESSAGE = {}

def sendUDP():
    MESSAGE['btn_b'] = btn_b
    MESSAGE['btn_f'] = btn_f
    MESSAGE['btn_l'] = btn_l
    MESSAGE['btn_r'] = btn_r
    print (json.dumps(MESSAGE))
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.sendto(json.dumps(MESSAGE), (UDP_IP, UDP_PORT))

def on_press(key):
    global btn_b,btn_f,btn_l,btn_r
    try:
        if (key.char == 'a'):
            btn_l = True
            sendUDP()
        elif (key.char == 'w'):
            btn_f = True
            sendUDP()
        elif (key.char == 's'):
            btn_b = True
            sendUDP()
        elif (key.char == 'd'):
            btn_r = True
            sendUDP()
    except AttributeError:
        do_nothing = 1

def on_release(key):
    global btn_b,btn_f,btn_l,btn_r
    try:
        if (key.char == 'a'):
            btn_l = False
        elif (key.char == 'w'):
            btn_f = False
        elif (key.char == 's'):
            btn_b = False
        elif (key.char == 'd'):
            btn_r = False
    except AttributeError:
        do_nothing = 1

with keyboard.Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()
