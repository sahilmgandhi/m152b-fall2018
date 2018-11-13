#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xil_exception.h>
//#include <xintc.h>
#include <xio.h>

#include "xparameters.h"
#include "cam_ctrl_header.h"
#include "vmodcam_header.h"
#include "globals.h"
#include "game_controller.h"
#include "game_board.h"
#include "display.h"

#define blDvmaCR 0x00000000		// Control Reg Offset
#define blDvmaFWR 0x00000004	// Frame Width Reg Offset
#define blDvmaFHR 0x00000008	// Frame Height Reg Offset
#define blDvmaFBAR 0x0000000c // Frame Base Addr Reg Offset
#define blDvmaFLSR 0x00000010 // Frame Line Stride Reg Offeset
#define blDvmaHSR 0x00000014	// H Sync Reg Offset
#define blDvmaHBPR 0x00000018 // H Back Porch Reg Offset
#define blDvmaHFPR 0x0000001c // H Front Porch Reg Offset
#define blDvmaHTR 0x00000020	// H Total Reg Offset
#define blDvmaVSR 0x00000024	// V Sync Reg Offset
#define blDvmaVBPR 0x00000028 // V Back Porch Reg Offset
#define blDvmaVFPR 0x0000002c // V Front Porch Reg Offset
#define blDvmaVTR 0x00000030	// V Total Reg Offset

uint32_t interruptHandler();

struct game g;

void main()
{
	clearDisplay();
	initGame(&g, 1);
	////
	////	// NOTE: This function may NOT be working (test it out a bit!)
	drawGameState(&g);
	interruptHandler();

	u32 lDvmaBaseAddress = XPAR_DVMA_0_BASEADDR;
	uint32_t posX, posY;
	uint32_t color;

	XIo_Out32(lDvmaBaseAddress + blDvmaHSR, 40);		// hsync
	XIo_Out32(lDvmaBaseAddress + blDvmaHBPR, 260);	// hbpr
	XIo_Out32(lDvmaBaseAddress + blDvmaHFPR, 1540); // hfpr
	XIo_Out32(lDvmaBaseAddress + blDvmaHTR, 1650);	// htr
	XIo_Out32(lDvmaBaseAddress + blDvmaVSR, 5);			// vsync
	XIo_Out32(lDvmaBaseAddress + blDvmaVBPR, 25);		// vbpr
	XIo_Out32(lDvmaBaseAddress + blDvmaVFPR, 745);	// vfpr
	XIo_Out32(lDvmaBaseAddress + blDvmaVTR, 750);		// vtr

	XIo_Out32(lDvmaBaseAddress + blDvmaFWR, 0x00000500);										 // frame width
	XIo_Out32(lDvmaBaseAddress + blDvmaFHR, 0x000002D0);										 // frame height
	XIo_Out32(lDvmaBaseAddress + blDvmaFBAR, XPAR_DDR2_SDRAM_MPMC_BASEADDR); // frame base addr
	XIo_Out32(lDvmaBaseAddress + blDvmaFLSR, 0x00000A00);										 // frame line stride
	XIo_Out32(lDvmaBaseAddress + blDvmaCR, 0x00000003);											 // dvma enable, dfl enable

	// so starting at top left and going down
	for (posX = 0; posX < 2560; posX++)
		for (posY = 0; posY < 720; posY++)
			XIo_Out16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2 * (posY * 2560 + posX), RED);
	drawGameState(&g);

	//	for (posX = 0; posX < 2560; posX++)
	//		for (posY = 0; posY < 720; posY++)
	//			XIo_Out16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2 * (posY * 2560 + posX), BLUE);
}

// TODO: We need to work with the ISR module to get the uint32_terrupts from the Gyroscope

// NOTE: This function will handle the gyro ISR when we read over a particular value?
uint32_t gyroscopeISR()
{
	return -1;
}

// NOTE: This function handles reading uint32_terrupts and what to do with them
uint32_t interruptHandler()
{
	return -1;
}

// TODO: We also need to configure the clock module to move the track forward.
// NOTE: There may be some timing conflicts that we will have to worry about

// STOPSHIP: Uncomment the bottom lines and move them to the appropriate place when done.
// #include "xtmrctr.h"
// XTmrCtr timer;
// XTmrCtr_Initialize(&timer, XPAR_TMRCTR_0_DEVICE_ID);
// XTmrCtr_Start(&timer, 0);
// /*
// * Restart the timer.
// */
// XTmrCtr_Reset(&timer, 0);
// XTmrCtr_Start(&timer, 0);

// // Busy wait while the timer ticks ahead
// while (XTmrCtr_GetValue(&timer, 0) < SCREEN_REFRESH_PERIOD){}