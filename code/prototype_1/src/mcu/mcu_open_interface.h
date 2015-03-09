/*
 * mcu_open_interface.h
 *
 *  Created on: 5 mar 2015
 *      Author: bt4268
 */

#ifndef MCU_OPEN_INTERFACE_H_
#define MCU_OPEN_INTERFACE_H_

#include "../common_headers/common_data_structures.h"
#include "../common_headers/pc_typedefs.h"

void delegateFunctionCall(OptionPacket*);

void printFunctionCall(OptionPacket*);

#endif /* MCU_OPEN_INTERFACE_H_ */
