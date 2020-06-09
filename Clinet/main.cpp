#include "clientschat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientsChat Client;
    return a.exec();
}
