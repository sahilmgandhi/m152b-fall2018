#include <stdint.h>

#include "globals.h"
#include "game_board.h"
#include "xil_printf.h"

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

// Controls the entire game

/**
 * We need to keep track of all of the obstacles.
 * Since this is mario kart, we need to keep "driving" on the road, so essentially we need to block off parts of the road for "turning", random obstacles litered through the road, "red and green shells"?, banana peels. 
 * Bullet bills can be multi column things. 
 * 
 */

struct game
{
  int8_t initialized;

  int8_t gameOver;

  int8_t level;

  // TODO: Keep track of the player y pos as well, but make it static for now
  int16_t xLeft;
  int16_t yTop;

  // Use this and player_pos to keep track of the movement
  int16_t xLeftOld;
  int16_t yTopOld;

  // holds the color at each screen block
  uint32_t screen[GAME_X][GAME_Y];
};

void fillScreen(struct game *game, uint32_t color);

/**
 * Iniitalizes the entire game
 * 
 * @param game    struct game     The game object
 * @param level   uint8_t         The starting level
 */
void initGame(struct game *g, uint8_t level)
{
  g->initialized = 1;
  g->level = level;
  g->gameOver = 0;
  g->xLeftOld = -1;
  g->yTopOld = -1;
  g->xLeft = 24;
  g->yTop = GAME_Y-2;

  fillScreen(g, ROAD);

//  g->screen[g->playerXPos][g->playerYPos] = CAR_COLOR;

  placeCarOnScreen(g);
  g->screen[25][10] = RED;
}

void placeCarOnScreen(struct game *g){
	g->screen[g->xLeft][g->yTop +1] = CAR_COLOR;
	g->screen[g->xLeft+1][g->yTop + 1] = CAR_COLOR;
	g->screen[g->xLeft+2][g->yTop + 1] = CAR_COLOR;
	g->screen[g->xLeft+1][g->yTop] = CAR_COLOR;
}

int detectCollision(struct game * g){
	if (g->screen[g->xLeft][g->yTop+1] != ROAD && g->screen[g->xLeft][g->yTop+1] != CAR_COLOR){
		return 1;
	}
	if (g->screen[g->xLeft+1][g->yTop+1] != ROAD && g->screen[g->xLeft+1][g->yTop+1] != CAR_COLOR){
		return 2;
	}
	if (g->screen[g->xLeft+2][g->yTop+1] != ROAD && g->screen[g->xLeft+2][g->yTop+1] != CAR_COLOR){
		return 3;
	}
	if (g->screen[g->xLeft+1][g->yTop] != ROAD && g->screen[g->xLeft+1][g->yTop] != CAR_COLOR){
		return 4;
	}

	return 0;
}

/**
 * Shift the entire game down INCLUDING the bottom most row
 * It's weird to think that X is actually referring to columns and y to rows
 * 
 * @param game   struct game    The game object
 * 
 * @return int    0 if the player is dead, 1 else
 */
int propagateGame(struct game *g)
{
  int i;
  int j;
  for (i = GAME_X - 1; i > 0; i--)
  {
    for (j = 0; j < GAME_Y; j++)
    {
      g->screen[j][i] = g->screen[j][i-1];
    }
  }

  // At this point, we need add the top most row to be filled with EITHER:
  // spaces, or some kind of blocks????????
  // black for now
  // TODO: Generate some random top most row here:
  for (j = 0; j < GAME_X; j++)
  {
    g->screen[j][0] = ROAD;
  }

  if (detectCollision(g))
  {
    playerDead(g);
    return 0;
  }

  placeCarOnScreen(g);

  return 1;
}

/**
 * Game is over. 
 * 
 * @param game    Game      The game struct
 */
void finishGame(struct game *g)
{
  g->gameOver = 1;
  fillScreen(g, GREEN);
}

/**
 * Player died, so the entire screen should be red 
 * 
 * @param game    Game      The game struct
 */
void playerDead(struct game *g)
{
  g->gameOver = 1;
  fillScreen(g, RED);
}

/**
 *  Fills the entire screen with a single color
 * 
 * @param game    Game    The game struct
 * @param color   int     The color for the screen
 */
void fillScreen(struct game *g, uint32_t color)
{
  int i;
  int j;
  for (i = 0; i < GAME_X; i++)
  {
    for (j = 0; j < GAME_Y; j++)
    {
      // Basically filling out column at a time
      g->screen[i][j] = color;
    }
  }
}

/**
 * Moves the player and records the previous position
 * 
 * @param game    Game      The game struct
 * @param newX    int16_t   New X position (range from [0-47])
 * @param newY    int16_t   New Y position 
 */
void movePlayer(struct game *g, int16_t newX, int16_t newY)
{

  if (newX >= 0 && newX < GAME_X-2){
	  g->xLeftOld = g->xLeft;
	  g->xLeft = newX;
  }

  // If newY < 0, dont move it
  if (newY > 0 && newY < GAME_Y-1){
	  g->yTopOld = g->yTop;
	  g->yTop = newY;
  }
  placeCarOnScreen(g);
}

//void textOnTopLeft(struct game *game, char[] text){
//  Bitmap *b = bm_create(128,128);
//
//  bm_set_color(b, bm_atoi("white"));
//  bm_puts(b, 30, 60, text);
//
//  for(int i = 0; i < 128; i++){
//	  for (int j = 0; j < 128; j++){
//		  game->screen[i][j] = bm_get(b, i, j);
//		  //printf("%d", bm_get(b, 60, 60));
//	  }
//  }
//
//  bm_free(b);
//}

#endif
