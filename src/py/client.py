import socket
import pygame as pg
from ConfigParser import ConfigParser
import hashlib
import time


#Create a socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#Parse in the game configuration data
fp = ConfigParser()
fp.read('game.cfg')
key = fp.get('UserData', 'CDKey')
uName = fp.get('UserData', 'UName')
pWord = fp.get('UserData', 'PWord')

#Use the current time as a token
currTime = "%s" % int(time.time())

#Build the login message:
msg = uName + "_" + pWord + "_" + currTime

#XOR with the CD key
codeMsg = ''.join(chr(ord(a) ^ ord(b)) for a, b in zip(msg, key))

#Connect to the server and send the message:
s.connect(("genericgameserver.com", 12345))
s.send(codeMsg)

#Read the server response:
rData = s.recv(4096)

#Generate what we thing the right response should be
# (hash of time and the cd key)
sh = hashlib.sha256()
sh.update(currTime + "_" + key)
oData = sh.digest()

if(rData == oData):
	print "Successful login. Flag is MCA-########"
else:
	print "Incorrect login. Please correct your configuration file."

#Clean-up the socket
s.close()
