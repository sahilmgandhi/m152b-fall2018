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

#include "game_board.h"
#include "game_controller.h"
#include "display.h"
#include "globals.h"

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

#define BUFFER_SIZE 5
static XSpi SPIINST;
Xuint8 readBuffer[BUFFER_SIZE] = {0, 0, 0, 0, 0};
Xuint8 writeBuffer[BUFFER_SIZE] = {0, 0, 0, 0, 0};

void print(char *str);

int spiSetup(XSpi *spiInst, u16 spiID)
{
	//	writeBuffer[4] = 0b10000000;
	int status;
	u32 Count;
	u8 Test;
	XSpi_Config *ConfigPtr; /* Pointer to Configuration data */

	ConfigPtr = XSpi_LookupConfig(spiID);
	if (ConfigPtr == NULL)
	{
		xil_printf("Device not found");
		return 1;
	}
	status = XSpi_CfgInitialize(spiInst, ConfigPtr, ConfigPtr->BaseAddress);
	//	status = XSpi_Initialize(spiInst, spiID);
	xil_printf("Status: %d\n\r", status);
	if (status != XST_SUCCESS)
	{
		xil_printf("Initialization failed");
		//XSpi_Reset(spiInst);
		//status = XSpi_Initialize(spiInst, spiID);
		//return 1;
	}
	status = XSpi_SetOptions(spiInst, (XSP_MASTER_OPTION | XSP_CLK_ACTIVE_LOW_OPTION | XSP_CLK_PHASE_1_OPTION) | XSP_MANUAL_SSELECT_OPTION);
	if (status != XST_SUCCESS)
	{
		xil_printf("SetOptions failed");
		return 1;
	}
	status = XSpi_SetSlaveSelect(spiInst, 0x01);
	if (status != XST_SUCCESS)
	{
		xil_printf("SlaveSelect failed");
		return 1;
	}
	XSpi_Start(spiInst);
	XSpi_IntrGlobalDisable(spiInst);

	//	while(1){
	//		XSpi_Transfer(spiInst, &writeBuffer[0], &readBuffer[0], BUFFER_SIZE);
	//		for (Count = 0; Count < BUFFER_SIZE; Count++) {
	//			xil_printf("%x", readBuffer[Count]);
	//		}
	//	int yy = readBuffer[2];
	//	yy |= readBuffer[3] << 8;
	//	int xx = readBuffer[0];
	//	xx |= readBuffer[1] << 8;
	//
	//	xil_printf("X is %d, and Y is %d \n\r", xx, yy);
	//		xil_printf("\n\r");
	////		return 1;
	//	}
	return 0;
}

int readGyroRegister(XSpi *gyro, u8 address)
{

	address &= 0x80;
	Xuint8 gyroRecv[1] = {0};

	XSpi_Transfer(gyro, &address, NULL, sizeof(address));
	XSpi_Transfer(gyro, gyroRecv, gyroRecv, 1);
	return gyroRecv[0];
}

int writeGyroRegister(XSpi *gyro, u8 address, u8 data)
{

	//	address &= 0x7F;

	XSpi_Transfer(gyro, &address, NULL, sizeof(address));
	XSpi_Transfer(gyro, &data, NULL, 1);
	return 1;
}

int readGyroReg(XSpi *gyro, u8 reg, int nData)
{
	u8 byteArray[nData + 1];

	byteArray[0] = ((nData > 1) ? 0xC0 : 0x80) | (reg & 0x3F);
	XSpi_Transfer(&gyro, byteArray, byteArray, nData + 1);
	return byteArray[1];
}

// Do whatever you want in here to play around with the Gyro
void gyroPlayground()
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
	u16 x, y, z;
	u16 xx, yy, zz;
	u8 temperature;
	int a = 20;
	u8 whoami = 0;
	GYRO_ReadReg(&pgyr, 0x0F, &whoami, 1);
	xil_printf("WHOAMI: %x \n\r", whoami);
	//	GYRO_end(&pgyr);
	while (a > 0)
	{
		GYRO_begin(&pgyr, XPAR_XPS_SPI_0_BASEADDR, XPAR_SPI_0_BASEADDR);
		GYRO_ReadReg(&pgyr, OUT_X_H, &temp, 1);
		x = temp << 8;
		GYRO_ReadReg(&pgyr, OUT_X_L, &temp, 1);
		x |= temp;

		GYRO_ReadReg(&pgyr, OUT_Y_H, &temp, 1);
		y = temp << 8;
		GYRO_ReadReg(&pgyr, OUT_Y_L, &temp, 1);
		y |= temp;

		GYRO_ReadReg(&pgyr, OUT_Z_H, &temp, 1);
		z = temp << 8;
		GYRO_ReadReg(&pgyr, OUT_Z_L, &temp, 1);
		z |= temp;

		temperature = GYRO_getTemp(&pgyr);

		xx = GYRO_getX(&pgyr);
		yy = GYRO_getY(&pgyr);
		zz = GYRO_getZ(&pgyr);

		//		xil_printf("X: %d, Y: %d, Z: %d\n\r", x, y, z);
		xil_printf("XX: %d, YY: %d, ZZ: %d, Temp: %d\n\r", xx, yy, zz, temperature); // This just prints out all 0s ... so looks like that library's getX/Y/Z is incorrect
		a--;
		GYRO_end(&pgyr);
	}
	GYRO_end(&pgyr);

	//	//while(1)
	//	spiSetup(&SPIINST, XPAR_XPS_SPI_0_DEVICE_ID);
	//
	//
	//	// Gyro seems to send and receive one byte at a time
	//	u8 data = 0b00001111;
	//	writeGyroRegister(&SPIINST,GYRO_REG_CTRL_REG1, data);
	//
	//	xil_printf("WHO_AM_I: %x", readGyroRegister(&SPIINST, GYRO_REG_WHO_AM_I)); // If read register is working, this should print out 0xD3
	//	xil_printf("WHO_AM_I: %x", readGyroReg(&SPIINST, GYRO_REG_WHO_AM_I, 1)); // If read register is working, this should print out 0xD3
	//
	//	return 1;
	//	while(1){
	//		int x, y, z;
	//
	//		x = (readGyroRegister(&SPIINST, GYRO_REG_OUT_X_H) & 0xFF) << 8;
	//		x |= (readGyroRegister(&SPIINST, GYRO_REG_OUT_X_L) & 0xFF);
	//
	//		y = (readGyroRegister(&SPIINST, GYRO_REG_OUT_Y_H) & 0xFF) << 8;
	//		y |= (readGyroRegister(&SPIINST, GYRO_REG_OUT_Y_L) & 0xFF);
	//
	//		z = (readGyroRegister(&SPIINST, GYRO_REG_OUT_Z_H) & 0xFF) << 8;
	//		z |= (readGyroRegister(&SPIINST, GYRO_REG_OUT_Z_L) & 0xFF);
	//
	//		xil_printf("X: %d, Y: %d, Z: %d \n\r", x, y, z);
	//	}
}

int main()
{
	init_platform();

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

	CamIicCfg(XPAR_CAM_IIC_0_BASEADDR, CAM_CFG_640x480P);
	CamIicCfg(XPAR_CAM_IIC_1_BASEADDR, CAM_CFG_640x480P);
	CamCtrlInit(XPAR_CAM_CTRL_0_BASEADDR, CAM_CFG_640x480P, 640 * 2);
	CamCtrlInit(XPAR_CAM_CTRL_1_BASEADDR, CAM_CFG_640x480P, 0);
	for (posX = 0; posX < 2560; posX++)
		for (posY = 0; posY < 720; posY++)
			XIo_Out16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2 * (posY * 2560 + posX), 0x0000);

	return 0;
}
