CC=gcc
CFLAGS=-Wall -c `sdl-config --cflags`
LIBS=-lcrypto `sdl-config --libs`

all: Client.bin 


Client.bin: client.o
	$(CC) -o Client.bin client.o $(LIBS)

client.o: client.c
	$(CC) $(CFLAGS) client.c

clean: 
	rm *.bin *.o
