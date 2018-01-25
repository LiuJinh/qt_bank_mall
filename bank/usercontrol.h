#ifndef USERCONTROL_H
#define USERCONTROL_H

#include "userdetail.h"

#include <list>
#include <vector>
class UserControl
{
public:
    UserControl();
    vector<UserDetail>  getAllUser(int mbank);              //获得所需银行所有用户数据
    void setAllUsers(vector<UserDetail > allUsers,int mbank);//更新文件
    int findUser(string user,string password);//通过账号密码查询该账号的编号
    void changeMoney(int user,int newMoney,int mbank);//修改账号余额
    UserDetail   getUser(int i);//获取指定位置的用户
};

#endif // USERCONTROL_H
