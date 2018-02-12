/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef GAUDIO_PLAY_BOARD_H
#define GAUDIO_PLAY_BOARD_H

#include "stm32f1xx_hal.h"
#include "spi.h"
#include "gfx.h"
#include "main.h"
// Initialise the board
static void board_init(void) {

}

// Chip is initialised enough so we can talk fast to it
static void board_init_end(void) {

}

// Reset the board
static void board_reset(void) {
	HAL_GPIO_WritePin(MP3_RST_GPIO_Port, MP3_RST_Pin, GPIO_PIN_SET);
}

// Returns the state of the dreq pin
static bool_t board_dreq(void) {
	return HAL_GPIO_ReadPin(MP3_DREQ_GPIO_Port, MP3_DREQ_Pin);
}

// Start a command write
static void board_startcmdwrite(void) {
	HAL_GPIO_WritePin(MP3_CS_GPIO_Port, MP3_CS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MP3_DCS_GPIO_Port, MP3_DCS_Pin, GPIO_PIN_SET);
}

// End a command write
static void board_endcmdwrite(void) {
	HAL_GPIO_WritePin(MP3_CS_GPIO_Port, MP3_CS_Pin, GPIO_PIN_SET);
}

// Start a command read
static void board_startcmdread(void) {
	HAL_GPIO_WritePin(MP3_CS_GPIO_Port, MP3_CS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MP3_DCS_GPIO_Port, MP3_DCS_Pin, GPIO_PIN_SET);
}

// End a command read
static void board_endcmdread(void) {
	HAL_GPIO_WritePin(MP3_CS_GPIO_Port, MP3_CS_Pin, GPIO_PIN_SET);
}

// Start a data write
static void board_startdatawrite(void) {
	HAL_GPIO_WritePin(MP3_DCS_GPIO_Port, MP3_DCS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MP3_CS_GPIO_Port, MP3_CS_Pin, GPIO_PIN_SET);
}

// End a data write
static void board_enddatawrite(void) {
	HAL_GPIO_WritePin(MP3_DCS_GPIO_Port, MP3_DCS_Pin, GPIO_PIN_SET);
}

// Write data to the SPI port
static void board_spiwrite(const uint8_t *buf, unsigned len) {
	HAL_SPI_Transmit(&hspi3, buf, len, 1000);
}

// Read data from the SPI port
static void board_spiread(uint8_t *buf, unsigned len) {
	HAL_SPI_Receive(&hspi3, buf, len, 1000);
}

#endif	/* GAUDIO_PLAY_BOARD_H */
