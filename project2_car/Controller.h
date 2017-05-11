//
// Created by Kristof on 5/9/2017.
//

#ifndef PROJ2_CAR_CONTROLLER_H
#define PROJ2_CAR_CONTROLLER_H


#include "ReceiverIR.h"
#include "m3pi.h"
#include "LightCommunication.h"
#include "rtos.h"

class Controller {
public:
    /**
     * Constructor
     */
    Controller();

    /**
     * Destructor
     */
    ~Controller();

    /**
     * Drives with the car, started within a thread
     */
    void run();

    /**
     * Receives data
     * @deprecated Not used anymore, using serial interrupt instead
     */
    void runThread();

private:
    /**
     *
     */
    m3pi *car;

    /**
     * Thread to receive data
     * @deprecated Recplaced by a serial interrupt
     */
    Thread receiveThread;

    /**
     * Thread to update according to the data received
     */
    Thread runningThread;

    /**
     * Pointer to the lightcommunication
     */
    LightCommunication *lightCommunication;

    /**
     * current speed the car is driving with
     */
    float current_left, current_right;

};


#endif //PROJ2_CAR_CONTROLLER_H
