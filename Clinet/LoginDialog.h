#ifndef SIGN_IN_H
#define SIGN_IN_H
#include <QDialog>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QSharedPointer>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFile>
class ClientsChat;


class TabDialog : public QDialog
{
    Q_OBJECT

public:

    explicit TabDialog(QWidget *parent = 0);
    QWidget *TabWindows;
    QVBoxLayout *mainLayout;
    QTabWidget *tabWidget;
};


class sign_in : public QWidget
{
    Q_OBJECT

public:
   // QSharedPointer<IPAndPort> ip_port;
    TabDialog *thisDialog;
    QLineEdit *ServAddr;
    QLineEdit *PortNumber;
    QLineEdit *login_LineEdit;
    QLineEdit *password_LineEdit;
    QPushButton *login_PushButton;
    QVBoxLayout *mainLayout;



    QString serverAddr;
    QString port;
    QString username;
    QString  password;
    explicit sign_in(QWidget *parent = 0);
signals:
    void signIn(QString username, QString password, QString serverAddr, QString port);
public slots:
    void LoginClicked();
};
#endif
