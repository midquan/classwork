import socket
import time 

HOST = '192.168.1.10'
PORT = 10589

def main():
    outputfile = open("output","a")
    current = str(counter) + " " + line 
    outputfile.write(current)
    print(current)
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
      s.connect((HOST, PORT))
      skeleton = 'Passepartout'.encode()
      s.sendall(skeleton)
      username = 'midquan'.encode() 
      data = s.recv(2048)
      s.sendall(username)
      data2 = s.recv(2048)
      password = 'SheffieldWednesday'.encode()
      s.sendall(password)
      data3 = s.recv(2048)
    #print('Received', repr(data))
    print(repr(data2))
    print(repr(data3))
    outputfile.write(repr(data2))
    outputfile.write("\n")
    outputfile.write(repr(data3))
    outputfile.write("\n")
    outputfile.close()
   
if __name__ == '__main__':
    main()
