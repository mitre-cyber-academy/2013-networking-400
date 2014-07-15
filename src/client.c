#include <openssl/sha.h>
#include <openssl/crypto.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <netdb.h>
#include "SDL.h"


int main(int argc, char* argv[])
{
	//Check for arguments
	if(argc < 4)
	{
		printf("Usage: %s <userName> <passWord> <CDKey>\n", argv[0]);
		exit(0);
	}
	//Initialize pointers to arguments with reasonable names
	char* uName = argv[1];
	char* pWord = argv[2];
	char* key = argv[3];
	//Get the current time, to be used later
	unsigned int currTime = time(NULL);
	//unsigned int currTime = 1369345567;
	//Get the length of the two arguments, plus two for underscores 
	int len = strlen(uName) + strlen(pWord) + 2;
	//Add 10 for the length of the time, 1 for the null-term
	int maxLen = len + 11;
	//Get some space for our (xor'd) string
	char* tokenStr = (char*) malloc(maxLen * sizeof(char));

	//Set up a count var for later
	int count;
	//And a socket file descriptor
	int sock;

	//Memory for connecting to the server
	struct sockaddr_in;
	struct in_addr;
	struct addrinfo hints;
	struct addrinfo* results;
	char readBuff[4096];

	//Our game server is at genericgameserver.com on port 12345
	char* hostName = "genericgameserver.com";
	char* port = "12345";
	
	//This will hold our version of the hash:
	char oData[SHA256_DIGEST_LENGTH];

	//get the length of the expected message:
	int msgLen = 1 + strlen(key) + 11;

	//This will hold our plaintext:
	char* oMsgBuff;

	//Build the plaintext string:
	snprintf(tokenStr, maxLen, "%s_%s_%d", uName, pWord, currTime);

	//'encrypt' the string with our CD key, keeping the null term
	for(count = 0; count < maxLen - 1; count ++)
	{
		tokenStr[count] = tokenStr[count] ^ key[count];
	}
	

	//Null out the hints structure, as we don't know anything yet:
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = 0;
	getaddrinfo(hostName, port, &hints, &results);
	sock = socket(results->ai_family, results->ai_socktype, 
			results->ai_protocol);
	if(sock < 0)
	{
		perror("Couldn't create socket");
		exit(2);
	}

	//Connect to the server, or die trying
	if(connect(sock, results->ai_addr, results->ai_addrlen) < 0)
	{
		perror("Couldn't connect");
		exit(1);
	}
	//We're connected, write our message
	write(sock, tokenStr, maxLen - 1);
	//Now, read from the socket:
	read(sock, readBuff, 4096);

	
	//Allocate our plaintext memory, then build it in:
	oMsgBuff = (char*) malloc(sizeof(unsigned char) * msgLen);
	snprintf(oMsgBuff, msgLen, "%d %s", currTime, key);

	//Hashing related things:
	SHA256((unsigned const char*) oMsgBuff, strlen(oMsgBuff), (unsigned char*) oData);

	for(count = 0; count < SHA256_DIGEST_LENGTH; count ++)
	{
		if(oData[count] != readBuff[count])
		{
			break;
		}
	}
	if(count == SHA256_DIGEST_LENGTH)
	{
		//Play "Game"
		//Initialize SDL:
		if(SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
			exit(1);
		}
		SDL_Surface *screen;
		screen = SDL_SetVideoMode(300, 300, 16, SDL_SWSURFACE);
		if(screen == NULL)
		{
			fprintf(stderr, "Unable to set screen: %s\n", SDL_GetError());
			exit(2);
		}
		//This will be be a rectangle describing the screen, a 300x300 px box
		SDL_Rect screenRect;
		screenRect.x = screenRect.y = 0;
		screenRect.w = screenRect.h = 300;
		Uint32 black = SDL_MapRGB(screen->format, 0,0,0);
		Uint32 white = SDL_MapRGB(screen->format, 0xFF,0xFF,0xFF);
		SDL_FillRect(screen, &screenRect, black);
		int h;
		int bl = 165;
		int tl = 135;
		int tmpx, tmpy;
		//Character spacing
		int chrSpc = 10;
		h = bl - tl;
		SDL_Rect lr;
		lr.h = lr.w = 3;
		lr.x = 10;
		//Draw the letters:
		//m
		for(lr.y = tl; lr.y < bl; lr.y ++)
		{
			SDL_FillRect(screen, &lr, white);
		}
		for(lr.y = tl; lr.y < h / 2 + tl; lr.y ++)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		for(; lr.y > tl; lr.y --)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		for(lr.y = tl; lr.y < bl; lr.y ++)
		{
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;
		//C
		tmpx = lr.x;
		for(lr.y = tl + h/2; lr.y < bl; lr.y ++)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x = tmpx;
		for(lr.y = tl + h/2; lr.y > tl; lr.y --)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;
		//A
		for(lr.y = bl; lr.y > tl; lr.y -= 2)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
			if(lr.y <= tl + h/2)
			{
				tmpy = lr.y;
				lr.y = tl + h/2;
				SDL_FillRect(screen, &lr, white);
				lr.y = tmpy;
			}
		}
		for(lr.y = tl; lr.y < bl; lr.y += 2)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
			if(lr.y <= bl - h/2)
			{
				tmpy = lr.y;
				lr.y = tl + h/2;
				SDL_FillRect(screen, &lr, white);
				lr.y = tmpy;
			}
		}
		lr.x += chrSpc;
		//-
		tmpx = lr.x;
		for(lr.y = tl + h/2; lr.x < tmpx + chrSpc; lr.x ++)
		{
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;
		//1
		for(lr.y = tl; lr.y < bl; lr.y ++)
		{
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;
		//2
		//A 2 is a backwards C plus a straight line on the bottom:
		tmpx = lr.x;
		for(lr.y = bl; lr.y > tl + h/2; lr.y --)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
			tmpy = lr.y;
			lr.y = bl;
			SDL_FillRect(screen, &lr, white);
			lr.y = tmpy;
		}
		lr.x = tmpx;
		for(lr.y = tl; lr.y < tl + h/2; lr.y ++)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;
		//1
		for(lr.y = tl; lr.y < bl; lr.y ++)
		{
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;
		//C
		tmpx = lr.x;
		for(lr.y = tl + h/2; lr.y < bl; lr.y ++)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x = tmpx;
		for(lr.y = tl + h/2; lr.y > tl; lr.y --)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;
		//4
		for(lr.y = tl; lr.y < tl + h/2; lr.y ++)
			SDL_FillRect(screen, &lr, white);
		tmpx = lr.x;
		for(; lr.x < tmpx + chrSpc; lr.x ++)
			SDL_FillRect(screen, &lr, white);
		for(lr.y = tl; lr.y < bl; lr.y ++)
		{
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;
		//1
		for(lr.y = tl; lr.y < bl; lr.y ++)
		{
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;
		//2
		tmpx = lr.x;
		for(lr.y = bl; lr.y > tl + h/2; lr.y --)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
			tmpy = lr.y;
			lr.y = bl;
			SDL_FillRect(screen, &lr, white);
			lr.y = tmpy;
		}
		lr.x = tmpx;
		for(lr.y = tl; lr.y < tl + h/2; lr.y ++)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;
		//D
		//A D is a backwards C with a line on the left
		for(lr.y = tl; lr.y < bl; lr.y ++)
		{
			SDL_FillRect(screen, &lr, white);
		}
		tmpx = lr.x;
		for(lr.y = bl; lr.y > tl + h/2; lr.y --)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x = tmpx;
		for(lr.y = tl; lr.y < tl + h/2; lr.y ++)
		{
			lr.x ++;
			SDL_FillRect(screen, &lr, white);
		}
		lr.x += chrSpc;
		lr.y = 0;
		lr.w = 1;
		lr.h = 300;
		for(lr.x = 0; lr.x < 300; lr.x ++)
		{
			SDL_UpdateRect(screen, lr.x, lr.y, 
				lr.w, lr.h);
			usleep(1000);
		}
		sleep(3);
	}
	freeaddrinfo(results);
	free(tokenStr);
	free(oMsgBuff);
	return 0;
}
