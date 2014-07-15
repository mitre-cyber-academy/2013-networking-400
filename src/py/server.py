import socket
import hashlib
import time

#Create a UDP socket
servSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#Bind to localhost on port 12345
# (change this to the system hostname to make sure the port is accessible 
# externally)
servSocket.bind(('localhost', 12345))
#These are the accepted values for the login:
good_key = "96c70ab05a922178e0668ba5402160d7"
goodUName = "Smith"
goodPWord = "IronFan30"
#Continuously listen for connections:
while(True):
	#Get data from (a) client
	data, addr = servSocket.recvfrom(4096)
	#XOR with the good key and see if it looks right
	catString = ''.join(chr(ord(a) ^ ord(b)) for a, b in zip(data, good_key))
	#Try and split their message
	arrVals = catString.split('_')
	#Get the current time for a (dummy) return message
	tmpTime = "%s" % time.time() 
	#Hash the time for the bad return
	m = hashlib.md5()
	m.update(tmpTime)

	#Default return value is the bad one
	retVal = m.digest()

	#First, make sure they have a full message delimited by '_'
	if(len(arrVals) == 3):
		#Split up the given values
		uName, pWord, currTime = arrVals
		#And check them against the good ones
		if(uName == goodUName and pWord == goodPWord):
			#Then, build the 'good' response - a SHA256 hash
			# of the given time code and the CD key
			sh = hashlib.sha256()
			sh.update(currTime + "_" + good_key)
			retVal = sh.digest()
			print "Successful login"
		else:
			print "Valid message format, bad data"
	else:
		print "Invalid message format"
	servSocket.sendto(retVal, addr)
