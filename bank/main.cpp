
#include "server.h"
#include <QApplication>
#include <login.h>
#include <usercontrol.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server * server = new Server;
    Login w;
    w.show();

    return a.exec();

//    UserControl * controller =  new UserControl;

//    vector<UserDetail*> * details = controller->getAllUser(3);


}
