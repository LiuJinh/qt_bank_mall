#ifndef USERDETAIL_H
#define USERDETAIL_H

#include <string>

using namespace std;
class UserDetail
{
public:
    UserDetail();
    string getUser();
    string getPassword();
    string getName();
    string getId();
    float getMoney();

    void setUser(string user);
    void setPassword(string password);
    void setName(string name);
    void setId(string id);
    void setMoney(float money);


private:
    string mUser;
    string mPassword;
    string mName;
    string mId;
    float mMoney;

};

#endif // USERDETAIL_H
