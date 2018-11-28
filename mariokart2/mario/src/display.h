//#include <stdint.h>
//#include <stdio.h>
//#include <xil_exception.h>
//#include <xintc.h>
#include <xio.h>

//#include "game_controller.h"
#include "globals.h"
//#include "mb_interface.h"
//#include "xgpio.h"
//#include "xparameters.h"

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
void clearDisplay(int color)
{
  uint32_t posX, posY;

  for (posX = 0; posX < 2560; posX++)
    for (posY = 0; posY < 720; posY++)
      XIo_Out16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2 * (posY * 2560 + posX), color);

  u32 lDvmaBaseAddress = XPAR_DVMA_0_BASEADDR;

  XIo_Out32(lDvmaBaseAddress + blDvmaHSR, 40);    // hsync
  XIo_Out32(lDvmaBaseAddress + blDvmaHBPR, 260);  // hbpr
  XIo_Out32(lDvmaBaseAddress + blDvmaHFPR, 1540); // hfpr
  XIo_Out32(lDvmaBaseAddress + blDvmaHTR, 1650);  // htr
  XIo_Out32(lDvmaBaseAddress + blDvmaVSR, 5);     // vsync
  XIo_Out32(lDvmaBaseAddress + blDvmaVBPR, 25);   // vbpr
  XIo_Out32(lDvmaBaseAddress + blDvmaVFPR, 745);  // vfpr
  XIo_Out32(lDvmaBaseAddress + blDvmaVTR, 750);   // vtr

  XIo_Out32(lDvmaBaseAddress + blDvmaFWR, 0x00000500); // frame width
  XIo_Out32(lDvmaBaseAddress + blDvmaFHR, 0x000002D0); // frame height

  XIo_Out32(lDvmaBaseAddress + blDvmaFBAR, XPAR_DDR2_SDRAM_MPMC_BASEADDR); // frame base addr
  XIo_Out32(lDvmaBaseAddress + blDvmaFLSR, 0x00000A00);                    // frame line stride
  XIo_Out32(lDvmaBaseAddress + blDvmaCR, 0x00000003);                      // dvma enable, dfl enable
}

/**
 * Draw the current game state onto the monitor.
 *
 * @param game The game object to draw onto the monitor.
 *
 * @return true if successfully drawn, false otherwise.
 */
int drawGameState(struct game *g)
{
  /*
	 * For each column we will only draw the pixels that actually have to be
	 * drawn. (leave the other pixels as being blank) 
	 */

  uint32_t posX, posY;
  uint32_t newPosX, newPosY;

  uint32_t xPadding = 70;
  uint32_t yPadding = 100;
  for (posX = 0; posX < GAME_X; posX++)
  {
    for (posY = 0; posY < GAME_Y; posY++)
    {
      for (newPosX = posX * 10; newPosX < (posX + 1) * 10; newPosX++)
      {
        for (newPosY = posY * 10 + yPadding; newPosY < (posY + 1) * 10 + yPadding; newPosY++)
        {
          XIo_Out16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2 * (newPosY * 2560 + newPosX + xPadding), g->screen[posX][posY]);
        }
      }
    }
  }

  u32 lDvmaBaseAddress = XPAR_DVMA_0_BASEADDR;

  XIo_Out32(lDvmaBaseAddress + blDvmaHSR, 40);    // hsync
  XIo_Out32(lDvmaBaseAddress + blDvmaHBPR, 260);  // hbpr
  XIo_Out32(lDvmaBaseAddress + blDvmaHFPR, 1540); // hfpr
  XIo_Out32(lDvmaBaseAddress + blDvmaHTR, 1650);  // htr
  XIo_Out32(lDvmaBaseAddress + blDvmaVSR, 5);     // vsync
  XIo_Out32(lDvmaBaseAddress + blDvmaVBPR, 25);   // vbpr
  XIo_Out32(lDvmaBaseAddress + blDvmaVFPR, 745);  // vfpr
  XIo_Out32(lDvmaBaseAddress + blDvmaVTR, 750);   // vtr

  XIo_Out32(lDvmaBaseAddress + blDvmaFWR, 0x00000500); // frame width
  XIo_Out32(lDvmaBaseAddress + blDvmaFHR, 0x000002D0); // frame height

  XIo_Out32(lDvmaBaseAddress + blDvmaFBAR, XPAR_DDR2_SDRAM_MPMC_BASEADDR); // frame base addr
  XIo_Out32(lDvmaBaseAddress + blDvmaFLSR, 0x00000A00);                    // frame line stride
  XIo_Out32(lDvmaBaseAddress + blDvmaCR, 0x00000003);                      // dvma enable, dfl enable

  return 1;
}

#endif
