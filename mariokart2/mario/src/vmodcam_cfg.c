/************************************************************************/
/*																								*/
/*	vmodcam_cfg.c -- various iic configuration for VmodCAM					*/
/*																								*/
/************************************************************************/
/*	Author: WANG, Tinghui (Steve)														*/
/*	Copyright 2011 Digilent CN															*/
/************************************************************************/
/*  Module Description: 																*/
/*		- provides various iic configuration procedures							*/
/*																								*/
/************************************************************************/
/*  Revision History:																	*/
/*			1.0	Initial Release		WANG, Tinghui		06Feb2011			*/
/*																								*/
/************************************************************************/


/* ------------------------------------------------------------ */
/*				Include File Definitions									 */
/* ------------------------------------------------------------ */
#include "vmodcam_header.h"

//#define DEBUG 1
//#define IIC_VERBOSE 1

#define CAM_IIC_CFG_NO	200
#define printf xil_printf

/* constant definition for iic driver */
#define	bIicRcFifo		0x10c
#define	bIicRcFifoPIRQ	0x120
#define	bIicCR			0x100
#define	bIicTxFifo		0x108
#define	bIicSR			0x104

#define	bitIicTxFifoRst	0x2
#define	bitIicEn				0x1
#define	bitIicGenCall		0x40
#define	bitIicStart			0x100
#define	bitIicStop			0x200
#define	bitIicRead			0x1
#define	bitIicTxEpt			0x80
#define	bitIicRcEpt			0x40

/* ------------------------------------------------------------ */
/*				Local Type Definitions										 */
/* ------------------------------------------------------------ */

/* ------------------------------------------------------------ */
/*				Global Variables												 */
/* ------------------------------------------------------------ */

/* ------------------------------------------------------------ */
/*				Local Variables												 */
/* ------------------------------------------------------------ */
int fCont = 1;

/* ------------------------------------------------------------ */
/*				Forward Declarations											 */
/* ------------------------------------------------------------ */
int CamIicInit(u32 lIicBaseAddress);
u32 CamIicSingleRead(u32 lIicBaseAddress, u32 lCamIicRegAddr);
int CamIicSingleWrite(u32 lIicBaseAddress, u32 lCamIicCfgCmd);
int CamIicSetupPicFormat(u32 lIicBaseAddress, u32 fOptions);
int CamIicPowerUp(u32 lIicBaseAddress);
void Delay(unsigned int msec);
void ClearScreen (u32 lBgColor);

/* ------------------------------------------------------------ */
/*				Procedure Definitions										 */
/* ------------------------------------------------------------ */

/***	CamIicCfg
 **
 **	Synopsis:
 **		CamIicCfg(iicBaseAddr, fOptions)
 **
 **	Parameters:
 **		u8 iicBaseAddress: base address for corresponding xps_iic device
 **		u32 fOptions: user-specified configuration options
 **			-> includes:
 **				CAM_CFG_640x480P: 640x480, Context A
 **				CAM_CFG_800x600: 800x600, Context A
 **				CAM_CFG_1280x720P: 1280x720, Context B
 **
 **	Return Value:
 **		integer: 0 - success; others - failure
 **
 **	Errors:
 **
 **	Description:
 **		The function sets configuration values based on fOption flags user
 **		specified.
 **
 */

int CamIicCfg(u32 lIicBaseAddress, u32 fOptions){
//	DvmaInit(XPAR_DVMA_0_BASEADDR);
	
	CamIicInit(lIicBaseAddress);
	CamIicSetupPLL(lIicBaseAddress);
	CamIicPowerUp(lIicBaseAddress);
	CamIicSetupPicFormat(lIicBaseAddress, fOptions);
	// Reset Reg (R/W), Parameter Hold, mask bad frame, Parallel Enable, 
	//                  Drive Pins, Lock Registers, Streaming Mode
	CamIicSingleWrite(lIicBaseAddress, 0x301A0ACC);
//	ClearScreen(0x00000000); // Set Background to Black
	return 0;
}

/* ------------------------------------------------------------ */

/***	CamIicSetupPLL
 **
 **	Synopsis:
 **		CamIicSetupPLL(lIicBaseAddress)
 **
 **	Parameters:
 **		u32 lIicBaseAddress - xps_iic device base address
 **
 **	Return Value:
 **		integer: 0 - success; others - failure
 **
 **	Errors:
 **
 **	Description:
 **		The function set the PLL on camera sensor into 24MHz in, 80MHz out.
 **
 */

int CamIicSetupPLL(u32 lIicBaseAddress) {
	xil_printf("Setting up Camera PLL into 24MHz/80MHz(in/out)...\r\n");
	CamIicSingleWrite(lIicBaseAddress, 0x341C0228); // PLL dividers; M=80,N=2,fMCLK=80MHz
	CamIicSingleWrite(lIicBaseAddress, 0x341E8F09); // PLL control; Power-up PLL; 
	Delay(200);													// Wait 3ms
	CamIicSingleWrite(lIicBaseAddress, 0x341E8F08);	// PLL control; Turn off bypass
	CamIicSingleWrite(lIicBaseAddress, 0x341406E6);	// MIPI Clock Overlap
	xil_printf("Setting up Camera PLL Successfully!\r\n");
}

/* ------------------------------------------------------------ */

/***	CamIicPowerUp
 **
 **	Synopsis:
 **		CamIicPowerUp(lIicBaseAddress)
 **
 **	Parameters:
 **		u32 lIicBaseAddress - xps_iic device base address
 **
 **	Return Value:
 **		integer: 0 - success; others - failure
 **
 **	Errors:
 **
 **	Description:
 **		The function power up the sensor, allows registers to be configured via i2c.
 **
 */

int CamIicPowerUp(u32 lIicBaseAddress) {
	xil_printf("Power up Camera. \r\n");
	
	CamIicSingleWrite(lIicBaseAddress, 0x32020008);	// Standby Ctrl (R/W), Enable IRQ. Doubt whether this is needed
	
	xil_printf("Power up successfully. \r\n");
}

/* ------------------------------------------------------------ */

/***	CamIicSetupPicFormat
 **
 **	Synopsis:
 **		CamIicSetupPicFormat(lIicBaseAddress)
 **
 **	Parameters:
 **		u8 iicBaseAddress: base address for corresponding xps_iic device
 **		u32 fOptions: user-specified configuration options
 **			-> includes:
 **				CAM_CFG_640x480P: 640x480, Context A
 **				CAM_CFG_800x600: 800x600, Context A
 **				CAM_CFG_1280x720P: 1280x720, Context B
 **
 **	Return Value:
 **		integer: 0 - success; others - failure
 **
 **	Errors:
 **
 **	Description:
 **		The function set the context camera is working on and specifies
 **		the output pixel format and size of the capture.
 **
 */
 
int CamIicSetupPicFormat(u32 lIicBaseAddress, u32 fOptions) {
	xil_printf("Setting up Camera Context and Capture Size.\r\n");
	/* Set Pixel Format */
	CamIicSingleWrite(lIicBaseAddress, 0x338c2795);	// Mode Var: output_format_A (R0x0095)
	CamIicSingleWrite(lIicBaseAddress, 0x339000e0);	// RGBx444
	CamIicSingleWrite(lIicBaseAddress, 0x338c2797);	// Mode Var: output_format_B (R0x0097)
	CamIicSingleWrite(lIicBaseAddress, 0x339000e0);	// RGBx444
	/* Set Picture Size */
	switch (fOptions) {
		// ------------------------------
		// New configuration Added here
		// ------------------------------
		
		// ----------- Add New Configuration above this line ------------//
		case CAM_CFG_640x480P:
			xil_printf("Current Settings: Context A, 640x480P ...\r\n");
			CamIicSingleWrite(lIicBaseAddress, 0x338C2702); // Context
			CamIicSingleWrite(lIicBaseAddress, 0x33900000); // A
			CamIicSingleWrite(lIicBaseAddress, 0x338CA103);	// Sequencer Var: cmd (R0x0003)
			CamIicSingleWrite(lIicBaseAddress, 0x33900001);	// Preview
			CamIicSingleWrite(lIicBaseAddress, 0x338C2703); // Output width context A
			CamIicSingleWrite(lIicBaseAddress, 0x33900280); // 640
			CamIicSingleWrite(lIicBaseAddress, 0x338C2705); // Output height context A
			CamIicSingleWrite(lIicBaseAddress, 0x339001E0); // 480
			CamIicSingleWrite(lIicBaseAddress, 0x338CA103);	// Sequencer Var: cmd (R0x0003)
			CamIicSingleWrite(lIicBaseAddress, 0x33900006);	// Refresh Mode
			break;
		case CAM_CFG_800x600:
			xil_printf("Current Settings: Context A, 800x600 ...\r\n");
			CamIicSingleWrite(lIicBaseAddress, 0x338C2702); // Context
			CamIicSingleWrite(lIicBaseAddress, 0x33900000); // A
			CamIicSingleWrite(lIicBaseAddress, 0x338CA103);	// Sequencer Var: cmd (R0x0003)
			CamIicSingleWrite(lIicBaseAddress, 0x33900001);	// Preview
			CamIicSingleWrite(lIicBaseAddress, 0x338C2703); // Output width context A
			CamIicSingleWrite(lIicBaseAddress, 0x33900320); // 800
			CamIicSingleWrite(lIicBaseAddress, 0x338C2705); // Output height context A
			CamIicSingleWrite(lIicBaseAddress, 0x33900258); // 600
			CamIicSingleWrite(lIicBaseAddress, 0x338CA103);	// Sequencer Var: cmd (R0x0003)
			CamIicSingleWrite(lIicBaseAddress, 0x33900006);	// Refresh Mode
			break;
		default: //CAM_CFG_1280x720P
			xil_printf("Current Settings: Context B, 1280x720p (Default)...\r\n");
			CamIicSingleWrite(lIicBaseAddress, 0x338C2707);	// Mode Var: output_width_B (R0x0007)
			CamIicSingleWrite(lIicBaseAddress, 0x33900500);	// = 1280
			CamIicSingleWrite(lIicBaseAddress, 0x338C2709);	// Mode Var: output_height_B (R0x0009)
			CamIicSingleWrite(lIicBaseAddress, 0x339002D0);	// = 720
			CamIicSingleWrite(lIicBaseAddress, 0x338C272F);	// Mode Var: sensor_row_start_B (R0x002F)
			CamIicSingleWrite(lIicBaseAddress, 0x33900004);	// = 4
			CamIicSingleWrite(lIicBaseAddress, 0x338C2731);	// Mode Var: sensor_col_start_B (R0x0031)
			CamIicSingleWrite(lIicBaseAddress, 0x33900004);	// = 4
			CamIicSingleWrite(lIicBaseAddress, 0x338C2733);	// Mode Var: sensor_row_end_B (R0x0033)
			CamIicSingleWrite(lIicBaseAddress, 0x339004BB);	// = 1211
			CamIicSingleWrite(lIicBaseAddress, 0x338C2735);	// Mode Var: sensor_col_end_B (R0x0035)
			CamIicSingleWrite(lIicBaseAddress, 0x3390064B);	// = 1611
			CamIicSingleWrite(lIicBaseAddress, 0x338C275F);	// Mode Var: crop_X0_B (R0x005F)
			CamIicSingleWrite(lIicBaseAddress, 0x33900000);	// = 0
			CamIicSingleWrite(lIicBaseAddress, 0x338C2761);	// Mode Var: crop_X1_B (R0x0061)
			CamIicSingleWrite(lIicBaseAddress, 0x33900500);	// = 1280
			CamIicSingleWrite(lIicBaseAddress, 0x338C2763);	// Mode Var: crop_Y0_B (R0x0063)
			CamIicSingleWrite(lIicBaseAddress, 0x33900000);	// = 0
			CamIicSingleWrite(lIicBaseAddress, 0x338C2765);	// Mode Var: crop_Y1_B (R0x0065)
			CamIicSingleWrite(lIicBaseAddress, 0x339002D0);	// = 720
			CamIicSingleWrite(lIicBaseAddress, 0x338CA120); // sequencer Var: captureParams.mode (R0x0020)
			CamIicSingleWrite(lIicBaseAddress, 0x33900002); // Capture Video
			CamIicSingleWrite(lIicBaseAddress, 0x338CA103); // Sequencer Var: cmd (R0x0003)
			CamIicSingleWrite(lIicBaseAddress, 0x33900002); // Capture Mode - Context B
			break;
	}	
	xil_printf("Setting up Camera Context and Capture Size successfully!\r\n");
	return 0;
}

/* ------------------------------------------------------------ */

/* ------------------------------------------------------------ */

/***	CamIicInit
 **
 **	Synopsis:
 **		CamIicInit(lIicBaseAddress)
 **
 **	Parameters:
 **		u32 lIicBaseAddress: base address for corresponding xps_iic device
 **
 **	Return Value:
 **		integer: 0 - success; others - failure
 **
 **	Errors:
 **		none
 **
 **	Description:
 **		The function initializes the xps_iic device for camera configuration
 **
 */

int CamIicInit(u32 lIicBaseAddress){
	u32 regCamIicCR;
	
	/* Set Receive FIFO Programmable Depth Interrupt Register (C_BASEADDR + 0x120) */
	XIo_Out32(lIicBaseAddress + bIicRcFifoPIRQ, 0xF);
	
	/* Reset Transmission FIFO */
	regCamIicCR = XIo_In32(lIicBaseAddress + bIicCR);
	regCamIicCR = regCamIicCR | bitIicTxFifoRst;
	XIo_Out32(lIicBaseAddress + bIicCR, regCamIicCR);
	
	regCamIicCR = XIo_In32(lIicBaseAddress + bIicCR);
	regCamIicCR = regCamIicCR & (~bitIicTxFifoRst) & (~bitIicGenCall); // General call disabled, Transmit FIFO normal operation
	regCamIicCR = regCamIicCR | bitIicEn; // Enables IIC Controller
	XIo_Out32(lIicBaseAddress + bIicCR, regCamIicCR);
}

/* ------------------------------------------------------------ */

/***	CamIicSingleRead
 **
 **	Synopsis:
 **		lCamIicRegData = CamIicSingleRead(lIicBaseAddress, lCamIicRegAddr)
 **
 **	Parameters:
 **		u32 lIicBaseAddress: base address for corresponding xps_iic device
 **		u32 lCamIicRegAddr: the address of the register to read
 **
 **	Return Value:
 **		u32 - data of target register
 **
 **	Errors:
 **		none
 **
 **	Description:
 **		The function reads out the value of target register.
 **
 */
 
u32 CamIicSingleRead(u32 lIicBaseAddress, u32 lCamIicRegAddr)
{
	u8* rgbCamIicAddr;
	u32 lCamIicRegData = 0;
	u32 lCamIicReadHeader;
	int cReadBytes;	
	
	if(!fCont){
		return 0;
	}

	rgbCamIicAddr = (u8*) (&lCamIicRegAddr);
	XIo_Out32(lIicBaseAddress + bIicTxFifo, lCamIicAddr | bitIicStart);
	XIo_Out32(lIicBaseAddress + bIicTxFifo, rgbCamIicAddr[2]);
	XIo_Out32(lIicBaseAddress + bIicTxFifo, rgbCamIicAddr[3]);

	XIo_Out32(lIicBaseAddress + bIicTxFifo, lCamIicAddr | bitIicStart | bitIicRead);
	XIo_Out32(lIicBaseAddress + bIicTxFifo, 0x02 | bitIicStop);
	
	cReadBytes = 2;
	while(cReadBytes){
		while(bitIicRcEpt & XIo_In32(lIicBaseAddress + bIicSR)){
			asm("nop");
		}
		lCamIicRegData = lCamIicRegData << 8;
		lCamIicRegData = lCamIicRegData + XIo_In32(lIicBaseAddress+bIicRcFifo);
		cReadBytes--;
	}
	return	lCamIicRegData;
}

/* ------------------------------------------------------------ */

/***	CamIicSingleWrite
 **
 **	Synopsis:
 **		CamIicSingleWrite(iicBaseAddress, camIicCfgCmd)
 **
 **	Parameters:
 **		u32 lIicBaseAddress - xps_iic device base address
 **		u32 lCamIicCfgCmd - camera iic configuration command
 **
 **	Return Value:
 **		integer: the bytes sent
 **
 **	Errors:
 **		none
 **
 **	Description:
 **		The function calls the corresponding procedure and passes
 **		all the argument to the procedure.
 **
 */
 
int CamIicSingleWrite(u32 lIicBaseAddress, u32 lCamIicCfgCmd){
	
	u8* rgbCamIicCfgCmd = (u8*) (&lCamIicCfgCmd);
	u32 lCamIicRegData = 0;
	int cWriteBytes;

	if(!fCont)
	{
		return;
	}

	while(!(bitIicTxEpt & XIo_In32(lIicBaseAddress+bIicSR))){
		asm("nop");
	}
	
#ifdef IIC_VERBOSE
	xil_printf("    %x\r\n", lCamIicCfgCmd);
#endif

	XIo_Out32(lIicBaseAddress + bIicTxFifo, lCamIicAddr | bitIicStart);
	XIo_Out32(lIicBaseAddress + bIicTxFifo, rgbCamIicCfgCmd[0]);
	XIo_Out32(lIicBaseAddress + bIicTxFifo, rgbCamIicCfgCmd[1]);
	XIo_Out32(lIicBaseAddress + bIicTxFifo, rgbCamIicCfgCmd[2]);
	XIo_Out32(lIicBaseAddress + bIicTxFifo, rgbCamIicCfgCmd[3] | bitIicStop);

	Delay(50);
#ifdef DEBUG
	lCamIicRegData = CamIicSingleRead(lIicBaseAddress, lCamIicCfgCmd >> 16);
	xil_printf("    >%4x\r\n", lCamIicRegData);
#endif

	return 0;
}

/* ------------------------------------------------------------ */

/***	Delay
 **
 **	Synopsis:
 **		Delay(msec)
 **
 **	Parameters:
 **		u32 msec - delay time in msec
 **
 **	Return Value:
 **		none
 **
 **	Errors:
 **		none
 **
 **	Description:
 **		Delay for certain msec.
 **
 */

void Delay(unsigned int msec) {
	int count = 0;
	
	for(count = 0; count < msec * XPAR_MICROBLAZE_0_FREQ / 1000; count++) {
		asm("nop");
	}
}

/* ------------------------------------------------------------ */

/***	ClearScreen
 **
 **	Synopsis:
 **		ClearScreen(lBgColor)
 **
 **	Parameters:
 **		u32 lBgColor - Background Color (GBR 44x4)
 **
 **	Return Value:
 **		none
 **
 **	Errors:
 **		none
 **
 **	Description:
 **		Set the background color for whole screen
 **
 */
 
void ClearScreen(u32 lBgColor) {
	u32 ilAddr;
	
	for (ilAddr = 0; ilAddr < 1280*720; ilAddr ++) {
		XIo_Out16(XPAR_DDR2_SDRAM_MPMC_BASEADDR + ilAddr * 2, lBgColor);
	}
	
	return 0;
}
/************************************************************************/
