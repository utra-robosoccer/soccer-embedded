import socket    
import os
f = os.popen('ifconfig eth0 | grep "inet\ addr" | cut -d: -f2 | cut -d" " -f1')
IPAddr=f.read()


#hostname = socket.gethostname()    
#IPAddr = socket.gethostbyname(hostname)  

#print("Your Computer Name is:" + hostname)    
#print("Your Computer IP Address is:" + IPAddr)
def main():
	file = open(r"ip.txt", "w+")
	file.write(IPAddr)
	file.close()

if __name__ == '__main__':
	main()