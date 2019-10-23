import sys 
import socket


#Usage: python3 ports.py [ports] [ip adress] [skeleton key] [user]
#HOST = '192.168.1.10'
#PORT = 10589

def main(): 
   listofports = sys.argv[1]
   port = open(listofports,"r")
   
   ip = sys.argv[2]
   skel = sys.argv[3]
   for line in port:
      currport = line[27:32] 
      print (currport)
      currport = int(currport)
      with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
         s.connect((ip, currport))
         skeleton = skel.encode()
         s.sendall(skeleton)
         user = sys.argv[4]
         username = user.encode() 
         data = s.recv(2048)
         s.sendall(username)
         data2 = s.recv(2048)
         print (data2)
         if (data2 == "Password: "):
            found = open("FoundPort","w")
            found.write(data2)

if __name__ == '__main__':
    main()