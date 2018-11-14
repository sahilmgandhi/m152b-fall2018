/************************************************************************/
/*																								*/
/*	vmodcam_header.h	--	functions for VmodCAM bringup							*/
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
/*			1.0 Initial Release			WANG, Tinghui		06Feb2011			*/
/*																								*/
/*	- version 1.0																			*/
/*		> i2c configuration for 720p 15Hz											*/
/*		> Single Camera																	*/
/*		> RGB444 pixel data output														*/
/*																								*/
/************************************************************************/
#ifndef VMODCAM_HEADER_H		/* prevent circular inclusions */
#define VMODCAM_HEADER_H		/* by using protection macros */

#include <stdio.h>
#include <xstatus.h>
#include <xio.h>

#include "xparameters.h"

// -----------------------------------------
// New configuration definition Added here
// -----------------------------------------

// ----------- Add New Configuration above this line ------------//
#define CAM_CFG_640x480P 0x0001
#define CAM_CFG_800x600 0x0002
#define CAM_CFG_1280x720P	0x0004

/* ------------------------------------------------------------ */
/*					Miscellaneous Declarations								 */
/* ------------------------------------------------------------ */

#define CAM_0_IIC_DEV_BASEADDR	XPAR_CAM_IIC_0_BASEADDR
#define lCamIicAddr	0x78

/* ------------------------------------------------------------ */
/*					General Type Declarations								 */
/* ------------------------------------------------------------ */

/* ------------------------------------------------------------ */
/*					Variable Declarations									 */
/* ------------------------------------------------------------ */

/* ------------------------------------------------------------ */
/*					Procedure Declarations									 */
/* ------------------------------------------------------------ */
int CamIicCfg(u32 lCamIicBaseAddress, u32 fOptions);
/* ------------------------------------------------------------ */
#endif
/************************************************************************/
