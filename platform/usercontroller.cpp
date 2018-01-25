#include "usercontroller.h"

#include <QFile>
#include <QTextStream>
#include <sstream>
#include <QDebug>
#include <string>

extern QString path;

UserController::UserController()
{

}

QVector<UserDetail> UserController::getAllUser()
{
    QVector<UserDetail >  allUsers ;
    QString currentPath = path+"users.txt";

    QFile file(currentPath);
    if(!file.open(QFile::ReadOnly|QIODevice::Text)){
        qDebug()<<"something wrong";
    }

    QTextStream rd(&file);
    QString line = rd.readLine();
    QString temp;
    line = rd.readLine();

    while(!line.isNull()){
        temp = line;

        UserDetail user;

        int k=0;
        QString sub="";

        QVector<QString> allCards;

        for(int i=0;i<temp.size();i++){


            if( temp[i]!='\\'  ){
                sub += temp[i];
             }
            else {
                switch (k){
                case 0:user.setUser(sub);break;
                case 1:user.setPassword(sub);break;
                case 2:user.setName(sub);break;
                case 3:user.setId(sub);break;
                default:
                        allCards.push_back(sub);
                }
                k++;
                sub = "";
            }

        }
        user.setCard(allCards);
        allUsers.push_back(user);
        line = rd.readLine();
    }

    file.close();
    return allUsers;
}

void UserController::setAllUsers(QVector<UserDetail> allUsers)
{
    QString currentPath = path +"users.txt";

    QFile file(currentPath);
    if(!file.open(QFile::WriteOnly|QIODevice::Text)){
        qDebug()<<"something wrong";
    }

    QTextStream wt(&file);
    wt<<"USER\\PWD\\NAME\\ID\\CARDS"<<endl;

    for(int i=0;i<allUsers.size();i++){

        QVector<QString> allCards;
        allCards=((UserDetail &)allUsers.at(i)).getCard();
        wt<<((UserDetail &)allUsers.at(i)).getUser()+'\\';
        wt<<((UserDetail &)allUsers.at(i)).getPassword()+'\\';
        wt<<((UserDetail &)allUsers.at(i)).getName()+'\\'+((UserDetail &)allUsers.at(i)).getId()+"\\";

        for(int j = 0;j<allCards.size();j++)
            wt<<allCards.at(j)+"\\";
        wt<<"\n";
    }

    file.close();
}

int UserController::findUser(QString user, QString password)
{
    QVector<UserDetail> allUsers = getAllUser();

    int size=allUsers.size();


    for(int i=0;i<size;i++){
        if(user==((UserDetail &)allUsers.at(i)).getUser()&&
                password ==((UserDetail &)allUsers.at(i)).getPassword()){
            return i;
        }
        else if(user == ((UserDetail &)allUsers.at(i)).getUser()&&
                password !=((UserDetail &)allUsers.at(i)).getPassword())
            return -1;
    }

    return -1;
}

void UserController::changePwd(int user, int newPwd)
{
    UserController controller;
    QVector<UserDetail >  allUsers = controller.getAllUser();

    ((UserDetail &)allUsers.at(user)).setPassword(QString::number(newPwd));
    controller.setAllUsers(allUsers);
}

UserDetail UserController::getUser(int i)
{
    QVector<UserDetail>  allUsers =  getAllUser();

    UserDetail  newUser = allUsers.at(i);

    return newUser;
}
