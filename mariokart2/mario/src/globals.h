#include "xparameters.h"

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

#define SCREEN_REFRESH_RATE_HZ 60UL
#define SCREEN_REFRESH_PERIOD XPAR_TMRCTR_0_CLOCK_FREQ_HZ / SCREEN_REFRESH_RATE_HZ

#define GREEN_HEIGHT 5
#define RED_HEIGHT 7
#define BLUE_HEIGHT 9
#define BLUE_WIDTH 25

#define blDvmaCR 0x00000000   // Control Reg Offset
#define blDvmaFWR 0x00000004  // Frame Width Reg Offset
#define blDvmaFHR 0x00000008  // Frame Height Reg Offset
#define blDvmaFBAR 0x0000000c // Frame Base Addr Reg Offset
#define blDvmaFLSR 0x00000010 // Frame Line Stride Reg Offeset
#define blDvmaHSR 0x00000014  // H Sync Reg Offset
#define blDvmaHBPR 0x00000018 // H Back Porch Reg Offset
#define blDvmaHFPR 0x0000001c // H Front Porch Reg Offset
#define blDvmaHTR 0x00000020  // H Total Reg Offset
#define blDvmaVSR 0x00000024  // V Sync Reg Offset
#define blDvmaVBPR 0x00000028 // V Back Porch Reg Offset
#define blDvmaVFPR 0x0000002c // V Front Porch Reg Offset
#define blDvmaVTR 0x00000030  // V Total Reg Offset

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
#define LANE 0xDDD

// Shell
#define SHELL 0xFDA
#define SHELLWHITE 0xFFE

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
