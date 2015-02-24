#ifndef __options_h__
#define __options_h__

#include "option_values.h"

struct options
{
    int option;
    int min;
    int max;
    bool changed;
};


static struct all_options[5] = {
    {FORK_LIFT_MAX_HEIGHT, 0, 100, false},

}


#endif
