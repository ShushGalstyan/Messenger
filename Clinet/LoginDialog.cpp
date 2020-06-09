#include "LoginDialog.h"
#include "clientschat.h"

sign_in::sign_in(QWidget *parent)
    : QWidget(parent)
{

    login_LineEdit = new QLineEdit();
    login_LineEdit->setPlaceholderText("Login");
    login_LineEdit->setAlignment(Qt::AlignCenter);


    ServAddr = new QLineEdit();
    ServAddr->setPlaceholderText("Server IP");
    ServAddr->setAlignment(Qt::AlignCenter);

    PortNumber = new QLineEdit();
    PortNumber->setPlaceholderText("Port Number");
    PortNumber->setAlignment(Qt::AlignCenter);

    password_LineEdit = new QLineEdit();
    password_LineEdit->setPlaceholderText("Password");
    password_LineEdit->setEchoMode(QLineEdit::Password);
    password_LineEdit->setAlignment(Qt::AlignCenter);

    login_PushButton = new QPushButton("Login");
    login_PushButton->setCheckable(true);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(login_LineEdit);
    mainLayout->addWidget(password_LineEdit);
    mainLayout->addWidget(ServAddr);
    mainLayout->addWidget(PortNumber);
    mainLayout->addWidget(login_PushButton);

    mainLayout->addStretch(1);
    setLayout(mainLayout);



    ServAddr->setPlaceholderText("Server IP addres:");
    PortNumber->setPlaceholderText("Port number:");
    /*server ip address-validator*/
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";

    QRegExp ipRegex ("^" + ipRange   + "\\." + ipRange   + "\\." + ipRange  + "\\." + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    ServAddr->setValidator(ipValidator);


     /*port number- validator*/
    QString PortRange = "([0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])(?::([0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5]))?";

    QRegExp PortRegex ("^" + PortRange  +"$");
    QRegExpValidator *PortValidator = new QRegExpValidator(PortRegex, this);
    PortNumber->setValidator(PortValidator);

    connect(login_PushButton, SIGNAL(clicked()), this, SLOT(LoginClicked()));

}





void sign_in::LoginClicked(){
    int count=0;
    login_LineEdit->setStyleSheet("margin:2px; border: 1px solid white;border-radius: 5px ;");
    password_LineEdit->setStyleSheet("margin:2px; border: 1px solid white;border-radius: 5px ;");
    if(login_LineEdit->text().isEmpty()){
        login_LineEdit->setStyleSheet("margin:2px; border: 1px solid red;border-radius: 5px ;");
        count=count+1;
    }


    if(password_LineEdit->text().isEmpty() || password_LineEdit->text().length()<6){
        password_LineEdit->setStyleSheet("margin:2px; border: 1px solid red;border-radius: 5px ;");
        count=count+1;
    }

    ServAddr->setStyleSheet("margin:2px; border: 1px solid white;border-radius: 5px ;");
    PortNumber->setStyleSheet("margin:2px; border: 1px solid white;border-radius: 5px ;");

    QString addressText=ServAddr->text();
    QStringList list = addressText.split(".");

    if(ServAddr->text().isEmpty()){
        ServAddr->setStyleSheet("margin:2px; border: 1px solid red;border-radius: 5px ;");
        count=count+1;
    }else if((list.size() < 4) or(list.size()==4 && list[list.size()-1]=="")){
        QMessageBox::information(this,"Error","Invalid Ip Address");
         ServAddr->setStyleSheet("margin:2px; border: 1px solid red;border-radius: 5px ;");
         count=count+1;
    }

    if(PortNumber->text().isEmpty()){
        PortNumber->setStyleSheet("margin:2px; border: 1px solid red;border-radius: 5px ;");
        count=count+1;
    }else if(PortNumber->text().toInt() >=0 && PortNumber->text().toInt()<=1024){
         PortNumber->setStyleSheet("margin:2px; border: 1px solid red;border-radius: 5px ;");
         QMessageBox::information(this,"Error","Port number is an unsigned short from 1-65535, ports under 1024 are reserved for system services http, ftp, etc.");
         count=count+1;
    }
    if(count==0){
        username=login_LineEdit->text();
        password=password_LineEdit->text();
        serverAddr=ServAddr->text();
        port=PortNumber->text();
        emit signIn(username, password, serverAddr, port);
        this->close();
    }

}
