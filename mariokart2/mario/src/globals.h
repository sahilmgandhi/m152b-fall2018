//#include "xparameters.h"

#ifndef GLOBALS_H
#define GLOBALS_H

// This file contains all of the global variables for the game

// Graphic/Screen parameters
#define GRAPHIC_WIDTH 640
#define GRAPHIC_HEIGHT 360

#define GAME_X 50
#define GAME_Y 50

#define SCREEN_TOP_EDGE 180
#define SCREEN_BOT_EDGE 540
#define SCREEN_LEFT_EDGE 320
#define SCREEN_RIGHT_EDGE 960

#define SCREEN_REFRESH_RATE_HZ 50UL
#define SCREEN_REFRESH_PERIOD XPAR_TMRCTR_0_CLOCK_FREQ_HZ / SCREEN_REFRESH_RATE_HZ

// Radius of the player
#define PLAYER_SYMBOL_RADIUS 2

// Game parameters
#define START_WIDTH 60
#define START_SPEED 1
#define MIN_WIDTH 25
#define MAX_SPEED 10

// Color definitions
// Think of it as RGB but with only 16 different options for R, G and B

// red shell
#define RED 0xF00

// green shell
#define GREEN 0x0F0

// blue shell
#define BLUE 0x00F

// the car
#define WHITE 0xFFF

// bananas
#define YELLOW 0xFF0
#define PURPLE 0xF0F
#define CYAN 0x0FF

// the side area
#define BLACK 0x000

// the road
#define GRAY 0x888

#define CAR_COLOR 0xFFF
#define ROAD 0x888

#endif
