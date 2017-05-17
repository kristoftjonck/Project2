#include "Controller.h"


Controller::Controller()
{
    //LCD init
    lcd = new LCD(p5, p7, p6, p8, p11);
    communication = new Communication();
    parser = new JSONParser();
    communication->setOwnID(100);
    communication->connect();
    lcd->printStart(100);
    lightCommunication = new LightCommunication();
}

Controller::~Controller()
{
    delete lcd;
    delete lightCommunication;
    delete parser;
    delete communication;
}
int Controller::run()
{
    // RECEIVE DATA FROM ETHERNET
    std::string received = communication->getData();
    // PARSE DATA
    uint8_t buffer[4];
    parser->getParsedData(received, buffer);
    //PRINT DATA ON LCD
    //lcd->printf("%X", buffer[1]);
    //SEND DATA WITH VISIBLE LIGHT
    //uint8_t buffer[] ={0x00,0x10,0x01, 0x10 + 0x};
    //printf("%X%X%X",buffer[0],buffer[1],buffer[2]);
    lightCommunication->sendSerial(buffer);
    //lightCommunication->sendIRStyle(buffer);
    //wait_ms(100);
    return 1;
}