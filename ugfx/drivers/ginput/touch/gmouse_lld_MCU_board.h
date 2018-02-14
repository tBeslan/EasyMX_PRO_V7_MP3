/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _LLD_GMOUSE_MCU_BOARD_H
#define _LLD_GMOUSE_MCU_BOARD_H

#include "main.h"
#include "gui.h"
#include "adc_support.h"

// Resolution and Accuracy Settings
#define GMOUSE_MCU_PEN_CALIBRATE_ERROR		8
#define GMOUSE_MCU_PEN_CLICK_ERROR			6
#define GMOUSE_MCU_PEN_MOVE_ERROR			4
#define GMOUSE_MCU_FINGER_CALIBRATE_ERROR	14
#define GMOUSE_MCU_FINGER_CLICK_ERROR		18
#define GMOUSE_MCU_FINGER_MOVE_ERROR		14
#define GMOUSE_MCU_Z_MIN					0
#define GMOUSE_MCU_Z_MAX					4095
#define GMOUSE_MCU_Z_TOUCHON				3090
#define GMOUSE_MCU_Z_TOUCHOFF				400

// How much extra data to allocate at the end of the GMouse structure for the board's use
#define GMOUSE_MCU_BOARD_DATA_SIZE		0

#define ADC_NUM_CHANNELS   2
#define ADC_BUF_DEPTH      1

static bool_t init_board(GMouse *m, unsigned driverinstance) {
	(void)	m;

	// Only one touch interface on this board
	if (driverinstance)
		return FALSE;

	HAL_GPIO_WritePin(TOUCH_DRIVEA_GPIO_Port, TOUCH_DRIVEA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(TOUCH_DRIVEB_GPIO_Port, TOUCH_DRIVEB_Pin, GPIO_PIN_RESET);
	ADC_Start();
	return TRUE;
}

static bool_t read_xyz(GMouse *m, GMouseReading *prd)
{

	(void) m;

	// No buttons
	prd->buttons = 0;

	// Get the z reading (assumes we are ready to read z)
	prd->z = getADC1();

	// Take a shortcut and don't read x, y if we know we are definitely not touched.
	if (prd->z >= GMOUSE_MCU_Z_TOUCHOFF)
	{

		// Get the x reading
		HAL_GPIO_WritePin(TOUCH_DRIVEA_GPIO_Port, TOUCH_DRIVEA_Pin,
				GPIO_PIN_SET);
		HAL_GPIO_WritePin(TOUCH_DRIVEB_GPIO_Port, TOUCH_DRIVEB_Pin,
				GPIO_PIN_RESET);
		HAL_Delay(2);
		prd->x = getADC0();

		// Get the y reading
		HAL_GPIO_WritePin(TOUCH_DRIVEA_GPIO_Port, TOUCH_DRIVEA_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(TOUCH_DRIVEB_GPIO_Port, TOUCH_DRIVEB_Pin,
				GPIO_PIN_SET);
		HAL_Delay(2);
		prd->y = getADC1();

		// Set up for reading z again. We know it will be 20ms before we get called again so don't worry about settling time
		HAL_GPIO_WritePin(TOUCH_DRIVEA_GPIO_Port, TOUCH_DRIVEA_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(TOUCH_DRIVEB_GPIO_Port, TOUCH_DRIVEB_Pin,
				GPIO_PIN_RESET);
	}
	return TRUE;
}

#endif /* _LLD_GMOUSE_MCU_BOARD_H */
