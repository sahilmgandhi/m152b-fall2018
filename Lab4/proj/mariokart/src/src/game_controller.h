#include <stdint.h>

#include "globals.h"

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
  int16_t playerXPos;
  int16_t playerYPos;

  // Use this and player_pos to keep track of the movement
  int16_t playerXLastPos;
  int16_t playerYLastPos;

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
void initGame(struct game *g, uint8_t level);
/**
 * Shift the entire game down INCLUDING the bottom most row
 * 
 * @param game   struct game    The game object
 * 
 * @return int    0 if the player is dead, 1 else
 */
int propagateGame(struct game *game);

/**
 * Game is over. 
 * 
 * @param game    Game      The game struct
 */
void finishGame(struct game *game);

/**
 * Player died, so the entire screen should be red 
 * 
 * @param game    Game      The game struct
 */
void playerDead(struct game *game);

/**
 *  Fills the entire screen with a single color
 * 
 * @param game    Game    The game struct
 * @param color   int     The color for the screen
 */
void fillScreen(struct game *game, uint32_t color);

/**
 * Moves the player and records the previous position
 * 
 * @param game    Game      The game struct
 * @param newX    int16_t   New X position 
 * @param newY    int16_t   New Y position 
 */
void movePlayer(struct game *game, int16_t newX, int16_t newY);

// void textOnTopLeft(struct game *game, char[] text);

#endif
