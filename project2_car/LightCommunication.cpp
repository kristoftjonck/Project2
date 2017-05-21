//
// Created by Kristof on 5/9/2017.
//

#include "LightCommunication.h"



LightCommunication::LightCommunication()
{
    left= 0;
    right = 0;
    ir_rx = new ReceiverIR(p21);
    device = new Serial(p13,p14);
    mut = new Mutex();
    device->baud(9600);
    //device->attach(callback(this,&LightCommunication::receiveData), Serial::RxIrq);
}

LightCommunication::~LightCommunication()
{
    delete mut;
    delete device;
    delete ir_rx;
}

void LightCommunication::getIRStyle(uint8_t * buf)
{
    RemoteIR::Format format;
    if (ir_rx->getState() == ReceiverIR::Received) {
        ir_rx->getData(&format, buf, sizeof(buf) * 8);
    }
}

void LightCommunication::receiveData()
{
    uint8_t data [4];
    //SERIAL RECEIVE
    //if(device->scanf("%c%c%c",data[0],data[1],data[2])>0) {
        if (device->readable()){
            data[0] = device->getc();
            
            
        printf("DATA");
        printf("Received data: client:%d \r\n",data[0]);
        if (OWN_ID == (int) data[0]) {
            data[1] = device->getc();
            data[2] = device->getc();
            data[3] = device->getc();
            printf("%X%X%X%X",data[0],data[1],data[2],data[3]);
            //if(data[3] ==  (((data[1] + data[2] + 127) % 251) & 0xFF)){
            if (LightCommunication::crc(data,data[3]) !=0)
                mut->lock();
                left = LightCommunication::toFloat(data[1]);
                right = LightCommunication::toFloat(data[2]);

                printf("DATA left = %f right = %f \r\n",left,right);
                mut->unlock();
            }
        }
    }
}

float LightCommunication::getRight(float cur_right)
{
    float r = right;
    mut->unlock();
    return r;
/*
    float r = right - cur_right;

    float cur_speed = 0;
    if (r>0.0f) {
        cur_speed = (float)(cur_right + (0.005*SPEED));
    } else if (r<0.0f) {

        cur_speed = (float)(cur_right - (0.005*SPEED));
    } else {
        cur_speed = cur_right;
    }
    mut->unlock();
    return cur_speed;
    */
}

float LightCommunication::getLeft(float cur_left)
{
    mut->lock();
    float l = left;
    
    return l;
/*
    mut->lock();
    float l = left - cur_left;
    if (l>0.0f) {
    printf("lefdif: %f\r\n",l);
        return (float)(cur_left + (0.005*SPEED));
    } else if (l<0.0f) {
        return (float)(cur_left - (0.005*SPEED));
    } else {
        return cur_left;
    }*/
    
}

float LightCommunication::toFloat(int8_t a)
{
    return (((float)a)/100.0f)*SPEED;
}

bool LightCommunication::needsToStop()
{
    mut->lock();
    bool stop = right == 0 && left == 0;
    mut->unlock();
    return stop;
}

/**
 *  EXAMPLE CRC CHECK : 0xAA00FF55 => checksum = 0x39
 *  0xAA          0x00              0xFF            0x55
 *  1 0 1 0 1 0 1 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 | 0 0 0 0 0 0
 *  1 0 1 0 0 1 1 | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
 *  0 0 0 0 1 1 0 0 0 0 0 | | | | | | | | | | | | | | | | | | | | | | | | | | | |
 *          1 0 1 0 0 1 1 | | | | | | | | | | | | | | | | | | | | | | | | | | | |
 *          0 1 1 0 0 1 1 0 | | | | | | | | | | | | | | | | | | | | | | | | | | | //102
 *            1 0 1 0 0 1 1 | | | | | | | | | | | | | | | | | | | | | | | | | | |
 *            0 1 1 0 1 0 1 0 | | | | | | | | | | | | | | | | | | | | | | | | | | //106
 *              1 0 1 0 0 1 1 | | | | | | | | | | | | | | | | | | | | | | | | | |
 *              0 1 1 1 0 0 1 0 | | | | | | | | | | | | | | | | | | | | | | | | | //114
 *                1 0 1 0 0 1 1 | | | | | | | | | | | | | | | | | | | | | | | | |
 *                0 1 0 0 0 0 1 0 | | | | | | | | | | | | | | | | | | | | | | | | //66
 *                  1 0 1 0 0 1 1 | | | | | | | | | | | | | | | | | | | | | | | |
 *                  0 0 1 0 0 0 1 0 1 | | | | | | | | | | | | | | | | | | | | | | //69
 *                      1 0 1 0 0 1 1 | | | | | | | | | | | | | | | | | | | | | |
 *                      0 0 1 0 1 1 0 1 1 | | | | | | | | | | | | | | | | | | | | //91
 *                          1 0 1 0 0 1 1 | | | | | | | | | | | | | | | | | | | |
 *                          0 0 0 1 0 0 0 1 1 1 | | | | | | | | | | | | | | | | | //71
 *                                1 0 1 0 0 1 1 | | | | | | | | | | | | | | | | |
 *                                0 0 1 0 1 0 0 1 1 | | | | | | | | | | | | | | | // 83
 *                                    1 0 1 0 0 1 1 | | | | | | | | | | | | | | |
 *                                    0 0 0 0 0 0 0 0 1 0 1 0 1 0 1 | | | | | | | //85
 *                                                    1 0 1 0 0 1 1 | | | | | | |
 *                                                    0 0 0 0 1 1 0 | 0 0 0 0 | | //96
 *                                                            1 0 1 | 0 0 1 1 | |
 *                                                            0 1 1 | 0 0 1 1 0 | //102
 *                                                              1 0 | 1 0 0 1 1 |
 *                                                              0 1 | 1 0 1 0 1 0 //106
 *                                                                1 | 0 1 0 0 1 1
 *                                                                0 | 1 1 1 0 0 1 //57 = 0x39
 * using this algorithm gives the same values.
 */
unsigned char LightCommunication::crc(uint8_t message[],unsigned char chk)
{
    int nBytes = 3;
    char remainder = 0;
    /**
     * Shifts the checksum 2 bits to the right,
     * the checksum is of the form 0b00xx xxxx,
     * so this has to get shifted to 0bxxxx xx00 to do the check
     */
    char check = chk<<2;

    /*
    * Perform modulo-2 division, bit by bit, byte by byte
    */

    for (int byte = 0; byte < nBytes; byte++) {
        for (char bit = 8; bit > 0; --bit) {
            /*
            * Try to divide the current data bit.
            */
            if (remainder & 0x40) {
                remainder = (remainder ^ 0x53) & 0x7F;
                remainder = (remainder << 1) | (0x01 & (message[byte]>>(bit-1)) & 0x7F);
            } else {
                remainder = ((remainder << 1) | (0x01 & (message[byte]>>(bit-1))) & 0x7F);
            }
        }
    }

    /*
     * Perform modulo-2 division, this for only the 6 bits of the chk value
     * will be performed 7 times but the trailing 0 will be removed later
     */
    for (char bit = 7; bit > 0; --bit) {
        /*
        * Try to divide the current data bit.
        */
        if (remainder & 0x40) {
            remainder = (remainder ^ 0x53) & 0x7F;
            remainder = (remainder << 1) | (0x01 & (check >> bit)) & 0x7F;
        } else {
            remainder = ((remainder << 1) | (0x01 & (check >> bit))) & 0x7F;
        }
    }
    /*
     *  Remove the trailing 0 that has been shifted and has to be removed
     */
    remainder = remainder >>1;
    return (remainder);

}
