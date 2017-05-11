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

    //receiveThread.start(callback(this,&Controller::runThread));
    runningThread.start(callback(this, &Controller::run));
    //receiveThread.join();
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
        printf("%s", "receiving");
    }
}

void Controller::run() {

    while (true) {

        float left = lightCommunication->getLeft(current_left);
        float right = lightCommunication->getRight(current_right);
        car->cls();
        car->locate(0, 1);
        car->printf("Left: %0.3f Right: %0.3f", left, right);
        printf("left = %f right = %f \r\n", current_left, current_right);
        if (current_right == right && current_left == left) {
            ;
        } else if (current_right == 0 && current_left == 0) {
            car->stop();
        } else {
            current_left = left;
            current_right = right;
            car->left_motor(current_left);
            car->right_motor(current_right);
        }
        wait_ms(20);
    }

}
