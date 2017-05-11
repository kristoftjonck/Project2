#ifndef IOController_H
#define IOController_H
#include <mbed.h>

#include "LCD.h"
#include "Communication.h"
#include "LightCommunication.h"
#include "JSONParser.h"

/** Controller class
 *  Controls both the input(TemperatureSensor, Potentiometer, Joystick) and
 *  output(Speaker, RGB, LCD ) devices. And uses the Communication class to send
 *  the read input data to an other client.
 */

class Controller
{
public:

    /**
     *  Makes an instance of the IOController class, this will initialize 
     *  all the IO devices
     */
    Controller();
    
    /**
     *  Deletes the IOController and calls the destructor from
     *  all the IO devices
     */
    ~Controller();
    
    /**
     *  The main run method used in a loop for controlling the IO Devices
     */
    int run();
    

private:

    
    /**
     *  Pointer to an object of the class LCD
     *
     *  @ref LDC
     */
    LCD * lcd;

    /**
     *  Pointer to an object of the class Communication
     *  @ref Communication
     */
    Communication * communication;

    /**
     * Pointer to an object of the class lightCommunication to send data via light
     */
    LightCommunication * lightCommunication;

    /**
     * Pointer to a JSONParser to parse data
     */
    JSONParser * parser;

};

#endif