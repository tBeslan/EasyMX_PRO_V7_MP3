/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H
#include "stm32f1xx_hal.h"
#include "main.h"

#define Set_Cs        TFT_CS_GPIO_Port->BSRR = TFT_CS_Pin
#define Clr_Cs        TFT_CS_GPIO_Port->BRR = TFT_CS_Pin

#define Set_Rs        TFT_RS_GPIO_Port->BSRR = TFT_RS_Pin
#define Clr_Rs        TFT_RS_GPIO_Port->BRR = TFT_RS_Pin

#define Set_nWr       TFT_WR_GPIO_Port->BSRR = TFT_WR_Pin
#define Clr_nWr       TFT_WR_GPIO_Port->BRR = TFT_WR_Pin

#define Set_nRd       TFT_RD_GPIO_Port->BSRR = TFT_RD_Pin
#define Clr_nRd       TFT_RD_GPIO_Port->BRR = TFT_RD_Pin

static GFXINLINE void init_board(GDisplay *g) {
	(void) g;
}

static GFXINLINE void post_init_board(GDisplay *g) {
	(void) g;
}

static GFXINLINE void setpin_reset(GDisplay *g, bool_t state) {
	(void) g;
	if(state) HAL_GPIO_WritePin(TFT_RST_GPIO_Port, TFT_RST_Pin, GPIO_PIN_RESET);
	else HAL_GPIO_WritePin(TFT_RST_GPIO_Port, TFT_RST_Pin, GPIO_PIN_SET);
}

static GFXINLINE void set_backlight(GDisplay *g, uint8_t percent) {
	(void) g;
	TIM1->CCR1 = percent*10;
}

static GFXINLINE void acquire_bus(GDisplay *g) {
	(void) g;
	Clr_Cs;
	Set_nRd;
}

static GFXINLINE void release_bus(GDisplay *g) {
	(void) g;
	Set_Cs;
}

static GFXINLINE void busmode16(GDisplay *g) {
	(void) g;
}

static GFXINLINE void busmode8(GDisplay *g) {
	(void) g;
}

static GFXINLINE void write_index(GDisplay *g, uint8_t index) {
	(void) g;

	Clr_Rs;
	TFT_D0_GPIO_Port->ODR = ((TFT_D0_GPIO_Port->IDR) & 0xFF00) | index;
	Clr_nWr;
	Set_nWr;;
}

static GFXINLINE void write_data(GDisplay *g, uint8_t data) {
	(void) g;

	Set_Rs;
	TFT_D0_GPIO_Port->ODR = ((TFT_D0_GPIO_Port->IDR) & 0xFF00) | data;
	Clr_nWr;
	Set_nWr;

}

static GFXINLINE void write_ram16(GDisplay *g, uint16_t data) {
	(void) g;
	uint8_t low_byte = (data & 0x00FF);
	uint8_t high_byte = ((data & 0xFF00) >> 8);

	Set_Rs;

	TFT_D0_GPIO_Port->ODR =  ((TFT_D0_GPIO_Port->IDR) & 0xFF00) | high_byte;
	Clr_nWr;
	Set_nWr;

	TFT_D0_GPIO_Port->ODR = ((TFT_D0_GPIO_Port->IDR) & 0xFF00) | low_byte;
	Clr_nWr;
	Set_nWr;

}

#endif /* _GDISP_LLD_BOARD_H */
