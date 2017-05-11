#ifndef LCD_H
#define LCD_H

#include "mbed.h"
#include "C12832.h"

/** LCD class (extended from 12832)
 *  Class to control an RGB LED using three PWM pins
 */
class LCD: public C12832
{
public:

    /** 
      * Create a C12832 object connected to SPI1
      */
    LCD(PinName mosi, PinName sck, PinName reset, PinName a0, PinName ncs);
    
    /** 
      * Prints some strings and a destinationID used in the run from IOController
      * @param destID the destination ID
      */
    void printStart(int destID);

    /**
     * prints out json received data on the LCD
     * @param client
     * @param left
     * @param right
     */
    void printJSON(int client, int left, int right);
};

#endif