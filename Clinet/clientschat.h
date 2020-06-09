#ifndef CLIENTSCHAT_H
#define CLIENTSCHAT_H
#include <QSharedPointer>
#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QTextEdit>
#include <QListWidget>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QIcon>
#include <QFileDialog>
#include <QMessageBox>
#include <QDirIterator>
#include <QApplication>
#include <QTableWidget>
#include <QHeaderView>
#include <QString>
#include <QLayout>
#include <QScopedPointer>
#include <QListWidgetItem>
#include <QVector>
#include <QPlainTextEdit>
#include "LoginDialog.h"
#include "Client.h"

class ClientsChat : public QWidget
{
    Q_OBJECT

public:
    QStringList List;
    QStringList ListUsers;
   QTableWidget *t;
    QTextEdit *ReadMessage;
    QTextEdit *SendMessage;
    QListWidget *OnlineUsers;
    QCheckBox *S_message_all_Users;
    QPushButton *SendButton;
    QPushButton *UploadFile;
    QPushButton *UploadImages;
    QPushButton *UploadEmotions;
    QPushButton *Logout;
    QWidget *ChatWiindow;
    QLabel *OnlineUsersList;
    QSpacerItem *spacer;
    QSpacerItem *spacer1;
    QSpacerItem *spacer2;
    QSpacerItem *spacer3;
    ClientsChat(QWidget *parent = 0);
    ~ClientsChat();


    QHBoxLayout *MainLayout;
    QHBoxLayout  *l;
    QHBoxLayout  *ll;
    QVBoxLayout  *l1;
    QVBoxLayout  *l2;
private:
    QString receiver;
    QString username;
    QString password;
    QString serverAddr;
    QString port;

    QSharedPointer<sign_in> loginDialog;
    QSharedPointer<Client> client;

    /** list of all the active private message dialogs */
    QVector<QString> privateDialogs;

    void initClient();
    void createPrivateDialog(QString username);
signals:
    void  PrivateMess(QString receiver,QString username);
    void sendPrivateMessage(QString receiver, QString message,QString sender);
    void  sendFile(QString blob, int fileSize, QString receiver, QString username);
public slots:
    void onSignUp();
    void onLogout();
    void onUploadEmotions();
    void onSignIn(QString username, QString password, QString serverAddr, QString port);
    //void onDisplayError(QAbstractSocket::SocketError socketError);
    void onReceivedMessage(QString message);
    void onSendMessage();
    void onReceivedUsersList(QString usersList);
    void itemClicked(QListWidgetItem* item);
    void onReceivedPrivateMessage(QString receiver, QString message, QString sender);
    void onItemClicked(int row, int col);
  //  void onSendFile();


};

#endif // CLIENTSCHAT_H

