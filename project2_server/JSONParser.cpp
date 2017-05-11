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
    printf("res error? %s\r\n", err.c_str());
    int left = (int)v.get("left").get<double>();
    int right =(int)v.get("right").get<double>();
    int client = (int)v.get("client").get<double>();
    // turn data into
    buf[0]= client & 0xFF;
    buf[1]= left & 0xFF;
    buf[2]= right & 0xFF;
}
