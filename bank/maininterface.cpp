#include "maininterface.h"
#include "login.h"
#include "usercontrol.h"
#include "changepassword.h"
#include "commonfunc.h"
#include "transfer.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <iostream>
#include <string>
#include <QApplication>
extern int bank;
extern int userNumber;
extern int changeMoney;
UserDetail me;

MainInterface::MainInterface()
{

    resize(500,300);

    mNameLabel = new QLabel("姓名");
    mMoney = new QLabel("余额");

    QLabel * idLabel = new QLabel("证件");
    idLine =  new QLineEdit;

    nameLine = new QLineEdit;
    moneyLine = new QLineEdit;

    changePwdBtn = new QPushButton("修改密码");
    savingBtn = new QPushButton("存款");
    drawbackBtn = new QPushButton("取款");
    transferBtn = new QPushButton("转账");
    removeBtn = new QPushButton("注销账户");
    exitBtn = new QPushButton("logout");

    nameLine->setFocusPolicy(Qt::NoFocus);
    moneyLine->setFocusPolicy(Qt::NoFocus);
    idLine->setFocusPolicy(Qt::NoFocus);

    QHBoxLayout *nameLayout = new QHBoxLayout;
    QHBoxLayout *idLayout = new QHBoxLayout;
    QHBoxLayout *moneyLayout = new QHBoxLayout;
    QVBoxLayout *logOutLayout = new QVBoxLayout;
    QVBoxLayout *detail = new QVBoxLayout;
    QVBoxLayout *changeMoneyLayout = new QVBoxLayout;

    nameLayout->addWidget(mNameLabel);
    nameLayout->addWidget(nameLine);

    moneyLayout->addWidget(mMoney);
    moneyLayout->addWidget(moneyLine);

    idLayout->addWidget(idLabel);
    idLayout->addWidget(idLine);

    logOutLayout->addWidget(removeBtn);
    logOutLayout->addWidget(changePwdBtn);
    logOutLayout->addWidget(exitBtn);
    changeMoneyLayout->addWidget(savingBtn);
    changeMoneyLayout->addWidget(drawbackBtn);
    changeMoneyLayout->addWidget(transferBtn);

    detail->addLayout(nameLayout);
    detail->addLayout(idLayout);
    detail->addLayout(moneyLayout);
    QHBoxLayout *total = new QHBoxLayout;
    total->addLayout(logOutLayout);
    total->addLayout(detail);
    total->addLayout(changeMoneyLayout);

    setLayout(total);

    initPerson();

    connect(changePwdBtn,SIGNAL(clicked(bool)),this,SLOT(onChangePassword()));
    connect(removeBtn,SIGNAL(clicked(bool)),this,SLOT(onRemove()));
    connect(savingBtn,SIGNAL(clicked(bool)),this,SLOT(onSavingBtn()));
    connect(drawbackBtn,SIGNAL(clicked(bool)),this,SLOT(onDrawback()));
    connect(transferBtn,SIGNAL(clicked(bool)),this,SLOT(onTransfer()));
    connect(exitBtn,SIGNAL(clicked(bool)),this,SLOT(onExitBtn()));


}

void MainInterface::initPerson()
{

    UserControl controller;

    vector<UserDetail> allUsers = controller.getAllUser(bank);

    me = allUsers.at(userNumber);

    nameLine->setText(QString::fromStdString(me.getName()));
    moneyLine->setText(QString::number(me.getMoney()));
    idLine->setText(QString::fromStdString(me.getId()));

}

void MainInterface::onChangePassword()
{
    ChangePassword *change = new ChangePassword;
    change->show();
}

void MainInterface::onRemove()
{
    UserControl controller;
    vector<UserDetail> allUsers = controller.getAllUser(bank);
    bool ok;
    QString answer = QInputDialog::getText(this,"","Password", QLineEdit::Normal,"",&ok);
    if(ok){
        if(answer.toStdString() == allUsers.at(userNumber).getPassword())
        {
            vector<UserDetail>::iterator it = allUsers.begin()+userNumber;
            allUsers.erase(it);
            controller.setAllUsers(allUsers,bank);
            QMessageBox::information(this,tr(""),tr("注销成功"),tr("OK"));
            Login *newLogin = new Login;
            newLogin->show();
            this->close();
        }
        else{
            QMessageBox::information(this,tr(""),tr("密码错误"),tr("OK"));
        }
    }
}

void MainInterface::onSavingBtn()
{
    UserControl controller;

    CommonFunc func;

    while(true){
        bool ok;
        QString answer = QInputDialog::getText(this,"","输入存款", QLineEdit::Normal,"",&ok);
        if(ok){
            if(func.isAllNumber(answer)&&answer.length()<5&&answer.toInt()>0&&answer.toInt()<10000)
            {
                me.setMoney(me.getMoney()+atoi(answer.toStdString().c_str()));
                controller.changeMoney(userNumber,me.getMoney(),bank);
                QMessageBox::information(this,tr(""),tr("存款成功"),tr("OK"));
                break;
            }
            else{
                QMessageBox::information(this,tr(""),tr("fail,please input 0~9999"),tr("OK"));
            }
        }
        else
            break;
    }

    moneyLine->setText(QString::number(me.getMoney()));
}

void MainInterface::onDrawback()
{
    UserControl controller;

    CommonFunc func;

    while(true){
        bool ok;
        QString answer = QInputDialog::getText(this,"","输入取款", QLineEdit::Normal,"",&ok);
        if(ok){
            if(func.isAllNumber(answer)&&atoi(answer.toStdString().c_str())<=me.getMoney()&&answer.toInt()>0&&answer.toInt()<10000)
            {
                me.setMoney(me.getMoney()-atoi(answer.toStdString().c_str()));
                controller.changeMoney(userNumber,me.getMoney(),bank);
                QMessageBox::information(this,tr(""),tr("取款成功"),tr("OK"));
                break;
            }
            else if(atoi(answer.toStdString().c_str())>me.getMoney()){
                QMessageBox::information(this,tr(""),tr("余额不足，请重新输入!"),tr("OK"));
            }
            else{
                QMessageBox::information(this,tr(""),tr("fail,please input 0~9999"),tr("OK"));
            }
        }
        else
            break;
    }

    moneyLine->setText(QString::number(me.getMoney()));
}

void MainInterface::onTransfer()
{

    Transfer * trans = new Transfer;
    trans->setWindowModality(Qt::ApplicationModal);
    trans->show();

    connect(trans,SIGNAL(changeValue(int)),this,SLOT(onRenewMoney()));
}

void MainInterface::onExitBtn()
{
    Login *newLogin = new Login;
    newLogin->show();
    this->close();
}

void MainInterface::onRenewMoney()
{
    UserControl controller;
    moneyLine->setText(QString::number(controller.getAllUser(bank).at(userNumber).getMoney()));
}


