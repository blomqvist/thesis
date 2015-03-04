#include "OCU.h"
#include "Functions.h" //Functions declaration file

/*

*/

struct Option OptionArray[NUMER_OF_OPTIONS];

int main()
{
  init();
  loop();
  return 0;
}


void init(void)
{
	//InitCommunication();
	BuildOptionArray();	
}

void loop(void)
{
    //for(;;)
    //{
        //CANReceive();
		
		printf("\n\n");
        
		struct Option opt;
        
		int i;
        for (i = 0; i < sizeof(OptionArray); ++i) //find corresponding option
        {
            opt = OptionArray[i];
            
            if(!(*opt.run)(opt));
	        printf("TOM OPTION\n");
        }
        
        // Here is where all the changed parameters actually is sent
        //CANSetResult();
    //}
}

void BuildOptionArray(void)
{
	struct Option opt;
    
	opt.run = &RunPrintName;
	opt.OptionName = "FÖRSTA_OPTIONENS_NAMN";
	OptionArray[0] = opt; 
	
	opt.run = &RunPrintName;
	opt.OptionName = "ANDRA_OPTIONENS_NAMN";
	OptionArray[1] = opt;
           
	opt.run = &RunPrintName;
	opt.OptionName = "TREDJE_OPTIONENS_NAMN";
	OptionArray[2] = opt;
}
