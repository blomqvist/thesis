/*
 * main.c
 *
 *  Created on: 5 mar 2015
 *      Author: bt4268
 */

#include "mcu_open_interface.h"
#include <stdlib.h>
#include <stdio.h>


#define PACKET_COUNT 10

int main()
{
	OptionPacket* options[PACKET_COUNT];

	int i;
	for (i = 0; i < PACKET_COUNT; ++i)
	{
		options[i] = (OptionPacket*) malloc(sizeof (OptionPacket));
		options[i]->system   = (i % 2 == 0) ? SIG_MODIFICATION : TRACTION;
		options[i]->function = (i * 10) + 49;
		options[i]->module   = (i * 10) + 50;
		options[i]->type     = tUByte;
		options[i]->value.u  = (i * 10) + 51;
	}

	for (i = 0; i < PACKET_COUNT; ++i)
	{
		delegateFunctionCall(options[i]);
		free(options[i]);
	}

	return 0;
}
