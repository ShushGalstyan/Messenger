#include "clientschat.h"
ClientsChat::ClientsChat(QWidget *parent)
    : QWidget(parent)
{
    ChatWiindow = new QWidget;
    ChatWiindow->setFixedSize(725,685);
    ChatWiindow->setWindowTitle("Chat");
    UploadFile =new  QPushButton;
    UploadImages =new  QPushButton;
    UploadEmotions =new  QPushButton;
    ReadMessage=new QTextEdit;
    SendMessage = new QTextEdit;
    OnlineUsers = new QListWidget;
    S_message_all_Users = new QCheckBox;
    SendButton = new QPushButton("Send message");
    Logout = new QPushButton("Logout");
    OnlineUsersList = new QLabel("Online Users");
    MainLayout=new QHBoxLayout ;
    spacer = new QSpacerItem(580, 20, QSizePolicy::Fixed);
    spacer1 = new QSpacerItem(286, 30, QSizePolicy::Fixed);
    spacer2 = new QSpacerItem(100, 30, QSizePolicy::Fixed);
    spacer3=new QSpacerItem(200, 20, QSizePolicy::Fixed);


    UploadEmotions->setIcon(QIcon(QPixmap(":/Icons/Icons/icons8-lol-48.png")));
    UploadEmotions->setIconSize(QSize(30,30));

    l=new QHBoxLayout;
    ll=new QHBoxLayout;
    l1=new QVBoxLayout;
    l2=new QVBoxLayout;

    l->addWidget(UploadEmotions);
    l->addItem(spacer1);
    l->addWidget(SendButton);

    ll->addItem(spacer2);
    ll->addWidget(Logout);

    l1->addWidget(ReadMessage);
    l1->addWidget(SendMessage);
    l1->addItem(spacer);
    l1->addLayout(l);

    l2->addWidget(OnlineUsersList);
    l2->addWidget(OnlineUsers);
    l2->addWidget(S_message_all_Users);
    l2->addItem(spacer3);
    l2->addLayout(ll);

    ReadMessage->setFixedSize(500,500);
    SendMessage->setFixedSize(500,100);
    SendButton->setFixedSize(140,30);
    OnlineUsersList->setFixedSize(200,30);
    OnlineUsers->setFixedSize(200,550);
    Logout->setFixedSize(100,30);
    UploadEmotions->setFixedSize(30,30);
    MainLayout->addLayout(l1);
    MainLayout->addLayout(l2);

    ReadMessage->setReadOnly(true);
    UploadEmotions->setStyleSheet("border-radius: 18px ;");
    SendButton->setStyleSheet("border: 1px solid rgb(24, 103, 155); border-radius: 5px ; background-color: rgb(124, 203, 255); color: white;");
    OnlineUsersList->setStyleSheet("border: 1px solid rgb(24, 103, 155); border-radius: 5px ; background-color: rgb(124, 203, 255); color: white;");
    Logout->setStyleSheet("border: 1px solid rgb(24, 103, 155); border-radius: 5px ; background-color: grey; color: white;");


    ChatWiindow->setLayout(MainLayout);



    connect(Logout,SIGNAL(clicked()),  SLOT(onLogout()));
    connect(UploadEmotions,SIGNAL(clicked()),  SLOT(onUploadEmotions()));

    loginDialog = QSharedPointer<sign_in>::create();
    loginDialog->show();
    connect(loginDialog.data(), &sign_in::signIn, this, &ClientsChat::onSignIn); // data(): extracts the raw pointer
    connect(SendButton, &QPushButton::clicked, this, &ClientsChat::onSendMessage);
    connect(OnlineUsers, &QListWidget::itemClicked, this, &ClientsChat::itemClicked);
    connect(OnlineUsers,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(itemClicked(QListWidgetItem*)));
}
void ClientsChat::itemClicked(QListWidgetItem *item){
    this->receiver = item->text();
}

void ClientsChat::onSignUp()
{
    ChatWiindow->show();
}

void ClientsChat::onUploadEmotions(){
    List = QStringList();
    t=new QTableWidget;
   t->setFixedSize(255,250);
    int row=20,col=8;
   t->resize(300,240);
   t->verticalHeader()->hide();
   t->horizontalHeader()->hide();
   t->verticalHeader()->setDefaultSectionSize(30);
   t->horizontalHeader()->setDefaultSectionSize(30);
   t->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
   t->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
   t->setRowCount(row);
   t->setColumnCount(col);
   t->setFocusPolicy(Qt::StrongFocus);
   t->setEditTriggers(QAbstractItemView::NoEditTriggers);
   t->setSelectionMode(QAbstractItemView::SingleSelection);
   t->setShowGrid(false);
    QDirIterator it(":/Emoji", QDirIterator::Subdirectories);

     for (int r = 0; r <t->rowCount(); r++)
         {
            for (int c = 0; c <t->columnCount(); c++)
            {
                QTableWidgetItem* item = new QTableWidgetItem;
               t->setIconSize(QSize(20,20));
                List <<it.next();
                item->setIcon(QIcon(QString(it.next())));
               t->setItem(r, c, item);
            }
         }
     t->show();
     connect(t, SIGNAL(cellClicked(int,int)), SLOT(onItemClicked(int,int)));

}

void ClientsChat::onItemClicked(int row , int col )
{
        qDebug()<<"row "<<row <<"   col  " << col << "  ***  "<< (((row) * 8) + col)<<endl;

     t->close();
     QString emojiPath = " <img src=" + List.at(((row) * 8) + col  ) + " height=16 width=16>";
     QString Path =List.at(((row) * 8) + col );
     QString html;
     html.append(emojiPath);
     SendMessage->setFocus();
     SendMessage->insertHtml(html);
     SendMessage->setFontPointSize(0.00001);
     SendMessage->insertPlainText(" " + Path +" " );
     SendMessage->setFontPointSize(10);

     SendMessage->setFocus();

}


void ClientsChat::onLogout()
{
    ChatWiindow->close();
}

void ClientsChat::onSignIn(QString username, QString password, QString serverAddr, QString port) {
    this->username = username;
    this->password = password;
    this->serverAddr = serverAddr;
    this->port = port;
    this->setWindowTitle(username);
    initClient();
}

void ClientsChat::initClient() {
    QString username = this->username;
    client = QSharedPointer<Client>::create(serverAddr, port, username);
    connect(client.data(), &Client::receivedMessage, this, &ClientsChat::onReceivedMessage);
    connect(client.data(), &Client::receivedUsersList, this, &ClientsChat::onReceivedUsersList);
    connect(client.data(), &Client::receivedPrivateMessage, this, &ClientsChat::onReceivedMessage);
    connect(this->Logout, &QPushButton::clicked, client.data(), &Client::onLogoutRequest);
    client->connectToServer();
    ChatWiindow->show();
}


void ClientsChat::onReceivedMessage(QString message) {
    ReadMessage->append(message);
}

void ClientsChat::onReceivedUsersList(QString usersList) {
    size_t pos = 0;
    std::string token;
    std::string inputStr = usersList.toStdString();
    while ((pos = inputStr.find(",")) != std::string::npos) {
        token = inputStr.substr(0, pos);
        QString text = QString::fromStdString(token);
        if ((OnlineUsers->findItems(text, Qt::MatchExactly).size()) == 0 && text != this->username) {
            OnlineUsers->addItem(text);
        }
        inputStr.erase(0, pos + 1);
    }
}

void ClientsChat::onReceivedPrivateMessage(QString receiver, QString message, QString sender) {
  ReadMessage->append(message);
}


void ClientsChat::onSendMessage() {
    SendMessage->setTextColor( QColor( "black" ) );

    QString new_message;
    QString mess;
    QString message = SendMessage->toPlainText();

    QByteArray TextArray = message.toUtf8();
    int i=0;
    while(int(TextArray[i]) != 0){
        if(int(TextArray[i]) == 58){
            new_message = new_message + "<img src=" ;
            while(int(TextArray[i]) != 32){
                new_message = new_message +TextArray[i];
                i++;
            }
            new_message=new_message + " height=16 width=16>  " +"  ";
        }else{
            new_message = new_message +TextArray[i];
            i++;
        }

    }
    QByteArray TextArray1 = new_message.toUtf8();

    for(i=0; i<TextArray1.length(); i++){
        if(int(TextArray1[i])>=0 && int(TextArray1[i])<=127){
           mess=mess + TextArray1[i];
        }else{
            continue;
        }
    }

    if(S_message_all_Users->isChecked()  && receiver.length()==0){

        client->onGlobalPackage(mess);
        SendMessage->clear();
    }else if(S_message_all_Users->isChecked()  && receiver.length()>0){
        QString receiver="global";
        client->onGlobalPackage(mess);
        SendMessage->clear();
    }
    else if(receiver.length()>0 && !(S_message_all_Users->isChecked()) ){
        QString message = SendMessage->toPlainText();
        QString message1= username+": " + mess;
        client->onSendPrivateMessage(receiver,message,username);
        ReadMessage->append( message1);
        SendMessage->clear();
    }

}

ClientsChat::~ClientsChat()
{

}
