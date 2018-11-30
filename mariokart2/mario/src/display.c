#include "display.h"

const short numbers[3][10][10] =
{
{
    {0,0,1,1,1,1,1,1,0,0},
    {0,1,1,1,1,1,1,1,1,0},
    {0,1,1,0,0,0,0,1,1,0},
    {0,1,1,0,0,0,0,1,1,0},
    {0,1,1,0,0,0,0,1,1,0},
    {0,1,1,0,0,0,0,1,1,0},
    {0,1,1,0,0,0,0,1,1,0},
    {0,1,1,0,0,0,0,1,1,0},
    {0,1,1,1,1,1,1,1,1,0},
    {0,0,1,1,1,1,1,1,0,0}
},{
    {0,0,0,0,1,1,0,0,0,0},
    {0,0,0,1,1,1,0,0,0,0},
    {0,0,1,0,1,1,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0},
    {0,0,1,1,1,1,1,1,0,0},
    {0,0,1,1,1,1,1,1,0,0}
},{
    {0,0,0,1,1,1,1,0,0,0},
    {0,0,1,1,1,1,1,1,0,0},
    {0,1,1,0,0,0,0,1,1,0},
    {0,1,0,0,0,0,0,1,1,0},
    {0,0,0,0,1,1,1,1,0,0},
    {0,0,0,1,1,1,1,0,0,0},
    {0,0,1,1,0,0,0,0,0,0},
    {0,1,1,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,1,1,0}
}
};

int drawGameScore(int score);

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
        for (posY = 10; posY < GAME_Y; posY++)
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

    drawGameScore(1);

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

/**
 * Draw the current game score onto the monitor.
 *
 * @param score The game score to draw onto the monitor.
 *
 * @return true if successfully drawn, false otherwise.
 */
int drawGameScore(int score){
    uint16_t xPadding = 100;
    uint16_t yPadding = 10;
    uint8_t digits[3] = {score % 10, (score % 100) / 10, (score % 1000) / 100};
    int i, posX, posY, newPosX, newPosY;
    for(i = 0; i < 3; i++){
    	short num = digits[i];
        for (posX = 0; posX < 10; posX++)
        {
            for (posY = 0; posY < 10; posY++)
            {
                uint32_t color;
                if(numbers[num][posY][posX] == 0)
                    color = BLACK;
                else
                    color = WHITE;
                for (newPosX = posX * 3 + i * 30; newPosX < (posX + 1) * 3 + i * 30; newPosX++)
                {
                    for (newPosY = posY * 3 + yPadding; newPosY < (posY + 1) * 3 + yPadding; newPosY++)
                    {
                        XIo_Out16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2 * (newPosY * 2560 + newPosX + xPadding), color);
                    }
                }
            }
        }
    }

}
