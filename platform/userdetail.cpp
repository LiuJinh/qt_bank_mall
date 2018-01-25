#include "userdetail.h"

UserDetail::UserDetail()
{

}

 QString UserDetail::getUser()
{
    return mUser;
}

 QString UserDetail::getPassword()
{
    return mPassword;
}

 QString UserDetail::getName()
{
    return mName;
}

 QString UserDetail::getId()
{
    return mId;
}

 QVector<QString> UserDetail::getCard()
{
    return mCard;
}

void UserDetail::setUser(QString user)
{
    mUser = user;
}

void UserDetail::setPassword(QString password)
{
    mPassword = password;
}

void UserDetail::setName(QString name)
{
    mName = name;
}

void UserDetail::setId(QString id)
{
    mId = id;
}

void UserDetail::setCard(QVector<QString> card)
{
    mCard.clear();
    for(int i = 0;i<card.size();i++)
    mCard.push_back(card.at(i));
}
