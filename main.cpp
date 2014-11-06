#include "logindialog.h"
#include "listdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //LoginDialog w;
    ListDialog w;
    w.show();

    return a.exec();
}
