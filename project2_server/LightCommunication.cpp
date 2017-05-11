//
// Created by Kristof on 5/9/2017.
//

#include "LightCommunication.h"

LightCommunication::LightCommunication() {
    light_IRStyle = new TransmitterIR(p21);
    light_serial = new Serial(p13, p14);
     light_serial->baud (19200);
}

LightCommunication::~LightCommunication() {
    delete light_serial;
    delete light_IRStyle;
}

void LightCommunication::sendSerial(uint8_t *data) {
    //light_serial->printf("%c%c%c", data[0],data[1],data[2]);
    light_serial->printf("%s", data);
}


void LightCommunication::sendIRStyle(uint8_t *data) {
    RemoteIR::Format format = RemoteIR::NEC;
    int bitcount = sizeof(data);
    if (light_IRStyle->getState() == TransmitterIR::Idle) {
        bitcount = light_IRStyle->setData(format, data, 3*8);
    }
}
