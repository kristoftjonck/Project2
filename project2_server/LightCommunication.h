//
// Created by Kristof on 5/9/2017.
//

#ifndef PROJ2_LIGHTCOMMUNICATION_H
#define PROJ2_LIGHTCOMMUNICATION_H

#include "TransmitterIR.h"


class LightCommunication {
public:

    /**
     * Constructor
     */
    LightCommunication();

    /**
     * Destructor
     */
    virtual ~LightCommunication();

    /**
     * Sends the data using serial UART
     * @param data
     */
    void sendSerial(uint8_t data[]);

    /**
     * Sends data using NEC formatted packets (like IR)
     * @param data
     */
    void sendIRStyle(uint8_t data[]);

private:

    /**
     * Pointer to a TransmitterIR used to transmit via IR
     */
    TransmitterIR *light_IRStyle;

    /**
     * Pointer to a serial to send data with uart
     */
    Serial *light_serial;
};


#endif //PROJ2_LIGHTCOMMUNICATION_H
