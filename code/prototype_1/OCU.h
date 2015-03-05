#ifndef __OCU_H__
#define __OCU_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> //For uint8_t

/* Define */
#define FALSE 0
#define TRUE 1
#define PAR_INDEX_MAX       23        // Length of OptParDef (ADJUST HERE WHEN FUNCTION ADDED)
#define NUMBER_OF_OPTIONS   1
#define NUMBER_OF_ARGUMENTS 4
#define BUFF_INDEX_SETUP    0x80
#define STATE_AUTO_LIFT     0x01
#define STATE_AUTO_LOWER    0x02
#define STATE_AUTO_TIEBACK  0x08
#define STATE_AUTO_OFF      0xf0

#define cLiftLowerTimeout   10   // sec.

#define NoItemDetected      (Inputs & 0x01) // active when no item detected
#define AboveGndSwitch      (Inputs & 0x02) // active when forks above switch
#define BelowTopSwitch      (Inputs & 0x04) // active when forks below switch and lift limit
#define ExtAutoLiftBtn      (Inputs & 0x08) // active when auto lift command given
#define ExtAutoLowerBtn     (Inputs & 0x10) // active when auto lower command given

#define HYDR_FUNC_1_PUMP    0x01
#define HYDR_FUNC_1_RELEASE 0x02
#define HYDR_FUNC_2_PUMP    0x04
#define HYDR_FUNC_2_RELEASE 0x08
#define HYDR_FUNC_3_PUMP    0x10
#define HYDR_FUNC_3_RELEASE 0x20
#define HYDR_FUNC_4_PUMP    0x40
#define HYDR_FUNC_4_RELEASE 0x80


/* Variables */
typedef enum {false, true} bool;
extern uint8_t SPEED;


/* Objects */
typedef struct option
{
	void (*run)();		// Option unique algorithm
	bool changes;		// I Case of changes -> notify MCU
	uint8_t arg[4];
} Option;

/* Functions */
void init(void);
void loop(void);
void BuildOptionArray(void);

#endif
