#ifndef PROJ2_JSONPARSER_H
#define PROJ2_JSONPARSER_H

#include <string>
#include "mbed.h"
#include "picojson.h"

/**
 * Parses a JSON string into other data
 */
class JSONParser {
public:

    /**
     * Constructor
     */
    JSONParser();

    /**
     * Destructor
     */
    virtual ~JSONParser();

    /**
     * Parses the data from a std::string into the buffer buf
     * @param string
     * @param buf
     */
    void getParsedData(std::string string, uint8_t * buf);
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

};


#endif //PROJ2_JSONPARSER_H
