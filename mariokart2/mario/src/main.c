#include <stdio.h>
#include <xio.h>
#include "platform.h"
#include "xspi.h"
#include "xspi_l.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "cam_ctrl_header.h"
#include "vmodcam_header.h"


#define blDvmaCR		0x00000000 // Control Reg Offset
#define blDvmaFWR		0x00000004 // Frame Width Reg Offset
#define blDvmaFHR		0x00000008 // Frame Height Reg Offset
#define blDvmaFBAR	0x0000000c // Frame Base Addr Reg Offset
#define blDvmaFLSR	0x00000010 // Frame Line Stride Reg Offeset
#define blDvmaHSR		0x00000014 // H Sync Reg Offset
#define blDvmaHBPR	0x00000018 // H Back Porch Reg Offset
#define blDvmaHFPR	0x0000001c // H Front Porch Reg Offset
#define blDvmaHTR		0x00000020 // H Total Reg Offset
#define blDvmaVSR		0x00000024 // V Sync Reg Offset
#define blDvmaVBPR	0x00000028 // V Back Porch Reg Offset
#define blDvmaVFPR	0x0000002c // V Front Porch Reg Offset
#define blDvmaVTR		0x00000030 // V Total Reg Offset

#define BUFFER_SIZE		5
static XSpi SPIINST;
Xuint8 readBuffer[BUFFER_SIZE] = {0,0,0,0,0};
Xuint8 writeBuffer[BUFFER_SIZE] = {0,0,0,0,0};

void print(char *str);

int SpiPoll(XSpi *spiInst, u16 spiID){
//	writeBuffer[4] = 0b10000000;
	int status;
	u32 Count;
	u8 Test;
	XSpi_Config *ConfigPtr;	/* Pointer to Configuration data */

	ConfigPtr = XSpi_LookupConfig(spiID);
	if (ConfigPtr == NULL) {
		xil_printf("Device not found");
		return 1;
	}
//	status = XSpi_CfgInitialize(spiInst, ConfigPtr, ConfigPtr->BaseAddress);

	status = XSpi_Initialize(spiInst, spiID);
	xil_printf("Status: %d\n\r", status);
	if (status == XST_DEVICE_IS_STARTED) {
		xil_printf("Initialization failed");
		XSpi_Reset(spiInst);
		status = XSpi_Initialize(spiInst, spiID);
		//return 1;
	}
	XSpi_SetOptions(spiInst, XSP_MASTER_OPTION);
	status = XSpi_Start(spiInst);
	XSpi_IntrGlobalDisable(spiInst);
	XSpi_SetSlaveSelect(spiInst, 0x01);
	while(1){
		XSpi_Transfer(spiInst, &writeBuffer[0], &readBuffer[0], BUFFER_SIZE);
		for (Count = 0; Count < BUFFER_SIZE; Count++) {
			xil_printf("%x", readBuffer[Count]);
		}
		xil_printf("\n\r");
//		return 1;
	}
	return 0;

}

int main() {
	init_platform();

	xil_printf("sadlfkasd");
	//while(1)
	SpiPoll(&SPIINST, XPAR_XPS_SPI_0_DEVICE_ID);

//	XSpi spi1;
//	int status;
//	status = XSpi_Initialize(&spi1, XPAR_XPS_SPI_0_DEVICE_ID);
//	if (status == XST_DEVICE_IS_STARTED) {
//			xil_printf("Initialization failed");
//			XSpi_Reset(&spi1);
//			status = XSpi_Initialize(&spi1, XPAR_XPS_SPI_0_DEVICE_ID);
//	}
//	XSpi_SetOptions(&spi1, XSP_MASTER_OPTION);
//	status = XSpi_Start(&spi1);
//	XSpi_IntrGlobalDisable(&spi1);
//	XSpi_SetSlaveSelect(&spi1, 0x01);
//
//	XSpi_Transfer(&spi1, &writeBuffer[0], &readBuffer[0], 5);
//
//	int yy = readBuffer[2];
//	yy |= readBuffer[3] << 8;
//	int xx = readBuffer[0];
//	xx |= readBuffer[1] << 8;
//
//	xil_printf("X is %d, and Y is %d \n\r", xx, yy);


//	u32 lDvmaBaseAddress = XPAR_DVMA_0_BASEADDR;
//	int posX, posY;
//	int color;
//
//	for(posX = 0; posX<2560; posX++)
//		for(posY = 0; posY<720; posY++)
//			XIo_Out16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2*(posY*2560+posX), (posX/40)<<4);
//
//	XIo_Out32(lDvmaBaseAddress + blDvmaHSR, 40); // hsync
//	XIo_Out32(lDvmaBaseAddress + blDvmaHBPR, 260); // hbpr
//	XIo_Out32(lDvmaBaseAddress + blDvmaHFPR, 1540); // hfpr
//	XIo_Out32(lDvmaBaseAddress + blDvmaHTR, 1650); // htr
//	XIo_Out32(lDvmaBaseAddress + blDvmaVSR, 5); // vsync
//	XIo_Out32(lDvmaBaseAddress + blDvmaVBPR, 25); // vbpr
//	XIo_Out32(lDvmaBaseAddress + blDvmaVFPR, 745); // vfpr
//	XIo_Out32(lDvmaBaseAddress + blDvmaVTR, 750); // vtr
//
//	XIo_Out32(lDvmaBaseAddress + blDvmaFWR, 0x00000500); // frame width
//	XIo_Out32(lDvmaBaseAddress + blDvmaFHR, 0x000002D0); // frame height
//	XIo_Out32(lDvmaBaseAddress + blDvmaFBAR, XPAR_DDR2_SDRAM_MPMC_BASEADDR); // frame base addr
//	XIo_Out32(lDvmaBaseAddress + blDvmaFLSR, 0x00000A00); // frame line stride
//	XIo_Out32(lDvmaBaseAddress + blDvmaCR, 0x00000003); // dvma enable, dfl enable
//
//	CamIicCfg(XPAR_CAM_IIC_0_BASEADDR, CAM_CFG_640x480P);
//	CamIicCfg(XPAR_CAM_IIC_1_BASEADDR, CAM_CFG_640x480P);
//	CamCtrlInit(XPAR_CAM_CTRL_0_BASEADDR, CAM_CFG_640x480P, 640*2);
//	CamCtrlInit(XPAR_CAM_CTRL_1_BASEADDR, CAM_CFG_640x480P, 0);
//	for(posX = 0; posX<2560; posX++)
//		for(posY = 0; posY<720; posY++)
//			XIo_Out16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2*(posY*2560+posX), 0x0000);

	return 0;
}
