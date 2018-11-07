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
 * 
 */

typedef struct game
{
  bool initialized = false;

  bool game_over = false;

  int level = -1;

  // TODO: Keep track of the player y pos as well, but make it static for now
  int16_t player_x_pos;
  int16_t player_y_pos;

  // Use this and player_pos to keep track of the movement
  int16_t player_x_last_pos;
  int16_t player_y_last_pos;

} Game;

bool initialize_game(Game *game, int level)
{
  game->initialized = true;
  game->level = level;
  game->game_over = false;
  game->player_x_pos = 0;
  game->player_y_pos = 0;
  game->player_x_last_pos = 0;
  game->player_y_last_pos = 0;

  return true;
}

#endif