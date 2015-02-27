#ifndef __spider_h__
#define __spider_h__

void init(void);

void InitializeCanProtocol();    
void BuildOptionArray();
  
void loop();
void waitForAndReadCANdata();

//Option unique operations
bool trigger();
bool booleancondition();
void action();

#endif