import socket
import hashlib
import time

servSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
servSocket.bind(('localhost', 12345))
good_key = "96c70ab05a922178e0668ba5402160d7"
goodUName = "Smith"
goodPWord = "IronFan30"
while(True):
	data, addr = servSocket.recvfrom(4096)
	catString = ''.join(chr(ord(a) ^ ord(b)) for a, b in zip(data, good_key))
	print data
	arrVals = catString.split('_')
	tmpTime = "%s" % time.time() 

	#Make the default return value an MD5 of the time
	m = hashlib.md5()
	m.update(tmpTime)

	retVal = m.digest()

	if(len(arrVals) == 3):
		uName, pWord, currTime = arrVals
		print arrVals
		if(uName == goodUName and pWord == goodPWord):
			sh = hashlib.sha256()
			sh.update(currTime + " " + good_key)
			retVal = sh.digest()
			print "Plaintext: '%s'" % (currTime + " " + good_key)
			print "everything was fine"
			print "Hashval: '%s'" % retVal
	servSocket.sendto(retVal, addr)
	print addr
	print data
