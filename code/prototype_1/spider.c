#include "spider.h";

struct Option 
{
    bool trigger();
    bool booleancondition();
    void action();
};

void init(void)
{
  InitializeCanProtocol();    
    
  BuildOptionArray();
  
  loop();
}

void loop()
{
    for(;;)
    {
         CanStandby(); //May include button events and such
    
        struct option opt;
        
        for (var i = 0; i < size(optionsArray); ++i) //find corresponding opttion
        {
            opt = optionsArray[i];
    
            //function pointer. Check for right Trigger event and possible conditions
            //perform option uniqe action, otherwise move on to next option.
            if((*opt->trigger)() && (*opt->booleancondition)())
                (*opt->action)(); //found it
        }
        
        // Here is where all the changed parameters actually is sent
        // CAN.setChangedParams(); BEHÖVS EJ?
    }
}

void CanStandby()
{
    receiveMcuPdo(); //Pdo?
    
}
//Unique Trigger, Booleancondition and action for every option.
//Used when new options are born. 
//Development main area below.
//Begin the function declaration fest.

bool trigger()
{
    //current trigger event is compared to option specific
    //option specific trigger 
}

bool booleancondition()
{
    //some conditions are checked to confirm 
    //validity before takeing action
}

void action()
{
    //perform action. Such as modify parameter or perform 
    //instruction. Uses CAN-bus Tx to instruct MCU
}
    
    
    
