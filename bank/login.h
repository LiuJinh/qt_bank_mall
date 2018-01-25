#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>



namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    void initBank();        //初始化银行选项中的银行
    bool isFindUser();      //判断是否存在用户
signals:

private slots:
    void onSubmitClicked();//槽函数，用于登录事件响应
    void onSignUpClicked();//槽函数，用于注册事件响应
    void onEnableSubmitBtn(const QString &text);//槽函数，根据输入框来确定登录按钮是否可以按下

private:
    Ui::Login *ui;
    QLineEdit *mUserLine;
    QLineEdit *mPwdLine;
    QLabel *proLabel;
    QLabel *mUseLabel;
    QLabel *mPwdLabel;
    QLabel *mBankLabel;
    QPushButton *submit;
    QPushButton *signUp;
    QComboBox *bankChoose;


};

#endif // LOGIN_H
