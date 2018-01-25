#include "transfer.h"
#include "commonfunc.h"
#include "usercontrol.h"
#include "maininterface.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

extern QString path;
extern int bank;
extern int userNumber;
int changeMoney;
Transfer::Transfer()
{
    bankLabel = new QLabel("选择银行");
    userLabel = new QLabel("输入账号");
    moneyLabel = new QLabel("输入金额");

    userLine = new QLineEdit;
    bankBox = new QComboBox;
    moneyLine = new QLineEdit;

    transBtn = new QPushButton("转账");
    quitBtn = new QPushButton("取消");
    transBtn->setEnabled(false);

    QHBoxLayout * bankLayout =  new QHBoxLayout;
    bankLayout->addWidget(bankLabel);
    bankLayout->addWidget(bankBox);

    QHBoxLayout * userLayout = new QHBoxLayout;
    userLayout->addWidget(userLabel);
    userLayout->addWidget(userLine);

    QHBoxLayout * moneyLayout = new QHBoxLayout;
    moneyLayout->addWidget(moneyLabel);
    moneyLayout->addWidget(moneyLine);

    QHBoxLayout * btnLayout = new QHBoxLayout;
    btnLayout->addWidget(transBtn);
    btnLayout->addWidget(quitBtn);

    QVBoxLayout * total = new QVBoxLayout;
    total->addLayout(bankLayout);
    total->addLayout(userLayout);
    total->addLayout(moneyLayout);
    total->addLayout(btnLayout);

    setLayout(total);

    initBank();

    connect(userLine,SIGNAL(textChanged(QString)),this,SLOT(onEnableTransBtn()));
    connect(moneyLine,SIGNAL(textChanged(QString)),this,SLOT(onEnableTransBtn()));

    connect(transBtn,SIGNAL(clicked(bool)),this,SLOT(onTransBtn()));
    connect(quitBtn,SIGNAL(clicked(bool)),this,SLOT(close()));

    changeMoney = 0;
}

void Transfer::initBank()
{
    int i=0;

    QFile file(path+"document\\bank.txt");
    if(!file.open(QFile::ReadOnly | QIODevice::Text)){

    }

    QTextStream readFile(&file);
    QString line = readFile.readLine();

    while(!line.isNull()){
        bankBox->addItem(line,i);
        line = readFile.readLine();
    }

    file.close();
}

void Transfer::onEnableTransBtn()
{
    CommonFunc func;
    if(func.isAllNumber(userLine->text())&&userLine->text().length()==19&&func.isAllNumber(moneyLine->text())&&moneyLine->text().length()<5){
        transBtn->setEnabled(true);
    }
    else
        transBtn->setEnabled(false);
}

void Transfer::onTransBtn()
{
    UserControl controller;
    CommonFunc func;
    bool isFind = false;
    QString answer = moneyLine->text();


    vector<UserDetail> allUsers1 = controller.getAllUser(bank);
    vector<UserDetail> allUsers2 = controller.getAllUser(bankBox->currentIndex());

    int i=0;
    for(;i<allUsers2.size();i++){
        if(allUsers2.at(i).getUser()==userLine->text().toStdString()){
            isFind = true;
            break;
        }
    }

    if(isFind){
        if(atoi(answer.toStdString().c_str())<=allUsers1.at(userNumber).getMoney()&&answer.toInt()>0&&answer.toInt()<10000){
            controller.changeMoney(userNumber,allUsers1.at(userNumber).getMoney()-atoi(answer.toStdString().c_str()),bank);
            controller.changeMoney(i,allUsers2.at(i).getMoney()+atoi(answer.toStdString().c_str()),bankBox->currentIndex());
            QMessageBox::information(this,tr(""),tr("success"),tr("OK"));
            changeMoney = atoi(answer.toStdString().c_str());
            emit changeValue(changeMoney);
            this->close();
        }
        else if(atoi(answer.toStdString().c_str())>allUsers1.at(userNumber).getMoney()){
            QMessageBox::information(this,tr(""),tr("fail,No much money"),tr("OK"));
        }
        else{
            QMessageBox::information(this,tr(""),tr("fail,please input 0~9999"),tr("OK"));
        }
    }
    else{
        QMessageBox::information(this,tr(""),tr("No such a person"),tr("OK"));
    }


}
