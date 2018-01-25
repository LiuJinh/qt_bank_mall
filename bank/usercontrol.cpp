#include "usercontrol.h"
#include "global.h"

#include <QDebug>
#include <vector>
#include <string>
#include <QFile>
#include <QTextStream>
#include <sstream>
#include <QString>

using namespace std;

extern QString path;
extern int bank;

UserControl::UserControl()
{

}

vector<UserDetail >UserControl::getAllUser(int mbank)
{
    vector<UserDetail >  allUsers ;
    QString currentPath = "";



//    if(bank==0)
//        currentPath = path+"document\\中国工商银行\\details.txt";
//    else if(bank==1)
//        currentPath = path+"document\\中国建设银行\\details.txt";
//    else if(bank==2)
//        currentPath = path+"document\\中国工商银行\\details.txt";
//    else if(bank==3)
//        currentPath = "c:\\Users\\liujing\\Desktop\\银行\\document\\中国邮政储蓄\\details.txt";


    switch(mbank){
    case 0:currentPath = path+"document\\中国工商银行\\details.txt";break;
    case 1:currentPath = path+"document\\中国建设银行\\details.txt";break;
    case 2:currentPath = path+"document\\中国农业银行\\details.txt";break;
    case 3:currentPath = path+"document\\中国邮政储蓄\\details.txt";break;
    }





    QFile file(currentPath);
    if(!file.open(QFile::ReadOnly|QIODevice::Text)){
        qDebug()<<"something wrong";
    }

    QTextStream rd(&file);
    QString line = rd.readLine();
    string temp;
    line = rd.readLine();

    while(!line.isNull()){
        temp = line.toStdString();

        UserDetail user  ;

        int k=0;
        string sub="";

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
                case 4:user.setMoney((QString::fromStdString(sub)).toFloat());
                }               
                k++;
                sub = "";
            }

        }

        allUsers.push_back(user);
        line = rd.readLine();
    }

    file.close();
    return allUsers;
}

void UserControl::setAllUsers(vector<UserDetail> allUsers,int mbank)
{
    QString currentPath;

    switch(mbank){
    case 0:currentPath = path+"document\\中国工商银行\\details.txt";break;
    case 1:currentPath = path+"document\\中国建设银行\\details.txt";break;
    case 2:currentPath = path+"document\\中国农业银行\\details.txt";break;
    case 3:currentPath = path+"document\\中国邮政储蓄\\details.txt";break;
    }

    QFile file(currentPath);
    if(!file.open(QFile::WriteOnly|QIODevice::Text)){
        qDebug()<<"something wrong";
    }

    QTextStream wt(&file);
    wt<<"账号\密码\姓名\身份证\余额"<<endl;

    for(int i=0;i<allUsers.size();i++){
        wt<< QString::fromStdString(allUsers.at(i).getUser())+'\\';
        wt<<QString::fromStdString(allUsers.at(i).getPassword())+'\\';
        wt<<QString::fromStdString(allUsers.at(i).getName())+'\\'+QString::fromStdString(allUsers.at(i).getId())+'\\';


        wt<<allUsers.at(i).getMoney()<<"\\";
        wt<<"\n";
    }

    file.close();

}

int UserControl::findUser(string user, string password) //若用户存在，则返回当前用户所在行数，不存在则返回-1
{
    vector<UserDetail  > allUsers = getAllUser(bank);

    int size=allUsers.size();

    for(int i=0;i<size;i++){
        if(user.compare(allUsers.at(i).getUser())==0&&
                password.compare(allUsers.at(i).getPassword())==0){
            return i;
        }
        else if(user.compare(allUsers.at(i).getUser())==0&&
                password.compare(allUsers.at(i).getPassword())!=0)
            return -1;
    }

    return -1;
}

void UserControl::changeMoney(int user,int newMoney,int mbank)
{
    UserControl  controller;
    vector<UserDetail >  allUsers = controller.getAllUser(mbank);

    allUsers.at(user).setMoney(newMoney);
    controller.setAllUsers(allUsers,bank);

}


UserDetail UserControl::getUser(int i)
{
    vector<UserDetail>  allUsers =  getAllUser(3);

    UserDetail  newUser = allUsers.at(i);

    return newUser;
}





