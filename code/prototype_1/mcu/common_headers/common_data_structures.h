/*
 * common_data_structures.h
 *
 *  Created on: 5 mar 2015
 *      Author: bt4268
 */

#ifndef COMMON_DATA_STRUCTURES_H_
#define COMMON_DATA_STRUCTURES_H_

#include "pc_typedefs.h"

// Common data types
typedef enum OPT_DataType {
	tUndefined = 0,
	tSWord,
	tUByte,
	tBool
} OPT_DataType;

// Option data struct
typedef struct {
	UByte system;
	UByte function;
	UByte module;

	OPT_DataType type;

	union {
		UByte u;
		SWord s;
		Bool b;
	} value;
} OptionPacket;

#endif /* COMMON_DATA_STRUCTURES_H_ */
