#include "xparameters.h"

#ifndef GLOBALS_H
#define GLOBALS_H

// This file contains all of the global variables for the game

// Graphic/Screen parameters
#define GRAPHIC_WIDTH 640
#define GRAPHIC_HEIGHT 360

#define GAME_X 256
#define GAME_Y 72

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
#define RED 0xF << 8
#define GREEN 0xF << 4
#define BLUE 0xF
#define WHITE 0xFFF
#define BLACK 0x0

#define CAR_COLOR 0xF

#endif