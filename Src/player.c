/*
 * player.c
 *
 *  Created on: 13 февр. 2018 г.
 *      Author: beslan
 */

#include "player.h"
#include "fatfs.h"
#include "gfx.h"
#include "gui.h"

	font_t			font;
	GFILE			*f;
	char 			*errmsg;
	uint32_t		toplay;
	uint32_t		len;
	GDataBuffer		*pd;

void playfile(char *path, char *file)
{

		if (!gfxBufferAlloc(4, 128)) {
		  		 gwinPrintf(GW1,"Err: No Memory\r\n");
		  	}

	/* Mount the file system. */
	  		if (gfileMount('F', path))
	  		  gwinPrintf(GW1, "Can't mount the FAT file system\r\n");

	  		if (!(f = gfileOpen(file, "r"))) {
	  			 gwinPrintf(GW1,"Err: Open file\r\n");
	  		}

	  		// Initialise the audio output device - bitrate is ignored
	  		if (!gaudioPlayInit(0, 44800, GAUDIO_PLAY_FORMAT_FILE)) {
	  			 gwinPrintf(GW1, "Err: Bad format/freq\r\n");
	  		}

	  		toplay = gfileGetSize(f);


	  		while(toplay) {
	  				// Get a buffer to put the data into
	  				pd = gfxBufferGet(TIME_INFINITE);		// This should never fail as we are waiting forever

	  				// How much data can we put in
	  				len = toplay > pd->size ? pd->size : toplay;
	  				pd->len = len;
	  				toplay -= len;

	  				// Read the data
	  				if (gfileRead(f, pd+1, len) != len) {
	  					 gwinPrintf(GW1, "Err: Read fail\r\n");

	  				}
	  				gaudioPlay(pd);
	  			}
	  			gfileClose(f);

	  			// Wait for the play to finish
	  			gaudioPlayWait(TIME_INFINITE);

	  gwinPrintf(GW1, "Done!\r\n");
}
