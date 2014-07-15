CC=gcc
CFLAGS=-c `sdl-config --cflags` 
LIBS=`sdl-config --libs` -lcrypto


all: Client.bin

Client.bin: client.o
	$(CC) -o Client.bin client.o $(LIBS)

client.o: client.c
	$(CC) client.c $(CFLAGS)

clean:
	rm *.o *.bin
