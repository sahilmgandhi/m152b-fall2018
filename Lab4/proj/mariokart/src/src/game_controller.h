#include <stdbool.h>
#include <stdint.h>

#include "globals.h"
#include "game_board.h"

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

// Controls the entire game

/**
 * We need to keep track of all of the obstacles.
 * Since this is mario kart, we need to keep "driving" on the road, so essentially we need to block off parts of the road for "turning", random obstacles litered through the road, "red and green shells"?, banana peels. 
 * Bullet bills can be multi column things. 
 * 
 */

typedef struct game
{
  int initialized;

  int gameOver;

  int8_t level;

  // TODO: Keep track of the player y pos as well, but make it static for now
  int16_t playerXPos;
  int16_t playerYPos;

  // Use this and player_pos to keep track of the movement
  int16_t playerXLastPos;
  int16_t playerYLastPos;

  // holds the color at each screen block
  uint32_t screen[GAME_X][GAME_Y];

} Game;

void fillScreen(Game *game, uint32_t color);

int initGame(Game *game, uint8_t level)
{
  game->initialized = 1;
  game->level = level;
  game->gameOver = 0;
  game->playerXPos = 0;
  game->playerYPos = 0;
  game->playerXLastPos = -1;
  game->playerYLastPos = -1;

  fillScreen(game, BLACK);

  game->screen[game->playerXPos][game->playerYPos] = CAR_COLOR;

  return 1;
}

// Shift the entire game down EXCEPT for the bottom most row
int propagateGame(Game *game)
{
	int i;
	int j;
  for (i = GAME_X-1; i > 0; i--)
  {
    for (j =0; j < GAME_Y; j++)
    {
      game->screen[i][j] = game->screen[i - 1][j];
    }
  }

  // At this point, we need add the top most row to be filled with EITHER:
  // spaces, or some kind of blocks????????
  // black for now
  for (j = 0; j < GAME_Y; j++)
  {
    game->screen[0][j] = BLACK;
  }

  // TODO: In this function, after moving everything down, you should check if the player has died

  return 1;
}

/**
 * Game is over. 
 * 
 * @param game    Game      The game struct
 */
void finishGame(Game *game)
{
  game->gameOver = true;
  fillScreen(game, GREEN);
}

/**
 * Player died, so the entire screen should be red 
 * 
 * @param game    Game      The game struct
 */
void playerDead(Game *game)
{
  game->gameOver = true;
  fillScreen(game, RED);
}

/**
 *  Fills the entire screen with a single color
 * 
 * @param game    Game    The game struct
 * @param color   int     The color for the screen
 */
void fillScreen(Game *game, uint32_t color)
{
	int i;
	int j;
  for (i = 0; i < GAME_X; i++)
  {
    for (j = 0; j < GAME_Y; j++)
    {
      // Basically filling out column at a time
      game->screen[i][j] = color;
    }
  }
}

/**
 * Moves the player and records the previous position
 * 
 * @param game    Game      The game struct
 * @param newX    int16_t   New X position 
 * @param newY    int16_t   New Y position 
 */
void movePlayer(Game *game, int16_t newX, int16_t newY)
{
  game->playerXLastPos = game->playerXPos;
  game->playerYLastPos = game->playerYPos;

  game->playerXPos = newX;
  game->playerYPos = newY;

  game->screen[game->playerXPos][game->playerYPos] = CAR_COLOR;
}

#endif
