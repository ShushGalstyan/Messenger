#include "TCPServer.h"
#include <iostream>
int main(int argc, char *argv[]) {
    std::string address = "127.0.0.1";
    if (argc < 2) {
        std::cout<< "ERROR, no port provided"<<std::endl;
        exit(1);
     }else{
    	int port = atoi(argv[1]);
         TCPServer tcpServer(address.c_str(), port);
         tcpServer.startServer();
    }
    return 0;
}

