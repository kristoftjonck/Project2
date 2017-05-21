//
// Created by Kristof on 5/9/2017.
//

#include "JSONParser.h"

JSONParser::JSONParser() {

}

JSONParser::~JSONParser() {

}

void JSONParser::getParsedData(std::string received, uint8_t * buf) {
    // PARSE JSON DATA
    picojson::value v;
    const char *json = received.c_str();
    std::string err = picojson::parse(v, json, json + strlen(json));
    int left = 0;
    int right = 0;
    int client = 0;
    if (err.empty()){
    printf("res error? %s\r\n", err.c_str());
    left = (int)v.get("left").get<double>();
    right =(int)v.get("right").get<double>();
    client = (int)v.get("client").get<double>();
    }
    // turn data into
    buf[0]= client & 0xFF;
    buf[1]= left & 0xFF;
    buf[2]= right & 0xFF;
    //buf[3] = ((buf[1] + buf[2] + 127) % 251) & 0xFF;
    buf[3] = JSONParser::crc(buf,0);
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
unsigned char JSONParser::crc(uint8_t message[],unsigned char chk)
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