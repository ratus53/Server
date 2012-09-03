/*
 * config.h
 * --------
 * 
 * Includes all the necessary values to run the game
 * 
 * */

#ifndef DEF_CONFIG
#define DEF_CONFIG 

	struct Position{
		short int x, y, d;
	};
	typedef struct Position Position;

	typedef unsigned char BOOL;
	typedef unsigned char Uchar;

	/* Board */
	#define SIZE 				12
	#define HEIGHT 				PIXEL * SIZE
	#define WIDE				PIXEL * SIZE

	/* Sprites */
	#define PIXEL 				34
	#define WALL_IMG			"sprites/mur.jpg"
	#define MARIO_IMG			"sprites/mario_bas.gif"
	#define CRATE_IMG			"sprites/caisse.jpg"
	#define GOAL_IMG			"sprites/objectif.png"
	#define REACHED_IMG			"sprites/caisse_ok.jpg"
	//mario
	#define MARIO_UP_IMG		"sprites/mario_haut.gif"
	#define MARIO_DOWN_IMG		"sprites/mario_bas.gif"
	#define MARIO_RIGHT_IMG		"sprites/mario_droite.gif"
	#define MARIO_LEFT_IMG		"sprites/mario_gauche.gif"
		#define NBSPRITES		6 // nbrsprite+1

	/* IMG */
	#define WIN_IMG				"sprites/win.jpg"
	#define MENU				"sprites/menu.jpg"

	/* Element of the game */
	enum Element 	{EMPTY, WALL, CRATE, GOAL, MARIO, REACHED};
	enum Direction 	{UP, DOWN, RIGHT, LEFT};
	typedef enum Direction Direction;

#endif