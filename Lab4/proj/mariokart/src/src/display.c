#include "display.h"

/**
 * Clear the screen with an all white screen.
 *
 */
void clearDisplay()
{
    uint32_t posX, posY;

    for (posX = 0; posX < 2560; posX++)
        for (posY = 0; posY < 720; posY++)
            XIo_Out16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2 * (posY * 2560 + posX), WHITE);

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

    // TODO: We need to fix this to work with the game: It needs to loop through the game's array and show the screen
    uint32_t posX, posY;
    uint32_t newPosX, newPosY;
    for (posX = 0; posX < GAME_X; posX++)
    {
        for (posY = 0; posY < GAME_Y; posY++)
        {
            for (newPosX = posX * 10; newPosX < (posX + 1) * 10; newPosX++)
            {
                for (newPosY = posY * 10; newPosY < (posY + 1) * 10; newPosY++)
                {
                    XIo_Out16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2 * (newPosY * 2560 + newPosX), g->screen[posX][posY]);
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