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
    buf[3] = ((buf[1] + buf[2] + 127) % 251) & 0xFF;
}
