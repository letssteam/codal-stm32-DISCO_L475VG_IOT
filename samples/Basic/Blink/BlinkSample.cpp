#include "BlinkSample.h"

void BlinkSample_main(){
    codal::STM32IotNode iotNode;
	int state = 0;
	while(1)
    {    
		iotNode.io.led1.setDigitalValue(state);
        iotNode.io.led2.setDigitalValue(!state);
        iotNode.sleep(1000);
        state = !state;
    }
}