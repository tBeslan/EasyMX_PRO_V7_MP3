/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_TOGGLE_BOARD_H
#define _GDISP_LLD_TOGGLE_BOARD_H

#include "stm32f1xx_hal.h"
#include "main.h"
#include "ginput_lld_toggle_config.h"
//#error "GINPUT Toggle Pal Driver: You need to define your board definitions"

// The below are example values

#define GINPUT_TOGGLE_NUM_PORTS			5       		// The total number of toggle inputs
#define GINPUT_TOGGLE_CONFIG_ENTRIES	5			// The total number of GToggleConfig entries

//#define GINPUT_TOGGLE_SW1			0				// Switch 1
//#define GINPUT_TOGGLE_SW2			1				// Switch 2
#define GINPUT_TOGGLE_UP			0				// Joystick Up
#define GINPUT_TOGGLE_DOWN			1				// Joystick Down
#define GINPUT_TOGGLE_LEFT			2				// Joystick Left
#define GINPUT_TOGGLE_RIGHT			3				// Joystick Right
#define GINPUT_TOGGLE_CENTER		4				// Joystick Center

#define GINPUT_TOGGLE_DECLARE_STRUCTURE() \
	const GToggleConfig GInputToggleConfigTable[GINPUT_TOGGLE_CONFIG_ENTRIES] = {\
		{KEY1_UP_GPIO_Port,	1,	 0, KEY1_UP_Pin},\
		{KEY1_LEFT_GPIO_Port,	1,	0, KEY1_LEFT_Pin},\
		{KEY1_RIGHT_GPIO_Port,	 1, 0, KEY1_RIGHT_Pin},\
		{KEY1_DOWN_GPIO_Port,	 1, 0, KEY1_DOWN_Pin},\
		{KEY1_CENTER_GPIO_Port,	 1, 0, KEY1_CENTER_Pin},\
	}


#endif /* _GDISP_LLD_TOGGLE_BOARD_H */
