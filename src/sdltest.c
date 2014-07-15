#include <stdlib.h>
#include "SDL.h"
#include <unistd.h>


int main()
{
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
	SDL_Rect screenRect;
	screenRect.x = screenRect.y = 0;
	screenRect.w = screenRect.h = 300;
	SDL_Rect currRect;
	Uint32 black = SDL_MapRGB(screen->format, 0,0,0);
	Uint32 white = SDL_MapRGB(screen->format, 0xFF,0xFF,0xFF);
	SDL_FillRect(screen, &screenRect, black);
	int count;
	//Draw the letters:
	int w, h, i;
	int bl = 165;
	int tl = 135;
	int tmpx, tmpy;
	int chrSpc = 10;
	h = bl - tl;
	SDL_Rect lr;
	SDL_Rect tmpr;
	lr.h = lr.w = 3;
	lr.x = 10;
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
	for(lr.y; lr.y > tl; lr.y --)
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
//	SDL_UpdateRect(screen, 0, 0, 300, 300);
	lr.y = 0;
	lr.w = 1;
	lr.h = 300;
	for(lr.x = 0; lr.x < 300; lr.x ++)
	{
		SDL_UpdateRect(screen, lr.x, lr.y, 
			lr.w, lr.h);
		usleep(1000);
	}
	sleep(1);
	return 0;
}
	
