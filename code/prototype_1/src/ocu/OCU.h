#ifndef __OCU_H__
#define __OCU_H__

#include <stdlib.h>
#include <stdio.h>

#include "../common_headers/common_data_structures.h"
#include "../common_headers/pc_typedefs.h"
#include "../common_headers/systems.h"
#include "../common_headers/signals.h"

/* Define */
#define PAR_INDEX_MAX       23        // Length of OptParDef (ADJUST HERE WHEN FUNCTION ADDED)
#define NUMBER_OF_OPTIONS   1
#define NUMBER_OF_ARGUMENTS 4

/* Templates */
typedef void(*ptr)(UByte, UByte, UByte, UByte, UByte);

typedef struct {
	UByte low;
	UByte high;
} tByteWord;

typedef struct option
{
	ptr run;		// Option unique algorithm
	UByte arg[4];
	tByteWord stat;
} Option;

/* Active option pool */
Option OptionArray[NUMBER_OF_OPTIONS];

/* Functions */
void init(void);
void loop(void);
void runOptions(void);
void optionDummy(UByte Arg1, UByte Arg2, UByte Arg3, UByte Arg4, UByte BuffIndex);
void AddRequestToCanBuffer(UByte Sys, UByte Function, UByte Module, UByte Data);
void convertSignalBufferToSignalArray();


#endif
