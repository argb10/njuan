# -*- coding: utf-8 -*-
"""
Created on Sun Apr 26 11:17:27 2020

@author: argb10

Core code retrive from    
sentdex
link: https://www.youtube.com/watch?v=szm3camsf8k
"""
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server = '127.0.0.1'

def pscan(port):
    try:
        s.connect((server, port))
        return True
    except:
        return False
    
openports = []
for port in range(1, 65535):
    if pscan(port):
        print('Port ',port,' is open')
        openports.append(port)
    else:
        print('Port ',port,' is closed')

print(openports)
