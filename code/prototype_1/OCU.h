#ifndef __OCU_H__
#define __OCU_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> //For uint8_t

/* Define */
#define FALSE 0
#define TRUE 1
#define NUMER_OF_OPTIONS 3

/* Variables */
typedef enum {false, true} bool;

/* Objects */
struct Option
{
	bool (*run)();
	
	bool changes;
	const char *OptionName;

	uint8_t System;
	uint8_t Argument1;
	uint8_t Argument2;
	uint8_t Argument3;
	uint8_t Argument4; 
} Option;

//extern struct Option OptionArray[NUMER_OF_OPTIONS];

/* Functions */
void init(void);
void loop(void);
void BuildOptionArray(void);

#endif
