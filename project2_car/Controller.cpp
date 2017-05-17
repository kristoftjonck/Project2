//
// Created by Kristof on 5/9/2017.
//

#include "Controller.h"

Controller::Controller() {

    current_left = 0;
    current_right = 0;
    //MAKES A NEW LIGHTCOMMUNICATION (starts receiving on serial)
    lightCommunication = new LightCommunication();
    car = new m3pi();
    car->stop();
    receiveThread.start(callback(this,&Controller::runThread));
    runningThread.start(callback(this, &Controller::run));
    receiveThread.join();
    runningThread.join();


}

Controller::~Controller() {
    delete car;
    delete lightCommunication;
}

/**
 *
 */
void Controller::runThread() {
    while (true) {
        lightCommunication->receiveData();
    }
}

void Controller::run() {

    while (true) {
    /*if (lightCommunication->needsToStop()){
        car->stop();
    }else {
        current_left = lightCommunication->getLeft(current_left);
        current_right = lightCommunication->getRight(current_right);
        car->left_motor(current_left) ;
        car->right_motor(current_right) ;
    }*/
        float left = lightCommunication->getLeft(current_left);
        float right = lightCommunication->getRight(current_right);
        //car->cls();
        //car->locate(0, 1);
        //car->printf("Left: %0.3f Right: %0.3f", left, right);
        if (current_right == right && current_left == left) {
             current_left = left;
            current_right = right;
            ;
        } else if (right == 0 && left == 0) {
             current_left = left;
            current_right = right;
            car->stop();
        } else {
            current_left = left;
            current_right = right;
            
        printf("cur_left = %f cur_right = %f \r\n", current_left, current_right);
            car->left_motor(current_left);
            car->right_motor(current_right);
        }
    }

}
