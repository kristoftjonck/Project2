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
};


#endif //PROJ2_JSONPARSER_H
