#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <list>
#include <vector>

#include "ClientThread.h"

typedef std::shared_ptr<std::list<std::unique_ptr<ClientThread>>> UserList;

/** synchronous TCP server where every client is managed in their own separate thread */
class TCPServer {
public:
    TCPServer(const char* address = "127.0.0.1", int port = 5000);
    virtual ~TCPServer();
    
    void startServer();
    std::vector<std::string> getOnlineUsers();
    
    void lockMutex() { pthread_mutex_lock(&mutex); }
    void unlockMutex() { pthread_mutex_unlock(&mutex); }
    void signalCondition() { pthread_cond_signal(&condition); }
 private:
    const char* address;
    int port;


    int listenSocket;
    int acceptSocket;
    struct sockaddr_in serverAddr;

    std::string errorMsg;

    int res;
    
    // thread for every user 
    std::list<std::unique_ptr<ClientThread>> clientThreads;
    // pointer to the list of clients
    UserList usersPtr;
    
    pthread_mutex_t mutex;
    pthread_cond_t condition;
    
    void initServer();
    void listenServer();
};

#endif /* TCPSERVER_H */

