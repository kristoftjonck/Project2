//
// Created by Kristof on 5/9/2017.
//

#include "LightCommunication.h"



LightCommunication::LightCommunication()
{
    ir_rx = new ReceiverIR(p21);
    device = new Serial(p13,p14);
    mut = new Mutex();
    left= 0;
    right = 0;
    device->baud(19200);
    device->attach(callback(this,&LightCommunication::receiveData), Serial::RxIrq);
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
    //SERIAL RECEIVE
    if(device->readable()) {
        uint8_t data [128];
        device->scanf("%s",data);
        printf("Received data: client:%d left: %d right:%d \r\n",data[0],data[1],data[2]);
        if (OWN_ID == (int) data[0]) {
            mut->lock();
            left = LightCommunication::toFloat(data[1]);
            right = LightCommunication::toFloat(data[2]);

            printf("DATA left = %f right = %f \r\n",left,right);
            mut->unlock();
        }
    }
}

float LightCommunication::getRight(float cur_right)
{

    float r = right - cur_right;

    float cur_speed = 0;
    if (r>0) {
        cur_speed = (float)(cur_right + (0.005*SPEED));
    } else if (r<0) {

        cur_speed = (float)(cur_right - (0.005*SPEED));
    } else {
        cur_speed = right;
    }
    mut->unlock();
    return cur_speed;
}

float LightCommunication::getLeft(float cur_left)
{

    mut->lock();
    float l = left - cur_left;
    if (l>0) {
        return (float)(cur_left + (0.005*SPEED));
    } else if (l<0) {
        return (float)(cur_left - (0.005*SPEED));
    } else {
        return cur_left;
    }
    //return left;
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


