#include <stdio.h>
#include <xio.h>
#include "platform.h"
#include "xspi.h"
#include "xspi_l.h"
#include "xgpio.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "cam_ctrl_header.h"
#include "vmodcam_header.h"
#include "pmodGYRO.h"
#include <stdint.h>

#include "game_controller.h"
#include "display.h"
#include "globals.h"
#include "xtmrctr.h"

struct game g;
XTmrCtr timer;
XGpio Button;

void print(char *str);

int16_t readGyro();

int myabs(int x);
int mymin(int x, int y);
int mymax(int x, int y);

void displayCamera();

void main()
{
	init_platform();
	displayCamera();

	/*
	 * Initialize system timer.
	 */
	XTmrCtr_Initialize(&timer, XPAR_TMRCTR_0_DEVICE_ID);
	XGpio_Initialize(&Button, XPAR_BUTTON_DEVICE_ID);

	XGpio_SetDataDirection(&Button, 1, 0x1);

	clearDisplay(BLACK);

	char mode;
	xil_printf("Choose a game mode: '1' for camera-determined obstacles, '0' for \"AI\"-generated obstacles:\r\n");
	mode = getc(stdin);
	getchar(); // get rid of nullbyte
	xil_printf("\r\n");

	XTmrCtr_Start(&timer, 0);

	int xpos = 23;
	while (1)
	{
		if (mode == '1')
		{
			initGame(&g, 1);
			xil_printf("Entering camera-generated obstacle mode. Please expose the camera to red, green or blue as you drive.\r\n");
		}
		else
		{
			initGame(&g, 0);
			xil_printf("Entering \"AI\"-generated obstacle mode.\r\n");
		}
		srand(XIo_Out16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 7040 + 2560 * 400 + 100 + 100 * 2560, 0x00));
		while (!g.gameOver)
		{
			XTmrCtr_Reset(&timer, 0);
			XTmrCtr_Start(&timer, 0);
			int xposnew = readGyro();
			xposnew /= -1024;

			xpos += xposnew;
			xpos = mymax(xpos, 0);
			xpos = mymin(xpos, GAME_X - 4);

			propagateGame(&g);
			movePlayer(&g, xpos, -1);
			drawGameState(&g);
			while (XTmrCtr_GetValue(&timer, 0) < SCREEN_REFRESH_PERIOD)
				;
			int pixelRed = 0;
			int pixelBlue = 0;
			int pixelGreen = 0;
			int i, j;
			for (i = 0; i < 200; i++)
			{
				for (j = 0; j < 200; j++)
				{
					if (i == 0 || i == 199 || j == 0 || j == 199)
						XIo_Out16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 7040 + 2560 * 400 + i + j * 2560, 0x00);
					int pixel = XIo_In16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 7040 + 2560 * 400 + i + j * 2560);
					pixelBlue += (pixel & 0x000f);
					pixelGreen += (pixel & 0x00f0) >> 4;
					pixelRed += (pixel & 0x0f00) >> 8;
				}
			}
			pixelBlue /= 4000;
			pixelGreen /= 4000;
			pixelRed /= 4000;
			if (pixelRed > 2 * pixelGreen && pixelRed > 2 * pixelBlue)
			{
				g.cameraColor = RED;
				//			xil_printf("RED\n\r");
			}
			else if (pixelGreen > 2 * pixelRed && pixelGreen > 2 * pixelBlue)
			{
				g.cameraColor = GREEN;
				//			xil_printf("GREEN\n\r");
			}
			else if (pixelGreen > 2 * pixelRed)
			{
				g.cameraColor = BLUE;
				//			xil_printf("BLUE\n\r");
			}
			else
			{
				g.cameraColor = BLACK;
				//			xil_printf("None\n\r");
			}
			//		xil_printf("Pixel Average: %d %d %d\n\r", pixelBlue, pixelGreen, pixelRed);

			//		xil_printf("Game score: %d \n\r", g.score);
		}

		while (!XGpio_DiscreteRead(&Button, 1))
			;
	}

	drawGameState(&g);
}

/* ------------------------------------------------------------ */
/*					Helper functions							*/
/* ------------------------------------------------------------ */

/**
 *	Inits the camera and displays it onto the screen 
 */
void displayCamera()
{
	u32 lDvmaBaseAddress = XPAR_DVMA_0_BASEADDR;
	int posX, posY;
	int color;

	for (posX = 0; posX < 2560; posX++)
		for (posY = 0; posY < 720; posY++)
			XIo_Out16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2 * (posY * 2560 + posX), (posX / 40) << 4);

	XIo_Out32(lDvmaBaseAddress + blDvmaHSR, 40);	// hsync
	XIo_Out32(lDvmaBaseAddress + blDvmaHBPR, 260);  // hbpr
	XIo_Out32(lDvmaBaseAddress + blDvmaHFPR, 1540); // hfpr
	XIo_Out32(lDvmaBaseAddress + blDvmaHTR, 1650);  // htr
	XIo_Out32(lDvmaBaseAddress + blDvmaVSR, 5);		// vsync
	XIo_Out32(lDvmaBaseAddress + blDvmaVBPR, 25);   // vbpr
	XIo_Out32(lDvmaBaseAddress + blDvmaVFPR, 745);  // vfpr
	XIo_Out32(lDvmaBaseAddress + blDvmaVTR, 750);   // vtr

	XIo_Out32(lDvmaBaseAddress + blDvmaFWR, 0x00000500);					 // frame width
	XIo_Out32(lDvmaBaseAddress + blDvmaFHR, 0x000002D0);					 // frame height
	XIo_Out32(lDvmaBaseAddress + blDvmaFBAR, XPAR_DDR2_SDRAM_MPMC_BASEADDR); // frame base addr
	XIo_Out32(lDvmaBaseAddress + blDvmaFLSR, 0x00000A00);					 // frame line stride
	XIo_Out32(lDvmaBaseAddress + blDvmaCR, 0x00000003);						 // dvma enable, dfl enable

	// Uncomment these lines to init the camera, and then comment them out afterwards
	//	CamIicCfg(XPAR_CAM_IIC_0_BASEADDR, CAM_CFG_640x480P);
	//	CamIicCfg(XPAR_CAM_IIC_1_BASEADDR, CAM_CFG_640x480P);
	CamCtrlInit(XPAR_CAM_CTRL_0_BASEADDR, CAM_CFG_640x480P, 640 * 2);
	CamCtrlInit(XPAR_CAM_CTRL_1_BASEADDR, CAM_CFG_640x480P, 0);
}

/**
 *	Read the gyro values
 * 
 * @return int16_t 		The Gyro value 
 */
int16_t readGyro()
{
	PmodGYRO pgyr;

	GYRO_begin(&pgyr, XPAR_XPS_SPI_0_BASEADDR, XPAR_SPI_0_BASEADDR);
	GYRO_enableInt1(&pgyr, INT1_XHIE);
	GYRO_enableInt2(&pgyr, REG3_I2_DRDY);

	u8 temp = 0x0F;

	int16_t x, y, z;

	GYRO_begin(&pgyr, XPAR_XPS_SPI_0_BASEADDR, XPAR_SPI_0_BASEADDR);
	GYRO_ReadReg(&pgyr, OUT_Z_H, &temp, 1);
	x = temp << 8;
	GYRO_ReadReg(&pgyr, OUT_Z_L, &temp, 1);
	x |= temp;
	GYRO_end(&pgyr);

	return x;
}

/**
 * Absolute value function without needing to import anything
 * @param 	x 	int		The value of interest
 * @return 		int		The absolute value of x 
 */
int myabs(int x)
{
	return x < 0 ? -x : x;
}

/**
 * Min function without needing to import anything
 * @param 	x 	int		Value 1
 * @param 	y 	int		Value 2
 * @return 		int		Min(x, y)
 */
int mymin(int x, int y)
{
	return x < y ? x : y;
}

/**
 * Max function without needing to import anything
 * @param 	x 	int		Value 1
 * @param 	y 	int		Value 2
 * @return 		int		Max(x, y)
 */
int mymax(int x, int y)
{
	return x > y ? x : y;
}
