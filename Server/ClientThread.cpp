#include "ClientThread.h"
#include "TCPServer.h"

typedef std::shared_ptr<std::list<std::unique_ptr<ClientThread>>> UserList;

ClientThread::ClientThread(TCPServer& tcpserver, UserList usersPtr, int acceptSocket) : tcpserver(&tcpserver),
        usersPtr(usersPtr) {
    this->acceptSocket = acceptSocket;

}

ClientThread::~ClientThread() {

}

void ClientThread::closeSocket() {
    close(acceptSocket);
}

void* ClientThread::run() {
    while (logoutRequest) {
        std::string package = readPackage();
        if (package.length() != 0) {
            std::cout << "received package from client: " << package << "\n";
        }

        std::string request;
        request = packaging.identifyRequest(package);
        
        if (request.compare("login_request") == 0) {
            std::cout << "request: " << "login_request" << "\n";
            onLoginRequest(package);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            sendUsersList();
        }
        else if (request.compare("logout_request") == 0) {
            std::cout << "request: " << "logout_request" << "\n";
            onLogoutRequest();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            sendUsersList();
        }
        else if (request.compare("global_package") == 0) {
            std::cout << "request: " << "global_package" << "\n";
            onGlobalMessageRequest(package);
        } else if (request.compare("private_package") == 0) {
            std::cout << "request: " << "private_package" << "\n";
            onPrivateMessageRequest(package);
        } 
    }
}

void ClientThread::sendPackage(const std::string& package) {
    //tcpserver->lockMutex();
    int res = send(acceptSocket, package.c_str(), package.length(), 0);
    if (res < 0) {
        errorMsg = "Error while sending the message to the client!";
   	perror(errorMsg.c_str());
   	exit(1);
    }
    std::cout << "Message sent to the client.\n" ;
   // tcpserver->unlockMutex();
}

void ClientThread::sendPackageToAll(const std::string& package) {
    auto list = usersPtr.get();
    std::list<std::unique_ptr<ClientThread>>::const_iterator iterator;
    tcpserver->lockMutex();
    for (iterator = list->begin(); iterator != list->end(); ++iterator) {
        (**iterator).sendPackage(package);
    }
    tcpserver->unlockMutex();
}

void ClientThread::sendPackageToTarget(const std::string& package, const std::string& target) {
    auto list = usersPtr.get();
    std::list<std::unique_ptr<ClientThread>>::const_iterator iterator;
    tcpserver->lockMutex();
    for (iterator = list->begin(); iterator != list->end(); ++iterator) {
        std::string username = (**iterator).getUsername();
        if (username.compare(target) == 0) {
            (**iterator).sendPackage(package);
            break;
        }
    }
    tcpserver->unlockMutex();
}

void ClientThread::onLoginRequest(const std::string& package) {
    int buffSize = sizeof(messageBuff);
    char sendBuff[buffSize];

    // create the new User object 
    packaging.parsePackage(package);
    std::string username = packaging.getSender();
    user = User(username);
    
    std::string outgoingPackage = packaging.createSimplePackage();
    std::cout << "package: " << outgoingPackage << "\n";
    sendPackage(outgoingPackage);
}

void ClientThread::sendUsersList() {
    std::vector<std::string> onlineUsers = tcpserver->getOnlineUsers();
    std::string package = packaging.createOnlineUsersPackage(onlineUsers);
    sendPackageToAll(package);
}

void ClientThread::onGlobalMessageRequest(const std::string& package) {
    std::cout << "Sending message to every user...\n";

    packaging.parsePackage(package);
    std::string message = packaging.getMessage();
    std::cout << "message: " << message << "\n";

    sendPackageToAll(package);
}

void ClientThread::onPrivateMessageRequest(const std::string& package) {
    packaging.parsePackage(package);
    std::string receiver = packaging.getReceiver();
    std::string message = packaging.getMessage();
    std::string sender = packaging.getSender();
    
    sendPackageToTarget(package, receiver);
}
/*
void ClientThread::sendChangedUsersList( std::string sender) {
    std::vector<std::string> newOnlineUsers;
    std::vector<std::string> onlineUsers = tcpserver->getOnlineUsers();
    for (auto it = onlineUsers.begin(); it != onlineUsers.end(); ++it) {
        std::string name = *it;
        if (name.compare(sender) != 0) {
          	newOnlineUsers.push_back(name);      
        }
	}
    std::string package = packaging.createOnlineUsersPackage(newOnlineUsers);
    sendPackageToAll(package);
}
*/
void ClientThread::onLogoutRequest() {


	std::vector<std::string> onlineUsers;
    std::string sender = packaging.getSender();
    auto list = usersPtr.get();     
    std::list<std::unique_ptr<ClientThread>>::const_iterator iterator;
    tcpserver->lockMutex();
    for (iterator = list->begin(); iterator != list->end(); ++iterator) {
        std::string name = (**iterator).getUsername();
        if (name.compare(sender) == 0) {
           list->erase(iterator);
            break;
        }
    }


   tcpserver->unlockMutex();
    for (iterator = list->begin(); iterator != list->end(); ++iterator) {
        onlineUsers.push_back((**iterator).getUsername());
    }
    
    
    closeSocket();
    std::cout << "User disconnected\n";
    pthread_exit(NULL);
    std::string package = packaging.createOnlineUsersPackage(onlineUsers);
    sendPackageToAll(package);

}

std::string ClientThread::readPackage() {
    int buffSize = sizeof(messageBuff);

    int res = recv(acceptSocket, messageBuff, buffSize, 0);
    if (res < 0) {
        errorMsg = "error when receiving the message from the client!\n";
   	perror(errorMsg.c_str());
   	exit(1);
    }
    messageBuff[res] = '\0';
    return messageBuff;
}


std::string ClientThread::getUsername() {
    return user.getUsername();
}
