/*	
 * main.c
 * ------
 * 
 * Handles the menu and everything about the game (level editor)
 * 
 * */
 
 
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "config.h"
//#include "game.h"


int main(int argc, char *argv[])
{
	SDL_Surface *screen, *menu;
	SDL_Event event;
	Uchar running = 1;
	
	/* Video Initialization */
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(WIDE, HEIGHT, 32, SDL_HWSURFACE);
	menu = IMG_Load(MENU);

	while(running)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_KP1:
						play(screen);
					break;
					case SDLK_2:
					break;
				}
			break;
			case SDL_QUIT:
				running = 0;
			break;
		}
		
		SDL_BlitSurface(menu, NULL, screen, NULL);
		SDL_Flip(screen);
	}
	
	
	SDL_FreeSurface(menu);
	SDL_Quit();
	/*for(i=0 ; i<SIZE ; i++){
		printf("\n");
		for(j=0 ; j<SIZE ; j++)
			printf("%d", board[i][j]);}*/
}
