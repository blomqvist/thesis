/*
 * common_data_structures.h
 *
 *  Created on: 5 mar 2015
 *      Author: bt4268
 */

#ifndef COMMON_DATA_STRUCTURES_H_
#define COMMON_DATA_STRUCTURES_H_

#include "pc_typedefs.h"
#include "signals.h"
#include "systems.h"

#define CAN_DATA_BUFFER_SIZE 2
#define LOOP_SLEEP_TIME 2 // in seconds


// Common data types
typedef enum OPT_DataType {
	tUndefined = 0,
	tSWord,
	tUWord,
	tUByte,
	tSByte,
	tBool
} OPT_DataType;

typedef union {
	UByte ub;
	SByte sb;
	SWord sw;
	UWord uw;
	Bool b;
} OPT_Data;

typedef enum FunctionName {
	setMaxOptionSpeedLoRangeKmph = 0,
	setMaxOptionSpeedHiRangeKmph,
	FlashWarningLight
} FunctionName;

/**
 * Signal struct
 */
typedef struct {
	UByte sig;
	Bool changed;
    OPT_DataType type;
    OPT_Data value;
} SignalPacket;

/**
 * Only in use on OCU. Mapped into the iternal signal array 
 */
typedef struct {
	OPT_DataType type;
	OPT_Data value;
} InternalSignal;

/**
 * Option data struct
 */
typedef struct {
	UByte sys; 
	UByte function; // UByte Id_
	UByte module; // UByte Arg1
	
	Bool changed;
	
	UByte value;
} OptionPacket;


// Global variables
OptionPacket option_buffer[CAN_DATA_BUFFER_SIZE]; // options sent from the OCU to MCU
SignalPacket signal_buffer[SIGNALS_COUNT]; // signal (and other) data sent from MCU TO OCU


InternalSignal signal_array[SIGNALS_COUNT]; // Used by OCU

#endif /* COMMON_DATA_STRUCTURES_H_ */

