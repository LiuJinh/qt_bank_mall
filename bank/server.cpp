#include "server.h"
#include "usercontrol.h"

#include <QMessageBox>
#include <QDebug>

Server::Server()
{
    tcpServer = new QTcpServer(this);
    tcpClient = new QTcpSocket(this);
    tcpServer->listen(QHostAddress::Any, 2200);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newConnect()));
}

void Server::sendMessage(QString str)
{
    tcpClient->write(str.toLatin1());
}

void Server::newConnect()
{
    tcpClient = tcpServer->nextPendingConnection();
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(readClient()));
}

void Server::readClient()
{
    recStr = tcpClient->readAll();

    qDebug()<<recStr;
    QString temp = 0;
    if(recStr!=""){

        for(int i = 0;i<recStr.length();i++){
            if(recStr[i]!='\\')
                temp+=recStr[i];
            else
                break;
        }
    }

    if(temp=="addcard"){
        onAddCardRequest();
    }
    else if(temp=="buy"){
        onBuyRequest();
    }

}

void Server::onAddCardRequest()
{
    if(recStr!=""){
        bool isFind = false;
        UserControl controller;

        vector<UserDetail> allUsers ;
        int k =0;
        QString ID;
        int bank;
        QString user;
        QString password;
        QString temp="";
        for(int i = 0;i<recStr.length();i++){
            if(recStr[i]!='\\')
                temp+=recStr[i];
            else
            {
                switch (k){
                case 1:ID=temp;break;
                case 2:bank=temp.toInt();break;
                case 3:user=temp;break;
                case 4:password=temp;break;

                }

                 k++;
                 temp="";
            }
        }

        allUsers = controller.getAllUser(temp.toInt());


        for(int i = 0;i<allUsers.size();i++){
            if(ID.toStdString()==((UserDetail&)allUsers.at(i)).getId()&&user.toStdString()==((UserDetail&)allUsers.at(i)).getUser()
                    &&password.toStdString()==((UserDetail&)allUsers.at(i)).getPassword())
            {
                sendMessage("OK");
                isFind = true;
                break;
            }
        }

        if(!isFind)
            sendMessage("wrong");

    }
}

void Server::onBuyRequest()
{


    bool isFind = false;
    UserControl controller;

    vector<UserDetail> allUsers ;
    int k =0;
    int bank = 0;
    QString user;
    QString password;
    QString temp="";
    float money=0;

    for(int i = 0;i<recStr.length();i++){
        if(recStr[i]!='\\')
            temp+=recStr[i];
        else
        {
            switch (k){
            case 1:user=temp;break;
            case 2:password=temp;break;
            case 3:money=temp.toFloat();break;
            }

             k++;
             temp="";
        }
    }

    temp = user.mid(0,4);

    if(temp == "6217")
        bank = 0;
    else if(temp == "6218")
        bank = 1;
    else if(temp == "6219")
        bank = 2;
    else if(temp == "6210")
        bank = 3;

    allUsers = controller.getAllUser(bank);


    for(int i = 0;i<allUsers.size();i++){
        if(user.toStdString()==((UserDetail&)allUsers.at(i)).getUser()
                &&password.toStdString()==((UserDetail&)allUsers.at(i)).getPassword()
                &&money<=((UserDetail&)allUsers.at(i)).getMoney())
        {
            isFind = true;
            sendMessage("OK");
            ((UserDetail&)allUsers.at(i)).setMoney(((UserDetail&)allUsers.at(i)).getMoney()-money);
            controller.setAllUsers(allUsers,bank);
            break;
        }
        else if(user.toStdString()==((UserDetail&)allUsers.at(i)).getUser()
                &&password.toStdString()==((UserDetail&)allUsers.at(i)).getPassword()
                &&money>((UserDetail&)allUsers.at(i)).getMoney()){
            isFind = true;
            sendMessage("NOMONEY");
            break;
        }
        else if(user.toStdString()==((UserDetail&)allUsers.at(i)).getUser()
                &&password.toStdString()!=((UserDetail&)allUsers.at(i)).getPassword()){
            isFind = true;
            sendMessage("WRONGPWD");
            break;
        }
    }

    if(!isFind)
        sendMessage("wrong");


}
