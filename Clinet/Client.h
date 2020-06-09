#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QDebug>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <string>
#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include <QMessageBox>
#include <QThread>
#include <QtConcurrent>
#include "Packaging.h"
#include <stdlib.h>     /* exit, EXIT_FAILURE */
struct sockaddr_in;

class Client : public QObject {
    Q_OBJECT
friend class ClientsChat;

public:
    explicit Client(QObject* parent = 0);
    Client(QString serverAddr = "127.0.0.1", QString portNr = "5000", QString username = "user");

    QString getUsername() { return username; }

    void connectToServer();
    void sendPackage(QString package);

private:
    QString serverAddr;
    QString portNr;

    QString username;

    int socket_descriptor;
    struct sockaddr_in server_addr;

    Packaging packaging;

signals:
    void readyRead();
    void error();
    void login();
    void receivedMessage(QString message);
    void receivedUsersList(QString usersList);
    void onUsersList(QString usersList);
    void receivedPrivateMessage(QString receiver, QString message, QString sender);

public slots:
    void onLoginRequest();
    void onReadMsg();
    void onLogoutRequest();
    void onGlobalPackage(QString message);
    void onSendPrivateMessage(QString receiver, QString message, QString sender);
};

#endif
