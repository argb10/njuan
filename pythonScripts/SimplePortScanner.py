# -*- coding: utf-8 -*-
"""
Created on Sun Apr 26 11:17:27 2020

@author: sentdex
link: https://www.youtube.com/watch?v=szm3camsf8k
"""
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server = 'pythonprogramming.net'

def pscan(port):
    try:
        s.connect((server, port))
        return True
    except:
        return False

for x in range(80,445):
    if pscan(x):
        print('Port ',x,' is open')
