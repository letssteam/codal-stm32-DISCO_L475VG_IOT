#include "LSM6DSL_accel_sample_event.h"

#include <array>

using namespace codal;
using namespace std;
/*
const char* gestureName(int value){
    switch(value){
        case ACCELEROMETER_EVT_NONE      :
            return "NONE";
        case ACCELEROMETER_EVT_TILT_UP   :
            return "TILT_UP";
        case ACCELEROMETER_EVT_TILT_DOWN :
            return "TILT_DOWN";
        case ACCELEROMETER_EVT_TILT_LEFT :
            return "TILT_LEFT";
        case ACCELEROMETER_EVT_TILT_RIGHT:
            return "TILT_RIGHT";
        case ACCELEROMETER_EVT_FACE_UP   :
            return "FACE_UP";
        case ACCELEROMETER_EVT_FACE_DOWN :
            return "FACE_DOWN";
        case ACCELEROMETER_EVT_FREEFALL  :
            return "FREEFALL";
        case ACCELEROMETER_EVT_3G        :
            return "3G";
        case ACCELEROMETER_EVT_6G        :
            return "6G";
        case ACCELEROMETER_EVT_8G        :
            return "8G";
        case ACCELEROMETER_EVT_SHAKE     :
            return "SHAKE";
        default :
            return "";

    }

}

void onSampleEvent(Event e){
    Sample3D sample = default_device_instance->accelerometer.getSample();
    if(e.source == DEVICE_ID_ACCELEROMETER)
        printf("(%ld) ACCELERATION  = |X : %d, Y : %d, Z : %d|\n", e.timestamp, sample.x, sample.y, sample.z);
    if(e.source == DEVICE_ID_GESTURE)
        printf("(%ld) GESTURE  = %s\n", e.timestamp, gestureName(e.value));
}*/

void lsm6dslAccelEventSample()
{
    STM32IotNode iotNode;
    iotNode.init();

    iotNode.serial.init(115200);

    default_device_instance->serial.init(115200);

    printf("\n");
    printf("****************\n\r");
    printf("* LSM6DSL TEST *\n\r");
    printf("****************\n\r");
    /*
        EventModel::defaultEventBus->listen(DEVICE_ID_ACCELEROMETER, DEVICE_EVT_ANY, onSampleEvent);
        EventModel::defaultEventBus->listen(DEVICE_ID_GESTURE, DEVICE_EVT_ANY, onSampleEvent);

        codal::STM32IotNode::sleep(500);
        iotNode.accelerometer.requestUpdate();*/

    while (true) {
        iotNode.io.led1.setDigitalValue(1);
        iotNode.io.led2.setDigitalValue(1);
        codal::STM32IotNode::sleep(1000);
        iotNode.io.led1.setDigitalValue(0);
        iotNode.io.led2.setDigitalValue(0);
        codal::STM32IotNode::sleep(1000);
    }
}
