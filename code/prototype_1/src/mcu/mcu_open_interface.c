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

	switch (call->sys)
	{
	case SIG_MODIFICATION:
		printf("MCU: Setting a signal\n");
		printFunctionCall(call);
	break;
	case TRACTION:
		printf("MCU: Calling a traction function\n");
		printFunctionCall(call);
	break;
	}

	return;
}

void printFunctionCall(OptionPacket* call)
{
	if (call->changed == FALSE)
	{
		return;
	}
	
	call->changed = FALSE;
	printf("%s", "MCU received following function call:\n");
	printf("function:  %X (%d)\n", call->function, call->function);
	printf("module:    %X (%d)\n", call->module,   call->module);
	printf("value:     %X (%d)\n", call->value,    call->value);

	printf("\n");
}

