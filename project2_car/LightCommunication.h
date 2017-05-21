//
// Created by Kristof on 5/9/2017.
//

#ifndef PROJ2_LIGHTCOMMUNICATION_H
#define PROJ2_LIGHTCOMMUNICATION_H

#include <cstdint>
#include "stdio.h"
#include "rtos.h"
#include "ReceiverIR.h"

#define OWN_ID 0
#define SPEED 0.5f //0-1

class LightCommunication {
public:

    /**
     * Constructor
     */
    LightCommunication();

    /**
     * Destructor
     */
    ~LightCommunication();

    /**
     * Gets the left value with a calculation done every loop
     * @return a right value
     */
    float getRight(float);

    /**
     * Gets the left value with a calculation done every loop
     * @return a left value
     */
    float getLeft(float);

    /**
     * Receives data via Serial into a buffer
     * @deprecated using receiveData instead
     * @param buf
     */
    void getSerial(char * buf);

    /**
     * Receives data with NEC protocol
     * @deprecated Not using NEC anymore
     * @param buf
     */
    void getIRStyle(uint8_t* buf);

    /**
     *
     */
    void receiveData();

    /**
     * @deprecated checked in the controller instead
     * @return
     */
    bool needsToStop();

    /**
        * Calculates the crc checksum of a given string, ending with a trailing character
        * chk.
        * - If this check byte is zero it will calculate the crc checksum itself
        * - If the check byte has a value, the returned char will be 0 if chk is
        *      the correct checksum value.
        *
        * @param str the string where the checksum has to be calculated from
        * @param chk the checksum value that has to be checked (will be 0 if the crc checksum has to be calculated)
        *
        * @return the calculated checksum char
        */
    unsigned char crc(uint8_t * str, unsigned char chk);


private:
    float right,left;

    /**
     * Receives the data using NEC protocol
     * @deprecated Not using this anymore, using serial instead
     */
    ReceiverIR * ir_rx;

    /**
     * Pointer to a device
     */
    Serial * device;

    /**
     * Pointer to a mutex
     */
    Mutex * mut;

    /**
     * Converts a received int8_t to a float (data/100)*speed
     * @return float value
     */
    float toFloat(int8_t data);

};


#endif //PROJ2_LIGHTCOMMUNICATION_H
