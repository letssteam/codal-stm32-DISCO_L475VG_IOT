#include "HCSR04_sample.h"

#include <string>


void isFar() {
    printf("tres loin\n\n");
}

void isNear() {
    printf("tres proche\n\n");
}

void basicGetDistance(codal::STM32DISCO_L475VG_IOT& discoL475VgIot) {
    codal::HCSR04 hcsr04(discoL475VgIot.io.D6, discoL475VgIot.io.D7);

    std::string distance1;
    std::string distance2;
    std::string distance3;
    std::string distance4;
    while(true) {
        distance1 = "distance = " + std::to_string(hcsr04.getDistance(codal::HCSR04Unit::Mm)) + " mm\n";
        distance2 = "distance = " + std::to_string(hcsr04.getDistance(codal::HCSR04Unit::Cm)) + " cm\n";
        distance3 = "distance = " + std::to_string(hcsr04.getDistance(codal::HCSR04Unit::Dm)) + " dm\n";
        distance4 = "distance = " + std::to_string(hcsr04.getDistance(codal::HCSR04Unit::M)) + " m\n\n";

        printf(distance1.c_str());
        printf(distance2.c_str());
        printf(distance3.c_str());
        printf(distance4.c_str());        

        discoL475VgIot.sleep(1000);
    }
}

codal::HCSR04Sensor* hcsr04Sensor;
void eventIsNearOrFar(codal::STM32DISCO_L475VG_IOT& discoL475VgIot) {
    hcsr04Sensor = new codal::HCSR04Sensor(discoL475VgIot.io.D6, discoL475VgIot.io.D7, 1337);

    hcsr04Sensor->registerDistanceEvent(codal::DistanceBehold::Near, 20, codal::HCSR04Unit::Cm, isNear);
    hcsr04Sensor->registerDistanceEvent(codal::DistanceBehold::Far, 300, codal::HCSR04Unit::Mm, isFar);
}

void hcsr04Sample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);
    printf("\r\n");
    printf("********************************************\r\n");
    printf("*         Demonstration du HC-SR04         *\r\n");
    printf("********************************************\r\n");

    eventIsNearOrFar(discoL475VgIot);
    basicGetDistance(discoL475VgIot);
}
