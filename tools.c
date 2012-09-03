/* 
 * tools.c
 * -------
 * 
 * Handles files
 * 
 * */
 
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "config.h"
#include "tools.h"

void openLevel(Uchar board[][SIZE])
{
	FILE *f;
	char c;
	int y,x;

	f = fopen("levels.lvl", "r");
		
	/*if(f == NULL)
		return 0;*/
		
	for (y = 0; y < SIZE; y++)
		for (x = 0; x < SIZ; x++)
			board[y][x] = fgetc(f) - '0'; /* Convert char->int */
			

	fclose(f);
	/*return 1;*/
}

