#include "DigitalIn.h"
#include "InterruptIn.h"
#include "PinNames.h"
#include "mbed.h"



LowPowerTicker flipper;
DigitalOut led(LED1);
DigitalIn btn(PA_0);
InterruptIn btnInterrupt(PA_0);


Timeout timeout;


int pushCounter = 0;

void ledSwitch(){
    led = 1;
    sleep_manager_lock_deep_sleep();
    flipper.detach();
    pushCounter = 0;

}

void lowPowerMode()
{
    
    led = 0;

    sleep_manager_can_deep_sleep();
    flipper.attach(&ledSwitch, float(pushCounter));
    
  
   
  
}

void push(){
     
    if(pushCounter > 0){
        timeout.detach();
    }
        
    timeout.attach(&lowPowerMode,2);
    
    pushCounter++;

}



int main()
{

    led = 1;
    btnInterrupt.rise(&push);

   

    while (1) {
        
        ThisThread::sleep_for(1000);
    }
}




