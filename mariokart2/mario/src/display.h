
#include <xio.h>
#include "globals.h"
#include "game_controller.h"

#ifndef DISPLAY_H
#define DISPLAY_H

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
