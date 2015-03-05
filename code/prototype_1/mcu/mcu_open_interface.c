/**
 * mcu_open_interface.c
 *
 *  Created on: 5 mar 2015
 *      Author: bt4268
 */

#include "mcu_open_interface.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Delegates a function call to its appropriate function
 * Works a secure layer between the OCU and MCU
 */
void delegateFunctionCall(OptionPacket* call)
{
	// This should not be possible
	if (call == NULL)
	{
		return;
	}

	switch (call->system)
	{
	case SIG_MODIFICATION:
		printf("Setting a signal\n");
		printFunctionCall(call);
	break;
	case TRACTION:
		printf("Calling a traction function\n");
		printFunctionCall(call);
	break;
	}

	return;
}

void printFunctionCall(OptionPacket* call)
{
	printf("function: %c\n", call->function);
	printf("module:   %c\n", call->module);

	if (call->type != tUndefined)
	{
		printf("value:    %c\n", call->value.u);
	}

	printf("\n");
}

