#include "OCU.h"
#include "Functions.h" //Functions declaration file

/* Signals */
uint8_t SPEED;


/* Active option pool */
Option* OptionArray[NUMBER_OF_OPTIONS];

typedef void(*run)(UByte, UByte, UByte, UByte, UByte);




int main()
{
  init();
  loop();
  return 0;
}


void init(void)
{
	//InitCommunication(); // For future CAN bus
	initializeOptions();
	BuildOptionArray();	
}

void loop(void)
{
    //for(;;)
    //{
        //CANReceive();
		
		runOptions();
		
		/*printf("%s","\n\n");
        
		Option* opt;
        
		int i = 0;
        for (i; i < NUMBER_OF_OPTIONS; ++i) //find corresponding option
        {
            opt = OptionArray[i];
            
            if(opt != NULL)
	        (*opt->run)();
	        
	        else
	        printf("%s \n", "EMPTY");
        }*/
        // Here is where all the changed parameters actually is sent
        //CANSetResult();
    //}
}

void BuildOptionArray(void)
{
	for (int i = 0; i < NUMBER_OF_OPTIONS; ++i)
	{
		Option* opt = malloc (sizeof (Option));
		opt->run = malloc (sizeof (RunPrintName));    
		opt->run = &RunPrintName;
		OptionArray[i] = opt; 
	}
}

/*---------------------------------------------------------------------------*/
/*!
    This function loads the option parameter (pointer and arguments) and check
    for min and max value of the arguments. The result is stored in a ram
    array where it can easily be picked by RunOptions().
    For each option function it is defined in what way optional hardware
    needs initialization
*/
/*---------------------------------------------------------------------------*/
void initializeOptions(void)
{
    const UByte DeadManMask = 0x24;
    UByte Option;
    SWord FuncIndex;
    SWord OptParArg;
    UByte Argument;
    UWord ParNumber;

    // Disable buttons 3 and 4 if they are used as dead mans handles
    if (cb_disabledOptionButton() == DeadManMask) {
        OptBtnHydrMask[3] = 0;
        OptBtnHydrMask[4] = 0;
    }

    // Reset state of extra hydraulic functions
    HydrOpt.State = HYDR_OPT_STATE_OFF;
    HydrOpt.OldState = HYDR_OPT_STATE_OFF;

    for (Option = 0; Option < NUMBER_OF_OPTIONS; Option++) {
        // Get index for parameter 1003, 1008, 1013, 1018, 1023, 1028, 1033 and 1038
        ParNumber = NUMBER_PAR_CONF_OPT_FUNC1 + (Option * 5);
        if (getParByNumber(ParNumber, &FuncIndex) != PAR_OK) {
            ASSERT_FAILED;
            break;
        }

        // Check boundaries of funcIndex
        if ((FuncIndex > 0) && (FuncIndex <= PAR_INDEX_MAX)) {

            // Store option function pointer in RAM
            RamParOpt[Option].ptr = OptParDef[FuncIndex - 1].ptr;

            // Get function arguments
            for (Argument = 0; Argument < NUMBER_OF_ARGUMENTS; Argument++) {
                ParNumber = NUMBER_PAR_CONF_OPT_FUNC1_ARG1 + (Option * 5) + Argument;
                if (getParByNumber(ParNumber, &OptParArg) != PAR_OK) {
                    ASSERT_FAILED;
                    break;
                }

                // First check it
                if ((OptParArg < OptParDef[FuncIndex - 1].min[Argument]) ||
                    (OptParArg > OptParDef[FuncIndex - 1].max[Argument])) {
                    // Set warning code for out of limit option value
                    errSet(ARG_ERR_SPIDER);
                    // Disable this option function pointer
                    RamParOpt[Option].ptr = optionDummy;
                }
                else {
                    // If ok, then store it in RAM
                    RamParOpt[Option].arg[Argument] = (UByte)OptParArg;
                }
            }
            // Request resources for this optional function, using its setup.
            // This also includes request to trig relevant spider
            if (RamParOpt[Option].ptr != 0 ) {
                (*((optfuncptr)RamParOpt[Option].ptr))
                    (RamParOpt[Option].arg[0],
                     RamParOpt[Option].arg[1],
                     RamParOpt[Option].arg[2],
                     RamParOpt[Option].arg[3],
                     BUFF_INDEX_SETUP | Option);     // Run the setup part of this function
            }
        }
    }
}


/*---------------------------------------------------------------------------*/
/*!
    Run all optional functions defined in option parameter area
*/
/*---------------------------------------------------------------------------*/
void runOptions(void)
{
	
	//TODO UByte
    uint8_t OptionFunction;

    // Before running the options, reset the speed restrictions if any
    // TODO resetMaxOptionSpeed(); DRIVER FUNCTION1

    for (OptionFunction = 0; OptionFunction < NUMBER_OF_OPTIONS; OptionFunction++) {

        if (OptionArray[OptionFunction].ptr != 0) {
            (*((run)OptionArray[OptionFunction].ptr))
            (OptionArray[OptionFunction].arg[0],
                    OptionArray[OptionFunction].arg[1],
                    OptionArray[OptionFunction].arg[2],
                    OptionArray[OptionFunction].arg[3],
                    OptionFunction );
        }
    }
}


