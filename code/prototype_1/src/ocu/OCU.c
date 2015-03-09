#include "OCU.h"
#include "Functions.h" //Functions declaration file

/* Signals */


/* Objects */

UByte option_buffer_counter = 0;

void init(void)
{
    
}

void loop(void)
{
    //Receive CAN-Data and update signals
    convertSignalBufferToSignalArray();
    printf("%s \n", "OCU received signal update");

    //runOptions();
    RunPrintName();

    option_buffer_counter = 0;
}

/*---------------------------------------------------------------------------*/
/*!
    Run all optional functions defined in option parameter area
*/
/*---------------------------------------------------------------------------*/
void runOptions(void)
{
    UByte OptionFunction;

    // Before running the options, reset the speed restrictions if any
    // TODO resetMaxOptionSpeed(); DRIVER FUNCTION1

    for (OptionFunction = 0; OptionFunction < NUMBER_OF_OPTIONS; OptionFunction++) {

        if (OptionArray[OptionFunction].run != 0) {
            (*((ptr)OptionArray[OptionFunction].run))
            (OptionArray[OptionFunction].arg[0],
                    OptionArray[OptionFunction].arg[1],
                    OptionArray[OptionFunction].arg[2],
                    OptionArray[OptionFunction].arg[3],
                    OptionFunction );
        }
    }
}

/**
 * Converts the signal_buffer to signal_array
 */
void convertSignalBufferToSignalArray()
{
    UByte i = 0;
    SignalPacket sigpack;
    InternalSignal intsig;
    
    for (; i < SIGNALS_COUNT; ++i)
    {
        sigpack = signal_buffer[i];
        
        intsig.type  = sigpack.type;
        intsig.value = sigpack.value;
        
        // Copy by value
        signal_array[sigpack.sig] = intsig;
    }
}

void AddRequestToCanBuffer(UByte Sys, UByte Function, UByte Module, UByte Data) 
{
    option_buffer[option_buffer_counter].sys      = Sys;
    option_buffer[option_buffer_counter].function = Function;
    option_buffer[option_buffer_counter].module   = Module;
    option_buffer[option_buffer_counter].value    = Data;
    option_buffer[option_buffer_counter].changed  = TRUE;
    
    option_buffer_counter++;
}