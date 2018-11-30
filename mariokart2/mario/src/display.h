
#include <xio.h>
#include "globals.h"
#include "game_controller.h"

#ifndef DISPLAY_H
#define DISPLAY_H

/**
 * Clear the screen with an all white screen.
 *
 */
void clearDisplay(int color);

/**
 * Draw the current game state onto the monitor.
 *
 * @param game The game object to draw onto the monitor.
 *
 * @return true if successfully drawn, false otherwise.
 */
int drawGameState(struct game *g);

#endif
