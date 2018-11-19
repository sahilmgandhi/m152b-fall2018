/************************************************************************/
/*																								*/
/*	cam_ctrl.c -- functions for VmodCAM Controller Device						*/
/*																								*/
/************************************************************************/
/*	Author: WANG, Tinghui (Steve)														*/
/*	Copyright 2011 Digilent CN															*/
/************************************************************************/
/*  Module Description: 																*/
/*		- provides various procedures for VmodCAM Controller					*/
/*																								*/
/************************************************************************/
/*  Revision History:																	*/
/*			1.0	Initial Release		WANG, Tinghui		06Feb2011			*/
/*																								*/
/************************************************************************/

/* ------------------------------------------------------------ */
/*				Include File Definitions									 */
/* ------------------------------------------------------------ */
#include "cam_ctrl_header.h"

#define printf xil_printf

/* ------------------------------------------------------------ */
/*				Local Type Definitions										 */
/* ------------------------------------------------------------ */

/* ------------------------------------------------------------ */
/*				Global Variables												 */
/* ------------------------------------------------------------ */

/* ------------------------------------------------------------ */
/*				Local Variables												 */
/* ------------------------------------------------------------ */

/* ------------------------------------------------------------ */
/*				Forward Declarations											 */
/* ------------------------------------------------------------ */

/* ------------------------------------------------------------ */
/*				Procedure Definitions										 */
/* ------------------------------------------------------------ */

/***	CamCtrlInit
 **
 **	Synopsis:
 **		CamCtrlInit(lCamCtrlBaseAddr)
 **
 **	Parameters:
 **		u32 lCamCtrlBaseAddress: base address for corresponding cam_ctrl device
 **
 **	Return Value:
 **		integer: 0 - success; others - failure
 **
 **	Errors:
 **		none
 **
 **	Description:
 **		The function configure the camera controller to different input mode.
 **
 */

int CamCtrlInit(u32 lCamCtrlBaseAddress, u32 fOptions, u32 blBaseAddr) {
	switch (fOptions) {
		case CAM_CFG_640x480P:
			XIo_Out32(lCamCtrlBaseAddress + blCamCtrlFWR, 640); // frame width
			XIo_Out32(lCamCtrlBaseAddress + blCamCtrlFHR, 480); // frame height
			XIo_Out32(lCamCtrlBaseAddress + blCamCtrlFBAR, XPAR_DDR2_SDRAM_MPMC_BASEADDR + blBaseAddr); // frame base addr
			XIo_Out32(lCamCtrlBaseAddress + blCamCtrlFLSR, 0x00000A00); // frame line stride
			XIo_Out32(lCamCtrlBaseAddress + blCamCtrlCR, 0x00000001); // CamCtrl enable
			break;
		case CAM_CFG_800x600:
			printf("enter cam config 800x600");
			XIo_Out32(lCamCtrlBaseAddress + blCamCtrlFWR, 832); // frame width
			XIo_Out32(lCamCtrlBaseAddress + blCamCtrlFHR, 600); // frame height
			XIo_Out32(lCamCtrlBaseAddress + blCamCtrlFBAR, XPAR_DDR2_SDRAM_MPMC_BASEADDR + blBaseAddr); // frame base addr
			XIo_Out32(lCamCtrlBaseAddress + blCamCtrlFLSR, 0x00000A00); // frame line stride
			XIo_Out32(lCamCtrlBaseAddress + blCamCtrlCR, 0x0000000F); // CamCtrl enable, not aligned to 32 word boundary, enable End Burst
			break;
		default: //CAM_CFG_1280x720P
			XIo_Out32(lCamCtrlBaseAddress + blCamCtrlFWR, 0x00000500); // frame width
			XIo_Out32(lCamCtrlBaseAddress + blCamCtrlFHR, 0x000002D0); // frame height
			XIo_Out32(lCamCtrlBaseAddress + blCamCtrlFBAR, XPAR_DDR2_SDRAM_MPMC_BASEADDR + blBaseAddr); // frame base addr
			XIo_Out32(lCamCtrlBaseAddress + blCamCtrlFLSR, 0x00000A00); // frame line stride
			XIo_Out32(lCamCtrlBaseAddress + blCamCtrlCR, 0x00000003); // CamCtrl enable
			break;
	}	
	xil_printf("Setting up Camera Control Block successfully!\r\n");
	return 0;
}

/***	CamStatus
 **
 **	Synopsis:
 **		CamStatus(lCamCtrlBaseAddr)
 **
 **	Parameters:
 **		u32 lCamCtrlBaseAddress: base address for corresponding cam_ctrl device
 **
 **	Return Value:
 **		integer: 0 - success; others - failure
 **
 **	Errors:
 **		none
 **
 **	Description:
 **		The function displays the current status of VmodCAM Sensor
 **
 */

int CamStatus(u32 lCamCtrlBaseAddress) {
	u32 lFrameWidth;
	u32 lFrameHeight;
	u32 lFrameClkCnt;
	u32 uFrameRate;
	
	lFrameWidth = XIo_In32(lCamCtrlBaseAddress + blCamCtrlFWDR);
	lFrameHeight = XIo_In32(lCamCtrlBaseAddress + blCamCtrlFHDR);
	lFrameClkCnt = XIo_In32(lCamCtrlBaseAddress + blCamCtrlFRDR);
	uFrameRate = 80000000 / lFrameClkCnt;
	xil_printf("Current Configuration:\r\n");
	xil_printf("\t%dx%d @ %d fps\r\n", lFrameWidth, lFrameHeight, uFrameRate);
}