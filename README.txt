Name: Cypsela 2013

Description: ``Thank you for installing Cypsela 2013. Before you can play
this award-winning plant evolution simulator, please make sure you enter
in the username, password and CD key given on your box and have an active
Internet connection.'' You've had enough of this DRM crap. Your buddy has
provided a packet cap of his game when he connected, along with his 
credentials. Maybe you can get back at those money-grubbing megacorps in 
your own little way.

How to Solve: The first thing to note is the server name that the server is
trying to connect to. This can be found by running strings on the program
and seeing 'genericgameserver.com' in the results. This indicates that the
user should set up a fake game server on localhost by using their /etc/hosts
file (or similar). That way, when the client tries to resolve the name, it
instead points to localhost. The port can be deduced from either the pcap
or strings. The user is given the correct CD key, username and password and
just needs to reverse engineer the protocol. This can be begun by looking at
the traffic passed between the client and server (via the pcap). The first 
thing that the user may attempt is to simply replay the message that was sent
to the other client program. This won't work, as the client sends a bit of 
nonce (the current time in seconds) in addition to the credentials, so the
user actually has to try a bit. Luckily for them, the 'encryption' that was
used to hide the message was just xor via the CD key. The user should then
be able to `decrypt' the message going to the server and observe that it is
a string composed of the username_password_time. As the username and 
password are known to both ends of the system ahead of time, the time is the
only thing which changes from session to log-in to log-in. This, combined
with the fact that the CD key is also not transmitted, may indicate that these
two data are used in a valid return message. Between a strings of the client
and an examination of the length of the return message, the user may notice
that the response is a SHA256 hash. Based on the format of the original 
message (thing1_thing2), they may think to combine the various variables
in a SHA hash and send them back to the server.

A valid server program is included in src/py/server.py. To show a proof of
the solution, configure your hosts file to contain the line:

127.0.0.1	genericgameserver.com

and run the server program. Then, run the client. If all is successful, a 
little SDL program will draw the flag on the screen, then exit. Otherwise,
an error message will be generated.

What to distribute: 
dist/Client.bin - a 64 bit Linux executable which depends on the OpenSSL crypto
	and SDL libraries.

login.pcap - a pcap of a session between the client and the server programs,
	showing relevant UDP traffic.

Flag: MCA-121C412D
