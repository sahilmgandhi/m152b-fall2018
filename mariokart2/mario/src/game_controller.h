#include <stdint.h>
#include <stdlib.h>

#include "globals.h"
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

  uint8_t propagationCount;
  uint8_t bananaCollisions;

  uint32_t score;
  int8_t camera;
  int32_t cameraColor;
};

/**
 * Inits the entire game
 * 
 * @param game    struct game     The game object
 * @param level   uint8_t         The starting level
 */
void initGame(struct game *g, uint8_t level);

/**
 * Places the car onto the screen
 *
 * @param game 	struct game		The game object
 */
void placeCarOnScreen(struct game *g);

/**
 * Detects if the player has collided with an object
 *
 * @param game	struct game		The game object
 * @return 		0 if no collision, 1-4 if collision
 */
int detectCollision(struct game *g);

/**
 * Shift the entire game down INCLUDING the bottom most row
 * It's weird to think that X is actually referring to columns and y to rows
 * 
 * @param game   struct game    The game object
 * 
 * @return int    0 if the player is dead, 1 else
 */
int propagateGame(struct game *g);

/**
 * Generates the enemy objects for the player
 *
 * @param game	struct game		The game object
 * @param color int32_t         The color to generate
 */
void generateObjectCamera(struct game *g, int32_t color);

/**
 * Generates the enemy objects for the player
 *
 * @param game	struct game		The game object
 */
void generateObject(struct game *g);

/**
 * Game is over. 
 * 
 * @param game    Game      The game struct
 */
void finishGame(struct game *g);

/**
 * Player died, so the entire screen should be red 
 * 
 * @param game    Game      The game struct
 */
void playerDead(struct game *g);

/**
 *  Fills the entire screen with a single color
 * 
 * @param game    Game    The game struct
 * @param color   int     The color for the screen
 */
void fillScreen(struct game *g, uint32_t color);

/**
 * Moves the player and records the previous position
 * 
 * @param game    Game      The game struct
 * @param newX    int16_t   New X position (range from [0-47])
 * @param newY    int16_t   New Y position 
 */
void movePlayer(struct game *g, int16_t newX, int16_t newY);

/**
 * Set the color for the game object
 * 
 * @param game    Game      The game struct
 * @param color   int32_t   The color the camera detected
 */
void setGameObjectColor(struct game *g, int32_t color);

#endif
