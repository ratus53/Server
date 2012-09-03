/*
 * game.c
 * ------
 * 
 * Includes all the code for the game itself
 * 
 * */

#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "config.h"
#include "game.h"
//#include "tools.h"


void play(SDL_Surface *screen)
{
	Uchar board[SIZE][SIZE], running = 1;
	SDL_Surface *sprites[NBSPRITES], *mario_sprites[4];
	SDL_Rect mario;
	SDL_Event event;
	int x, y, i;
	
	
	/* Load Mario's Sprites */
	mario_sprites[UP]	= IMG_Load(MARIO_UP_IMG);
	mario_sprites[DOWN]	= IMG_Load(MARIO_DOWN_IMG);
	mario_sprites[RIGHT]= IMG_Load(MARIO_RIGHT_IMG);
	mario_sprites[LEFT]	= IMG_Load(MARIO_LEFT_IMG);
	/* Load Sprites */
	sprites[WALL] 		= IMG_Load(WALL_IMG);
	sprites[CRATE] 		= IMG_Load(CRATE_IMG);
	sprites[GOAL] 		= IMG_Load(GOAL_IMG);
	sprites[REACHED] 	= IMG_Load(REACHED_IMG);
	sprites[MARIO]		= mario_sprites[DOWN];
	
	openLevel(board);
	for (y = 0; y < SIZE; y++){
		printf("\n");
		for (x = 0; x < SIZE; x++){
			printf("%d", board[y][x]);
		}
	}
	/* Set Mario's position */
	for (y = 0; y < SIZE; y++)
		for (x = 0; x < SIZE; x++)
				if (board[y][x] == MARIO) {
					mario.x = x;
					mario.y = y;
					board[y][x] = EMPTY;
				}
	
	/* Wait for action */
	while (running) {
		SDL_WaitEvent(&event);
		switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					sprites[MARIO] = mario_sprites[UP];
					move(board, &mario, UP);
					break;
				
				case SDLK_DOWN:
					sprites[MARIO] = mario_sprites[DOWN];
					move(board, &mario, DOWN);
					break;
				
				case SDLK_RIGHT:
					sprites[MARIO] = mario_sprites[RIGHT];
					move(board, &mario, RIGHT);
					break;
				
				case SDLK_LEFT:
					sprites[MARIO] = mario_sprites[LEFT];
					move(board, &mario, LEFT);
					break;
				}
				break;
			
			case SDL_QUIT:
				running = 0;
				break;
		}
		
		display(screen, sprites, board, &mario, &running);
	}
	
	do {
		SDL_WaitEvent(&event);
	} while (event.type != SDL_KEYDOWN);
	
	/* Free Sprites */
	for (i = 0; i< NBSPRITES; i++)
		if ( (i != EMPTY) && (i != MARIO) )
			SDL_FreeSurface(sprites[i]);

	for (i = 0; i < 4; i++)
		SDL_FreeSurface(mario_sprites[i]);	

}

void move(Uchar board[][SIZE], SDL_Rect *mario, Direction d)
{
	switch (d) {
	case UP:
		if (mario->y - 1 < 0)
			break;

		if (board[mario->y - 1][mario->x] == EMPTY || board[mario->y - 1][mario->x] == GOAL)
			mario->y--;
		else if ( (mario->y - 2 >= 0) && (board[mario->y - 1][mario->x] == CRATE || board[mario->y - 1][mario->x] == REACHED) &&
					(board[mario->y - 2][mario->x] == EMPTY || board[mario->y - 2][mario->x] == GOAL)) 
		{
			moveCrate( &board[mario->y - 1][mario->x] , &board[mario->y - 2][mario->x]);
			mario->y--;
		}
		break;
		
	case DOWN:
		if (mario->y + 1 >= SIZE)
			break;

		if (board[mario->y + 1][mario->x] == EMPTY || board[mario->y + 1][mario->x] == GOAL)
			mario->y++;
		else if ( (mario->y + 2 < SIZE) && (board[mario->y + 1][mario->x] == CRATE || board[mario->y + 1][mario->x] == REACHED) &&
					(board[mario->y + 2][mario->x] == EMPTY || board[mario->y + 2][mario->x] == GOAL)) 
		{
			moveCrate( &board[mario->y + 1][mario->x] , &board[mario->y + 2][mario->x]);
			mario->y++;
		}
		break;
		
	case RIGHT:
		if (mario->x + 1 >= SIZE)
			break;

		if (board[mario->y][mario->x + 1] == EMPTY || board[mario->y][mario->x + 1] == GOAL)
			mario->x++;
		else if ( (mario->x + 2 < SIZE) && (board[mario->y][mario->x + 1] == CRATE || board[mario->y][mario->x + 1] == REACHED) &&
					(board[mario->y][mario->x + 2] == EMPTY || board[mario->y][mario->x + 2] == GOAL)) 
		{
			moveCrate( &board[mario->y][mario->x + 1] , &board[mario->y][mario->x + 2]);
			mario->x++;
		}
		break;
		
	case LEFT:
		if (mario->x - 1 < 0)
			break;

		if (board[mario->y][mario->x - 1] == EMPTY || board[mario->y][mario->x - 1] == GOAL)
			mario->x--;
		else if ( (mario->x - 2 >= 0) && (board[mario->y][mario->x - 1] == CRATE || board[mario->y][mario->x - 1] == REACHED) &&
					(board[mario->y][mario->x - 2] == EMPTY || board[mario->y][mario->x - 2] == GOAL)) 
		{
			moveCrate( &board[mario->y][mario->x - 1] , &board[mario->y][mario->x - 2]);
			mario->x--;
		}
		break;
	}
}

void moveCrate(Uchar *crate1, Uchar *crate2)
{
	if (*crate2 == EMPTY)
		*crate2 = CRATE;
	else
		*crate2 = REACHED;
		
	if (*crate1 == CRATE)
		*crate1 = EMPTY;
	else
		*crate1 = GOAL;
}

void display(SDL_Surface *screen, SDL_Surface *sprites[], Uchar board[][SIZE], SDL_Rect *mario, BOOL *running)
{
	SDL_Rect currentSprite = {0, 0, PIXEL, PIXEL};
	int x, y;
	Uchar win = 1;

	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
	
	for (y = 0; y < SIZE; y++) {
		currentSprite.y = y * PIXEL;
		
		for(x=0 ; x<SIZE ; x++) {
			currentSprite.x = x * PIXEL;
			
			if (board[y][x] != EMPTY)
				SDL_BlitSurface(sprites[ board[y][x] ], NULL, screen, &currentSprite);
				
			if (board[y][x] == GOAL)
				win = 0;
		}
	}
	
	currentSprite.x = mario->x * PIXEL;
	currentSprite.y = mario->y * PIXEL;
	SDL_BlitSurface(sprites[ MARIO ], NULL, screen, &currentSprite);
	
	/* Check Win */
	if (win) {
		SDL_Surface * bravo;
		bravo = IMG_Load(WIN_IMG);
		currentSprite.x = WIDE/2 - bravo->w/2;
		currentSprite.y = HEIGHT/2 - bravo->h/2;
		currentSprite.h = 0;
		currentSprite.w = 0;
		SDL_BlitSurface(bravo, NULL, screen, &currentSprite);
		*running = 0;
	}
	
	SDL_Flip(screen);
}
