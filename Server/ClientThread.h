#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <cstring>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

#include <chrono>
#include <thread>
#include <list>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

#include "Packaging.h"
#include "MyThread.h"
#include "User.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
class TCPServer;

class ClientThread : public MyThread {
    typedef std::shared_ptr<std::list<std::unique_ptr<ClientThread>>> UserList;
public:
    explicit ClientThread(TCPServer& tcpserver, UserList usersPtr, int acceptSocket);
    virtual ~ClientThread();
    
    virtual void* run();
    
    void onLoginRequest(const std::string& package);
    void onLogoutRequest();
    void onGlobalMessageRequest(const std::string& package);
    void onPrivateMessageRequest(const std::string& package);

    
    bool logoutRequest = true;
    
    void closeSocket();

    std::string getUsername();
    
private:
    int acceptSocket;
    char messageBuff[2048];
    
    User user;
    void sendPackage(const std::string& package);

    std::string readPackage();


    

    void sendPackageToAll(const std::string& package);
    void sendPackageToTarget(const std::string& package, const std::string& target);
    void sendUsersList();
    void sendChangedUsersList( std::string sender);

    std::shared_ptr<TCPServer> tcpserver;
    Packaging packaging;
    UserList usersPtr;
};

#endif 
