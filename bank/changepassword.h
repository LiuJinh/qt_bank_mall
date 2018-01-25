#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
class ChangePassword:public QDialog
{
    Q_OBJECT
public:
    ChangePassword();

private slots:
    void onChangePwd();     //确认按钮按下时修改密码并进行比对
    void onSubmitBtnEnable();//根据输入框来判断修改密码按钮是否可以按下

private:
    QLabel *currentPwd;
    QLabel *newPwd;

    QLineEdit *currentLine;
    QLineEdit *newLine;

    QPushButton *submitBtn;
    QPushButton *quitBtn;
};

#endif // CHANGEPASSWORD_H
