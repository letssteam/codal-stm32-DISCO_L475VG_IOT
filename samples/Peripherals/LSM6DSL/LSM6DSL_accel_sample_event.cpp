#include "LSM6DSL_accel_sample_event.h"

#include <array>
#include <cstdio>

codal::Accelerometer* lsm6dsl;
codal::CoordinateSpace coordinateSpace(codal::SIMPLE_CARTESIAN, true, COORDINATE_SPACE_ROTATED_180);

void onSampleEvent(codal::Event e)
{
    codal::Sample3D sample = lsm6dsl->getSample();
    if (e.source == DEVICE_ID_ACCELEROMETER) {
        printf("ACCELERATION  = |X : %d, Y : %d, Z : %d|\n", sample.x, sample.y, sample.z);
    }
}

void lsm6dslAccelEventSample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*         Demonstration du LSM6DSL        *\r\n");
    printf("*******************************************\r\n");

    lsm6dsl = new codal::LSM6DSL_Accelerometer(&discoL475VgIot.i2c2, 0xD4, coordinateSpace);
    lsm6dsl->init();

    codal::EventModel::defaultEventBus->listen(DEVICE_ID_ACCELEROMETER, DEVICE_EVT_ANY, onSampleEvent);

    discoL475VgIot.sleep(500);
    lsm6dsl->requestUpdate();

    while (true) {
        discoL475VgIot.io.led1.setDigitalValue(1);
        discoL475VgIot.io.led2.setDigitalValue(0);

        discoL475VgIot.sleep(500);

        discoL475VgIot.io.led1.setDigitalValue(0);
        discoL475VgIot.io.led2.setDigitalValue(1);

        discoL475VgIot.sleep(500);
    }

    delete lsm6dsl;
}
