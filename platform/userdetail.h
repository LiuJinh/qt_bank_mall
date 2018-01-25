#ifndef USERDETAIL_H
#define USERDETAIL_H

#include <QString>
#include <QVector>

class UserDetail
{
public:
    UserDetail();

    QString getUser();
    QString getPassword();
    QString getName();
    QString getId();
    QVector<QString> getCard();

    void setUser(QString user);
    void setPassword(QString password);
    void setName(QString name);
    void setId(QString id);
    void setCard(QVector<QString> card);


private:
    QString mUser;
    QString mPassword;
    QString mName;
    QString mId;
    QVector<QString> mCard;
};

#endif // USERDETAIL_H
