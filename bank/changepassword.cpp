#include "changepassword.h"
#include "commonfunc.h"
#include "usercontrol.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialog>
#include <QMessageBox>

extern int bank;
extern int userNumber;
ChangePassword::ChangePassword()
{

    currentPwd = new QLabel("原始密码");
    newPwd = new QLabel("更改密码");

    currentLine = new QLineEdit;
    newLine = new QLineEdit;
    currentLine->setEchoMode(QLineEdit::Password);
    newLine->setEchoMode(QLineEdit::Password);

    submitBtn = new QPushButton("ok");
    quitBtn = new QPushButton("exit");
    submitBtn->setEnabled(false);

    QHBoxLayout *currentLayout = new QHBoxLayout;
    QHBoxLayout *newLayout = new QHBoxLayout;
    QHBoxLayout *btnLayout = new QHBoxLayout;

    QVBoxLayout *total = new QVBoxLayout;

    currentLayout->addWidget(currentPwd);
    currentLayout->addWidget(currentLine);

    newLayout->addWidget(newPwd);
    newLayout->addWidget(newLine);

    btnLayout->addWidget(submitBtn);
    btnLayout->addWidget(quitBtn);

    total->addLayout(currentLayout);
    total->addLayout(newLayout);
    total->addLayout(btnLayout);

    connect(submitBtn,SIGNAL(clicked(bool)),this,SLOT(onChangePwd()));
    connect(currentLine,SIGNAL(textChanged(QString)),this,SLOT(onSubmitBtnEnable()));
    connect(newLine,SIGNAL(textChanged(QString)),this,SLOT(onSubmitBtnEnable()));
    connect(quitBtn,SIGNAL(clicked(bool)),this,SLOT(close()));

    setLayout(total);
}

void ChangePassword::onChangePwd()
{
    UserControl controller;

    vector<UserDetail> allUsers = controller.getAllUser(bank);
    if(allUsers.at(userNumber).getPassword() == currentLine->text().toStdString())
    {
        QMessageBox::information(this,tr(""),tr("修改成功"),tr("OK"));
        allUsers.at(userNumber).setPassword(newLine->text().toStdString());
        controller.setAllUsers(allUsers,bank);
        this->close();
    }
    else{
        QMessageBox::information(this,tr(""),tr("原始密码输入错误"),tr("OK"));
    }
}

void ChangePassword::onSubmitBtnEnable()
{
    CommonFunc func;

    if(currentLine->text().length()==6&&newLine->text().length()==6
            &&func.isAllNumber(currentLine->text())&&func.isAllNumber(newLine->text()))
        submitBtn->setEnabled(true);
}


