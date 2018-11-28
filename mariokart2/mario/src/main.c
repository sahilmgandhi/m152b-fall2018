#include <stdio.h>
#include <xio.h>
#include "platform.h"
#include "xspi.h"
#include "xspi_l.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "cam_ctrl_header.h"
#include "vmodcam_header.h"
#include "pmodGYRO.h"
#include <stdint.h>

#include "game_board.h"
#include "game_controller.h"
#include "display.h"
#include "globals.h"
#include "xtmrctr.h"

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

#define SCALE 10;

#define BUFFER_SIZE 5
static XSpi SPIINST;
Xuint8 readBuffer[BUFFER_SIZE] = {0, 0, 0, 0, 0};
Xuint8 writeBuffer[BUFFER_SIZE] = {0, 0, 0, 0, 0};

void print(char *str);

// Do whatever you want in here to play around with the Gyro
int16_t readGyro()
{
	PmodGYRO pgyr;

	GYRO_begin(&pgyr, XPAR_XPS_SPI_0_BASEADDR, XPAR_SPI_0_BASEADDR);
	//	GYRO_setThsXH(&pgyr, 0x0F);
	GYRO_enableInt1(&pgyr, INT1_XHIE);
	GYRO_enableInt2(&pgyr, REG3_I2_DRDY);

	u8 temp = 0x0F;
	GYRO_WriteReg(&pgyr, CTRL_REG1, &temp, 1);

	temp = 0x07;
	GYRO_WriteReg(&pgyr, CTRL_REG3, &temp, 1);
	temp = 1 << 4;
	GYRO_WriteReg(&pgyr, CTRL_REG4, &temp, 1);
	int16_t x, y, z;
	u8 temperature;
	u8 whoami = 0;
	GYRO_ReadReg(&pgyr, 0x0F, &whoami, 1);
	xil_printf("WHOAMI: %x \n\r", whoami);

	GYRO_begin(&pgyr, XPAR_XPS_SPI_0_BASEADDR, XPAR_SPI_0_BASEADDR);
	GYRO_ReadReg(&pgyr, OUT_X_H, &temp, 1);
	x = temp << 8;
	GYRO_ReadReg(&pgyr, OUT_X_L, &temp, 1);
	x |= temp;
	GYRO_end(&pgyr);

	//xil_printf("XX: %d, YY: %d, ZZ: %d, Temp: %d\n\r", xx >> 5 , yy >> 5, zz >> 5, temperature); // This just prints out all 0s ... so looks like that library's getX/Y/Z is incorrect
	return x; //(int16_t)(xx >> 5);


}

struct game g;
XTmrCtr timer;

int myabs(int x){
	return x < 0 ? -x : x;
}

int mymin(int x, int y){
	return x < y ? x : y;
}

int mymax(int x, int y){
	return x > y ? x : y;
}

void displayCamera();

void main()
{
	init_platform();
	displayCamera();

	/*
	 * Initialize system timer.
	 */
	XTmrCtr_Initialize(&timer, XPAR_TMRCTR_0_DEVICE_ID);

	clearDisplay(BLACK);
	initGame(&g, 1);

	XTmrCtr_Start(&timer, 0);

	int a = 0;
	int xpos = 23;
	while (!g.gameOver)
	{
		XTmrCtr_Reset(&timer, 0);
		XTmrCtr_Start(&timer, 0);
		int xposnew = readGyro();

//		xil_printf("Xposnew: %d\n\r", xpos);
		xposnew /= 1024;
//		xil_printf("Xposnew: %d\n\r", xpos);

		xpos += xposnew;
		xpos = mymax(xpos, 0);
		xpos = mymin(xpos, 47);
//		xil_printf("Xpos: %d\n\r", xpos);
//		xil_printf("%d\n", xpos); // doruk
		propagateGame(&g);
		movePlayer(&g, xpos, -1);
		drawGameState(&g);
		while (XTmrCtr_GetValue(&timer, 0) < SCREEN_REFRESH_PERIOD);
		int pixel = 0;
		int i, j;
		for(i = 0; i <50; i++){
			for(j = 0; j < 50; j++){
				pixel += XIo_In16(XPAR_DDR2_SDRAM_MPMC_BASEADDR+1280+1280 + i + j*1280);
			}
		}
		xil_printf("Pixel Average: %d\n", pixel/2500);
		a++;
	}

	drawGameState(&g);

}

void displayCamera(){
	u32 lDvmaBaseAddress = XPAR_DVMA_0_BASEADDR;
	int posX, posY;
	int color;

	for(posX = 0; posX<2560; posX++)
		for(posY = 0; posY<720; posY++)
			XIo_Out16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2*(posY*2560+posX), (posX/40)<<4);

	XIo_Out32(lDvmaBaseAddress + blDvmaHSR, 40); // hsync
	XIo_Out32(lDvmaBaseAddress + blDvmaHBPR, 260); // hbpr
	XIo_Out32(lDvmaBaseAddress + blDvmaHFPR, 1540); // hfpr
	XIo_Out32(lDvmaBaseAddress + blDvmaHTR, 1650); // htr
	XIo_Out32(lDvmaBaseAddress + blDvmaVSR, 5); // vsync
	XIo_Out32(lDvmaBaseAddress + blDvmaVBPR, 25); // vbpr
	XIo_Out32(lDvmaBaseAddress + blDvmaVFPR, 745); // vfpr
	XIo_Out32(lDvmaBaseAddress + blDvmaVTR, 750); // vtr

	XIo_Out32(lDvmaBaseAddress + blDvmaFWR, 0x00000500); // frame width
	XIo_Out32(lDvmaBaseAddress + blDvmaFHR, 0x000002D0); // frame height
	XIo_Out32(lDvmaBaseAddress + blDvmaFBAR, XPAR_DDR2_SDRAM_MPMC_BASEADDR); // frame base addr
	XIo_Out32(lDvmaBaseAddress + blDvmaFLSR, 0x00000A00); // frame line stride
	XIo_Out32(lDvmaBaseAddress + blDvmaCR, 0x00000003); // dvma enable, dfl enable

//	CamIicCfg(XPAR_CAM_IIC_0_BASEADDR, CAM_CFG_640x480P);
//	CamIicCfg(XPAR_CAM_IIC_1_BASEADDR, CAM_CFG_640x480P);
	CamCtrlInit(XPAR_CAM_CTRL_0_BASEADDR, CAM_CFG_640x480P, 640*2);
	CamCtrlInit(XPAR_CAM_CTRL_1_BASEADDR, CAM_CFG_640x480P, 0);

}
