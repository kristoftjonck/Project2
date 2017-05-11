#include "LCD.h"

LCD::LCD(PinName mosi, PinName sck, PinName reset, PinName a0, PinName ncs):C12832(mosi, sck, reset, a0, ncs)
{

}

void LCD::printStart(int destID)
{
    cls();
    locate(0,3);
    this->printf("Own ip: 192.168.0.%d\n", destID);
}

void LCD::printJSON(int client, int left, int right)
{
    cls();
    locate(0,3);
    this->printf("left =%d\r\n" ,  left);
    this->printf("right =%d\r\n" ,  right);
    this->printf("client =%d\r\n" ,  client);
}