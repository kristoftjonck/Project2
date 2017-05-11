#ifndef Communication_H
#define Communication_H
#include <mbed.h>
#include <string>

#include "EthernetInterface.h"

#define SERVER_PORT   4000

/** Communication class.
 *  Utilised to make use of the EthernetInterface to receive packets
 *  with the help of a TCPSocketServer, but also to send packets to other clients
 *  with a TCPSocketConnection
 */
class Communication{ 
 public: 
   
    /** Default Constructor
    *   Creates an object of the Communication class, which 
    *   will automaticly connect to the EthernetInterface.
    */
    Communication();
         
    /** Destructor 
    *   Destroys all the objects using memory with this class
    *   and disconnects the connections made by the class.
    */
    ~Communication();
    
    /** Connects to internet with the help of the EthernetInterface
    *   and manualy sets the ip address, it also generates a TCPSocketServer
    *   to be able to receive data.
    */
    void connect();
    
    /** Creates a TCPSocketConnection "client" to receive a Packet from a client
    *   by accepting it with the TCPSocketServer "server"
    *   @param buffer The reference to a std::string buffer that has to be 
    *   filled with the received data Packet.
    */
   std::string getData();
    
    /** 
    *   Sets the ID where the MBED has to connect to
    *
    */
    void setOwnID(int i);

    int getOwnID();
  
 private:
 
    /**
    *   An instance of the TCPSocketServer to be able to receive data.
    */
    
    TCPSocketServer * server;
    /**
    *   An instance of the EthernetInterface class that will make it possible 
    *   to connect to the internet.
    */
    EthernetInterface * eth;  
    
    int ownID;
};

#endif