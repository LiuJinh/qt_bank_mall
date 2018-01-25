#include "login.h"
#include "mainprofile.h"
#include "applycardserver.h"
#include <cartdetail.h>
#include <allshow.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Login w;
    w.show();

    return a.exec();
}
