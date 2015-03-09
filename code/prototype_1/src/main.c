#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "mcu/mcu_open_interface.h"
#include "ocu/OCU.h"

// Function declarations

void generateCANSignalData(void);
void setSignalPacket(SignalPacket* sig, UByte type, void* data);

int main ()
{
    // Init rand
    srand(time(NULL));
    
    // We must create buffers for "CAN" data. - 

    // We must add signals (just add a few to test with?)

    // We must add some kind of randomization on different signals

    // We must initialize the "CAN" data buffer with values

    int opt_i;
    for (;;)
    {
        // "Send" "CAN" data
        
        // This means that we scramble current signals a bit
        generateCANSignalData();
        
        convertSignalBufferToSignalArray();
        // OCU loop here - iterate through all of the options
        // and calculate a new state depending on the changed signals
        // This will fill up a buffer of OptionPacket
        loop();

        // Iterate the list of OptionPacket and apply correct function
        
        for (opt_i = 0; opt_i < CAN_DATA_BUFFER_SIZE; ++opt_i)
        {
            // Just print and test (for now)
            printFunctionCall(&option_buffer[opt_i]);
        }
        
        // Sleep for LOOP_SLEEP_TIME
        sleep(LOOP_SLEEP_TIME);
    }

    // Make the compiler happy
    return 0;
}

void generateCANSignalData()
{
    // We change rand() % CAN_DATA_BUFFER_SIZE / 2 CAN data messages
    UByte NUM_CHANGE = rand() % SIGNALS_COUNT;

    UByte i = 0;
    UByte data;
    for (; i < NUM_CHANGE; ++i)
    {
        data = rand() % 125;
        setSignalPacket(&signal_buffer[i], tUByte, &data);
        signal_buffer[i].sig = i; // Move this to Init function - we only set the signal number once
    }
}

/**
 * Set signal packet
 * We only set changed to TRUE if the value is new, else the OCU already has the current value
 */
void setSignalPacket(SignalPacket* sig, UByte type, void* data)
{
    if (sig == NULL)
    {
        printf("setSignalPacket: Is null\n");
        return; // Null pointer - let's deploy parachute
    }

    switch (type)
    {
        case tUByte:
            if (sig->value.ub != *((UByte*)data))
            {
                sig->value.ub = *((UByte*)data);
                sig->changed = TRUE;
            }
        break;

        case tSByte:
            if (sig->value.sb != *((SByte*)data))
            {
                sig->value.sb = *((SByte*)data);
                sig->changed = TRUE;
            }
        break;

        case tUWord:
            if (sig->value.uw != *((UWord*)data))
            {
                sig->value.uw = *((UWord*)data);
                sig->changed = TRUE;
            }
        break;

        case tSWord:
            if (sig->value.sw != *((SWord*)data))
            {
                sig->value.ub = *((SWord*)data);
                sig->changed = TRUE;
            }
        break;

        case tBool:
            if (sig->value.ub != *((Bool*)data))
            {
                sig->value.ub = *((Bool*)data);
                sig->changed = TRUE;
            }
        break;
    }

    sig->type = type;
}

/**
 * Checks if option is equal to other option
 */

Bool optionPacketIsEqualTo(OptionPacket* original, OptionPacket* copy)
{
    return (original->sys      == copy->sys      &&
            original->function == copy->function &&
            original->module   == copy->module   &&
            original->value    == copy->value);
}

/**
 * Set signal packet
 * We only set changed to TRUE if the value is new, else the OCU already has the current value
 */
void setOptionPacket(OptionPacket* opt, OptionPacket data)
{
    if (opt == NULL)
    {
        return; // Null pointer - let's deploy parachute
    }

    if (optionPacketIsEqualTo(opt, &data) == FALSE)
    {
        *opt = data;
        opt->changed = 1;
    }
}

