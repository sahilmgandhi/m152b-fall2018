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
  bool initialized = false;

  bool gameOver = false;

  uint8_t level = -1;

  // TODO: Keep track of the player y pos as well, but make it static for now
  int16_t playerXPos;
  int16_t playerYPos;

  // Use this and player_pos to keep track of the movement
  int16_t playerXLastPos;
  int16_t playerYLastPos;

  uint32_t screen[GAME_X][GAME_Y];

} Game;

bool initGame(Game *game, uint8_t level)
{
  game->initialized = true;
  game->level = level;
  game->gameOver = false;
  game->playerXPos = 0;
  game->playerYPos = 0;
  game->playerXLastPos = -1;
  game->playerYLastPos = -1;

  fillScreen(game, BLACK);

  game->screen[playerXPos][playerYPos] = CAR_COLOR;

  return true;
}

// Shift the entire game down EXCEPT for the bottom most row
bool propagateGame(Game *game)
{
  for (int i = GAME_X - 1; i > 0; i--)
  {
    for (int j = 0; j < GAME_Y; j++)
    {
      game->screen[i][j] = game->screen[i - 1][j];
    }
  }

  // At this point, we need add the top most row to be filled with EITHER:
  // spaces, or some kind of blocks????????
  // black for now
  for (int j = 0; j < GAME_Y; j++)
  {
    game->screen[0][j] = BLACK;
  }

  return true;
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
void fillScreen(Game *game, int color)
{
  for (int i = 0; i < GAME_X; i++)
  {
    for (int j = 0; j < GAME_Y; j++)
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
  playerXLastPos = playerXPos;
  playerYLastPos = playerYPos;

  playerXPos = newX;
  playerYPos = newY;

  game->screen[playerXPos][playerYPos] = CAR_COLOR;
}

#endif