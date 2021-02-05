#include "BlinkSample.h"

void BlinkSample_main(){
    codal::STM32IotNode iotNode;
	bool state = false;
	while(true)
    {    
		iotNode.io.led1.setDigitalValue((int)state);
        iotNode.io.led2.setDigitalValue((int)!state);
        iotNode.sleep(1000);
        state = !state;
    }
}