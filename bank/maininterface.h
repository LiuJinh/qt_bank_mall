#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <string>

using namespace std;

class MainInterface:public QWidget
{
    Q_OBJECT
public:
    MainInterface();
    void initPerson();//初始化个人信息，构造函数内调用

private slots:
    void onChangePassword();//响应修改密码按钮点击事件，调出修改密码对话框，进行修改密码的一串操作
    void onRemove();//响应注销账户按钮点击事件，删除登录的此用户
    void onSavingBtn();//响应存钱按钮点击事件，调出存钱对话框，进行存钱的一串操作
    void onDrawback();//响应取钱按钮点击事件，调出取钱对话框，进行取钱的一串操作
    void onTransfer();//响应转账按钮点击事件，调出转账对话框，进行转账的一串操作
    void onExitBtn();//响应退出按钮点击事件，关闭此界面并打开登录界面
    void onRenewMoney();//响应存钱，取钱，转账事件，更新个人信息中余额
private:
    QLabel *mNameLabel;
    QLabel *mMoney;

    QLineEdit *nameLine;
    QLineEdit *moneyLine;
    QLineEdit * idLine ;

    QPushButton *changePwdBtn;
    QPushButton *savingBtn;
    QPushButton *drawbackBtn;
    QPushButton *transferBtn;
    QPushButton *removeBtn;
    QPushButton *exitBtn;
};

#endif // MAININTERFACE_H
