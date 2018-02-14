/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#include "gfx.h"
#include "gui.h"

#if (GFX_USE_GINPUT && GINPUT_NEED_TOGGLE) /*|| defined(__DOXYGEN__)*/

#include "../../../../src/ginput/ginput_driver_toggle.h"
#include "stm32f1xx_hal.h"

GINPUT_TOGGLE_DECLARE_STRUCTURE();

void ginput_lld_toggle_init(const GToggleConfig *ptc) {

}

unsigned ginput_lld_toggle_getbits(const GToggleConfig *ptc) {
//	gwinPrintf(GW1, "get toogle %d,  %d\r\n", HAL_GPIO_ReadPin(ptc->id, ptc->mode), ptc->mode);
	return (uint8_t)HAL_GPIO_ReadPin(ptc->id, ptc->mode);
}

#endif /* GFX_USE_GINPUT && GINPUT_NEED_TOGGLE */
