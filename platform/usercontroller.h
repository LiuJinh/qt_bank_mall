#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "userdetail.h"

#include <QVector>


class UserController
{
public:
    UserController();

    QVector<UserDetail>  getAllUser();    //获得所需银行所有用户数据
    void setAllUsers(QVector<UserDetail > allUsers);//更改文件中所有用户信息
    int findUser(QString user,QString password);//根据用户账号密码返回用户编号
    void changePwd(int user,int newPwd);//根据账号编号和新密码修改信息
    UserDetail   getUser(int i);//返回编号为i的用户
};

#endif // USERCONTROLLER_H
