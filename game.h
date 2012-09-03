/*
 * game.h
 * ------
 * 
 * Includes the functions' prototypes
 * 
 * */
 
 
#ifndef DEF_GAME
#define DEF_GAME
	
	void display(SDL_Surface *screen, SDL_Surface *sprites[], Uchar board[][SIZE], SDL_Rect *mario, BOOL *running);
	void play(SDL_Surface *screen);
	void move(Uchar board[][SIZE], SDL_Rect *mario, Direction d);
	void moveCrate(Uchar *crate1, Uchar *crate2);

#endif
