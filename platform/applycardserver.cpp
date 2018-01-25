#include "applycardserver.h"
#include "usercontroller.h"
#include<QMessageBox>

extern int userNumber;
ApplyCardServer::ApplyCardServer()
{
    tcpClient = new QTcpSocket(this);

    tcpClient->connectToHost(QHostAddress::LocalHost,2200);

    if(tcpClient->waitForConnected()==false)
        QMessageBox::information(this,tr("remind"),tr("connect fail"),tr("OK"));
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(readMessageFromTcpServer()));
}

void ApplyCardServer::setMessage(QString message)
{
    sendStr = message;
    QByteArray temp = message.toLatin1();
    tcpClient->write(temp);
}

QString ApplyCardServer::getMessage()
{
    return getStr;
}

void ApplyCardServer::onDealAddCard()
{
    UserController controller;

    QVector<UserDetail> allUsers = controller.getAllUser();
    bool isFind = false;
    int k =0;
    QString ID;
    int bank;
    QString user;
    QString password;
    QString temp="";
    if(getStr=="OK"){
        for(int i = 0;i<sendStr.length();i++){
            if(sendStr[i]!='\\')
                temp+=sendStr[i];
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

        QVector<QString> allCards = ((UserDetail&)allUsers.at(userNumber)).getCard();
        for(int i = 0;i<allCards.size();i++){
            if(allCards.at(i)==user){
                isFind = true;
            }
        }
        if(!isFind){
            allCards.push_back(user);
            ((UserDetail&)allUsers.at(userNumber)).setCard(allCards);
            controller.setAllUsers(allUsers);
            QMessageBox::information(this,tr("reminder"),tr("success"),tr("OK"),tr("EXIT"));
            this->close();
            emit successAdd();
        }

    }

    else{
        QMessageBox::information(this,tr("reminder"),tr("ID or password is wrong!"),tr("OK"),tr("EXIT"));
    }
}

void ApplyCardServer::onDealBuy()
{
    if(getStr=="OK"){
        QMessageBox::information(this,tr("reminder"),tr("Buy success!"),tr("OK"),tr("EXIT"));
        emit successBuy();
    }
    else if(getStr=="NOMONEY")
        QMessageBox::information(this,tr("reminder"),tr("No much money!"),tr("OK"),tr("EXIT"));
    else if(getStr=="WRONGPWD")
        QMessageBox::information(this,tr("reminder"),tr("Password wrong!"),tr("OK"),tr("EXIT"));

    else
        QMessageBox::information(this,tr("reminder"),tr("No such a card!"),tr("OK"),tr("EXIT"));


}


void ApplyCardServer::readMessageFromTcpServer()
{
    getStr = QVariant(tcpClient->readAll()).toString();

    qDebug()<<getStr;
    QString temp = 0;
    if(sendStr!=""){

        for(int i = 0;i<sendStr.length();i++){
            if(sendStr[i]!='\\')
                temp+=sendStr[i];
            else
                break;
        }
    }
    if(temp=="addcard"){
        onDealAddCard();
    }
    else if(temp=="buy"){
        onDealBuy();
    }

}


