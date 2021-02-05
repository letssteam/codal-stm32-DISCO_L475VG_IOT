#include "Sensor.h"
#include "GPIOSample.h"

using namespace codal;

void onSampleEvent(Event e){
    int value = default_device_instance->io.A3.getAnalogValue();
    default_device_instance->io.D5.setAnalogValue(value);
    printf("A3 = %d\n", value);
}


void GPIOSample_main(){
    codal::STM32IotNode iotNode;
    printf("\n");
    printf("*******************************************\n");
    printf("*           Demonstration de I/O          *\n");
    printf("*******************************************\n");
    //iotNode.io.A1.setAnalogValue(512);
    iotNode.sleep(1000);
    system_timer_event_every(1000, ID_PIN_P0, SENSOR_UPDATE_NEEDED);
    EventModel::defaultEventBus->listen(ID_PIN_P0, SENSOR_UPDATE_NEEDED, onSampleEvent);

    while(true) {
        iotNode.io.led1.setDigitalValue(1);
        iotNode.sleep(1000);

        iotNode.io.led1.setDigitalValue(0);
        iotNode.sleep(1000);
    }
}