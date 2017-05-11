#include "Communication.h"

Communication::Communication()
{
    //Create the ethernet interface and set the own ID
    this->ownID = 113;
    eth = new EthernetInterface();
    printf("Ethernet initialized\r\n");
}

Communication::~Communication()
{
    delete eth;
    delete server;
}


void Communication::connect()
{
    //Print the IPAddr in a char array and use it to initiate the ethernet
    char IPAddr[512];
    sprintf(IPAddr,"192.168.0.%d",ownID);
    eth->init(IPAddr, "255.255.255.0", "192.168.0.1");
    eth->connect();
    printf("Server IP Address is %s\r\n", eth->getIPAddress());

    //Create a new socket server and bind it to a port
    server = new TCPSocketServer();
    server->bind(SERVER_PORT);
    printf("Listen to port %d\r\n", SERVER_PORT);
    server->listen();
}


std::string Communication::getData()
{
    TCPSocketConnection client;
    server->accept(client);
    //client.set_blocking(false, 5000);

    /* receives the data in a char array buffer and prints this
     * byte per byte in an std::string (prevents null values to stop the copy)
     */
    std::string str;
    char buffer[512];
    while (true) {
        int n = client.receive(buffer, 512);

        if (n <= 0) break;
        printf("size of the packet:'%d'\r\n",n);
        // print received message to terminal
        buffer[n] = '\0';

        str = buffer;
        
        printf("%s \r\n", str.c_str());
        break;
    }
    client.close();
    return str;

}

void Communication::setOwnID(int i)
{
    this->ownID = i;
}

int Communication::getOwnID()
{
    return this->ownID;
}
