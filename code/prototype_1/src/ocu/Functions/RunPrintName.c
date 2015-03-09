
#include "../Functions.h"

void RunPrintName()
{
    if(signal_buffer[CURRENT_SPEED].value.ub > 60)
    {
        AddRequestToCanBuffer(0, 
            rand() % 50 + 48, 
            rand() % 50 + 48, 
            rand() % 50 + 48);
    }
    
}
