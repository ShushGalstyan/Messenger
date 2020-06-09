#include "Client.h"


Client::Client(QObject* parent) : QObject(parent) {}

Client::Client(QString serverAddr, QString portNr, QString username) {
    this->serverAddr = serverAddr;
    this->portNr = portNr;
    this->username = username;

    socket_descriptor = 0;
    server_addr.sin_addr.s_addr = inet_addr( serverAddr.toStdString().c_str() );
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons( portNr.toInt() );

    socket_descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    QtConcurrent::run(this,&Client::onReadMsg);
    connect(this, &Client::login, this, &Client::onLoginRequest);


}

void Client::connectToServer() {

    /** connect to the main server */
    ::connect(socket_descriptor, (struct sockaddr *) &server_addr, sizeof(server_addr));
        emit login();

}

void Client::onLoginRequest() {
    std::string package = packaging.createLoginPackage(username.toStdString());
    sendPackage(QString::fromStdString(package));
}

void Client::onLogoutRequest() {
    std::string package = packaging.createDisconnectPackage();
    sendPackage(QString::fromStdString(package));
}

void Client::onGlobalPackage(QString message) {
    std::string package = packaging.createGlobalPackage(message.toStdString(), username.toStdString());
    sendPackage(QString::fromStdString(package));
}

void Client::onReadMsg() {
    while(1)
    {

        char res[2048];
        int m=recv(socket_descriptor, (void*)res, sizeof(res), 0);
        if(m == -1){
                exit (EXIT_FAILURE);
        }
        QString package = QString(res);
        packaging.parsePackage(package.toStdString());
        QString sender = QString::fromStdString(packaging.getSender());
        QString message = QString::fromStdString(packaging.getMessage());
        QString receiver = QString::fromStdString(packaging.getReceiver());
        std::string request = packaging.identifyRequest(package.toStdString());
        QString output;

         if (request.compare("online_users_package") == 0) {
            emit receivedUsersList(message);
        }
        else if (request.compare("global_package") == 0) {
            output = sender + ": " + message;
            emit receivedMessage(output);
        }
        else{
            QString output=sender+": "+message;
                emit receivedMessage(output);
        }
    }
}


void Client::sendPackage(QString package) {

    /** encode the message into a byte array */
    QByteArray messageBlock = package.toUtf8();;

    char buff[2048];
    std::memcpy(buff,messageBlock.data(), 2048);

    send(socket_descriptor, (char*)&buff, sizeof(buff), 0);
}

void Client::onSendPrivateMessage(QString receiver, QString message, QString sender) {
    std::string package = packaging.createPivatePackage(receiver.toStdString(), message.toStdString(), sender.toStdString());
    sendPackage(QString::fromStdString(package));
}


