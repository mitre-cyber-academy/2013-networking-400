import socket
import pygame as pg
from ConfigParser import ConfigParser
import hashlib
import time


s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#currGameId = "ee5bbb297de159a92d4c603ed214548a"
fp = ConfigParser()
fp.read('game.cfg')
key = fp.get('UserData', 'CDKey')
uName = fp.get('UserData', 'UName')
pWord = fp.get('UserData', 'PWord')
'''
uName = 'Smith'
pWord = 'IronFan30'
goodKey = "96c70ab05a922178e0668ba5402160d7"
'''
#currTime = "%s" % int(time.time())
currTime = "1369345567"
print "Time: ", currTime
msg = uName + "_" + pWord + "_" + currTime

#uName = raw_input("Please enter your username: ")
codeMsg = ''.join(chr(ord(a) ^ ord(b)) for a, b in zip(msg, key))

print "".join("%d\n" % ord(c) for c in codeMsg)
print "Code message sent:", codeMsg
s.connect(("genericgameserver.com", 12345))
s.send(codeMsg)
print "Message sent:", msg
print "receiving:"
rData = s.recv(4096)
sh = hashlib.sha256()
sh.update(currTime + " " + key)
oData = sh.digest()

'''
if(rData == oData):
	pg.init()
	size = (300, 300)
	black = (0,0,0)
	white = (0xFF, 0xFF, 0xFF)
	screen = pg.display.set_mode(size)
	screen.fill(black)
	pg.display.flip()
	for i in range(1000):
		screen.fill(black)
		rectLoc = (i % 300, i % 100, i % 300 + 5, i % 100 + 5)
		pg.draw.rect(screen, white, rectLoc)
		pg.time.wait(10)
		pg.display.update()

'''

print "Expected:", oData
print "Got: ", rData

print (rData == oData)


s.close()
