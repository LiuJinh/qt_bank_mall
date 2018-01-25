#include "signup.h"
#include "commonfunc.h"
#include "usercontrol.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <string>
#include <QDateTime>
#include <stdlib.h>
#include <time.h>
#include <QMessageBox>

extern QString path;

int signBank;
SignUp::SignUp()
{
    mName = new QLabel("姓名");
    nameLine = new QLineEdit;
    mName->setBuddy(nameLine);


    mId = new QLabel("id");
    idLine = new QLineEdit;
    mId->setBuddy(mId);


    mPassword = new QLabel("密码");
    pwdLine = new QLineEdit;
    mPassword->setBuddy(pwdLine);
    pwdLine->setEchoMode(QLineEdit::Password);

    bankName = new QLabel("银行");
    bankBox = new QComboBox;

    sign = new QPushButton("注册");
    sign->setEnabled(false);


    QVBoxLayout * left = new QVBoxLayout;

    left->addWidget(mName);
    left->addWidget(mId);
    left->addWidget(mPassword);

    QVBoxLayout * right = new QVBoxLayout;

    right->addWidget(nameLine);
    right->addWidget(idLine);
    right->addWidget(pwdLine);

    QHBoxLayout * on = new QHBoxLayout;
    on->addLayout(left);
    on->addLayout(right);

    QHBoxLayout *bankLayout = new QHBoxLayout;
    bankLayout->addWidget(bankName);
    bankLayout->addWidget(bankBox);
    bankLayout->addWidget(sign);

    QVBoxLayout *total = new QVBoxLayout;
    total->addLayout(on);
    total->addLayout(bankLayout);

    setWindowTitle("sign");
    setLayout(total);

    connect(nameLine,SIGNAL(textChanged(QString)),this,SLOT(onEnableSignBtn()));
    connect(idLine,SIGNAL(textChanged(QString)),this,SLOT(onEnableSignBtn()));
    connect(pwdLine,SIGNAL(textChanged(QString)),this,SLOT(onEnableSignBtn()));

    connect(sign,SIGNAL(clicked(bool)),this,SLOT(onSubmitRequest()));

    initBank();
}

void SignUp::initBank()
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
}

void SignUp::onEnableSignBtn()
{
    CommonFunc func;
    if((func.isAllNumber(idLine->text()))&&idLine->text().length()==18
            &&!nameLine->text().isEmpty()
            &&func.isAllNumber(pwdLine->text())&&pwdLine->text().length()==6)
        sign->setEnabled(true);
    else
        sign->setEnabled(false);

}

void SignUp::onSubmitRequest()
{
    bool isOk = true;
    int quantity = 0;
    int banktemp=bankBox->currentIndex();
    UserControl * controller =  new UserControl;


    UserDetail newUser;

    vector<UserDetail> allUsers;
    allUsers = controller->getAllUser(banktemp);

    signBank = banktemp;

    for(int i=0;i<allUsers.size();i++){
        if(allUsers.at(i).getId() == idLine->text().toStdString())
            quantity++;
    }

    if(quantity>=5)
        isOk = false;

    if(isOk == true){
        newUser.setId(idLine->text().toStdString());
        newUser.setName(nameLine->text().toStdString());
        newUser.setPassword(pwdLine->text().toStdString());
        newUser.setMoney(0);

        QString bankPre;

        switch(banktemp){
        case 0:bankPre="6217";break;
        case 1:bankPre="6218";break;
        case 2:bankPre="6219";break;
        case 3:bankPre="6210";break;
        }

        QDateTime currenTime = QDateTime::currentDateTime();
        QString time = currenTime.toString("yyyymmddhhmmss");
        string back;

        back = std::to_string(rand()%10);
        newUser.setUser((bankPre+time).toStdString()+back);

        allUsers.push_back(newUser);

        controller->setAllUsers(allUsers,banktemp);

        QMessageBox msgBox;
        msgBox.setText("User:"+QString::fromStdString(newUser.getUser())+"\tPlease remember");
        msgBox.exec();

        this->close();

    }

    else{
        QMessageBox msgBox;
        msgBox.setText("你已申请超过5个账号，注册失败");
        msgBox.exec();
    }

    delete(controller);
}
