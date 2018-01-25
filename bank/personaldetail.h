#ifndef PERSONALDETAIL_H
#define PERSONALDETAIL_H

#include "userdetail.h"
#include <string>

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

using namespace std;

class PersonalDetail
{
public:
    PersonalDetail();


private slots:
    void drawback(int money);
    void save(int money);
    bool transfer(int bank,string user,int money);



private:
    UserDetail mUser;


};

#endif // PERSONALDETAIL_H
