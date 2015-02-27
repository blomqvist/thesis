#ifndef __options_h__
#define __options_h__

#include "option_values.h"

typdef struct options options;
struct options
{
    int option;
    int min;
    int max;
    bool changed;
};


typedef struct {
    bool (*run)(void); // Function pointer to the option logic
    bool changed;      // Tells the system that the run function have changed
                       // some data
    
    // More if needed
} Option;


struct ANYTYPE
{
    enum {
      typUndefined,
      typInt,           // 1
      typUint,
      typString,
      typLong
    } iType;

    union
    {
        int i;
        unsigned int u;
        bool b;
        long l;
    } value;
    
    enum {
        NO_PARAM = -1,
        PAR_ACC_FORKS_HIGH,
        PAR_APPL_CLEAR_DATA,
        PAR_BCU_CHARGER_PRESENT,
    } paramNum;
    
    // To access bool value you write:
    // b.value;
};

struct ANYTYPE data;

if (data.iType == typInt) {
    if (data.paramNum == NO_PARAM) {
        // Not a parameter
        int myVal = data.i.value;
    } else {
        // This is a parameter
        setParam(data.paramNum, data.i.value);
    }
}


static options all_options[5] = {
    {PAR_TOP_SPEED_FORK_DIR, 30, 100, false},
    {PAR_TOP_SPEED_DRIVEWHEEL_DIR, 30, 100, false},
    {PAR_ACCELERATION, 10, 100, false},
    {PAR_AUTO_BRAKE, 40, 100, false},
    {PAR_TOP_SPEED_RIDE_LOW_RANGE, 30, 100, false}
};

enum {
    HAL = 0,
    FORK,
    DRIVE
} system;

enum {
    LED = 0,
    SENSOR,
    TEMPERATURE
} hal_functions;

enum {
    LIFT = 0,
} fork_function;

enum {
    LED_1 = 0,
    LED_2, 
    LED_3
} leds;

struct data {
    int domain,
    int function,
    int module,
    int value
}


struct data d = {HAL, LED, LED_1, 1};

d.domain = HAL;
d.function = LED;
d.module = LED_1;
d.value = 1;

switch(d.system) {
    case HAL:
        handle_HAL(d);
    break;
    case FORK:
        handle_FORK(d);
    break;
}

#endif
