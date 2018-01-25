#include "userdetail.h"

UserDetail::UserDetail()
{

}

string UserDetail::getUser()
{
    return mUser;
}

string UserDetail::getPassword()
{
    return mPassword;
}

string UserDetail::getName()
{
    return mName;
}

string UserDetail::getId()
{
    return mId;
}

float UserDetail::getMoney()
{
    return mMoney;
}

void UserDetail::setUser(string user)
{
    mUser=user;
}

void UserDetail::setPassword(string password)
{
    mPassword=password;
}

void UserDetail::setName(string name)
{
    mName=name;
}

void UserDetail::setId(string id)
{
    mId=id;
}

void UserDetail::setMoney(float money)
{
    mMoney = money;
}
