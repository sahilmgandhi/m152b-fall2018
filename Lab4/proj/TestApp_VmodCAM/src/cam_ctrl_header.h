/************************************************************************/
/*																								*/
/*	cam_ctrl_header.h	--	Digilent Video Memory Access								*/
/*																								*/
/************************************************************************/
/*	Author:	WANG, Tinghui (steve)													*/
/*	Copyright 2011 Digilent CN															*/
/************************************************************************/
/*  File Description:																	*/
/*																								*/
/*																								*/
/************************************************************************/
/*  Revision History:																	*/
/*			1.0 Initial Release			WANG, Tinghui		04Mar2011			*/
/*																								*/
/************************************************************************/
#ifndef CAM_CTRL_HEADER_H		/* prevent circular inclusions */
#define CAM_CTRL_HEADER_H		/* by using protection macros */

#include <stdio.h>
#include <xio.h>

#include "xparameters.h"
#include "vmodcam_header.h"

/* ------------------------------------------------------------ */
/*					Miscellaneous Declarations								 */
/* ------------------------------------------------------------ */
#define blCamCtrlCR		0x00000000 // Control Reg Offset
#define blCamCtrlFWR		0x00000004 // Frame Width Reg Offset
#define blCamCtrlFHR		0x00000008 // Frame Height Reg Offset
#define blCamCtrlFBAR	0x0000000c // Frame Base Addr Reg Offset
#define blCamCtrlFLSR	0x00000010 // Frame Line Stride Reg Offeset
#define blCamCtrlFWDR	0x00000014 // H Sync Reg Offset
#define blCamCtrlFHDR	0x00000018 // H Back Porch Reg Offset
#define blCamCtrlFRDR	0x0000001c // H Front Porch Reg Offset

/* ------------------------------------------------------------ */
/*					General Type Declarations								 */
/* ------------------------------------------------------------ */

/* ------------------------------------------------------------ */
/*					Variable Declarations									 */
/* ------------------------------------------------------------ */

/* ------------------------------------------------------------ */
/*					Procedure Declarations									 */
/* ------------------------------------------------------------ */
int CamCtrlInit(u32 lCamCtrlBaseAddress, u32 fOptions, u32 blBaseAddr);
int CamStatus(u32 lCamCtrlBaseAddress);

/* ------------------------------------------------------------ */
#endif
/************************************************************************/
