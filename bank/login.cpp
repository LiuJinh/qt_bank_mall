#include "login.h"
#include "ui_login.h"
#include "global.h"
#include "usercontrol.h"
#include "signup.h"
#include "commonfunc.h"
#include "maininterface.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <string>
#include <string.h>
#include <QMessageBox>
#include <QDir>

using namespace std;

int bank = -1;
int userNumber = -1;
QString path =  QDir::currentPath()+"\\..\\bank\\";

Login::Login(QWidget *parent) :
   QWidget(parent),
    ui(new Ui::Login)
{
    QFont ft1;
    ft1.setPointSize(16);
    proLabel = new QLabel("银行登录系统");
    proLabel->setFont(ft1);

    mUserLine = new QLineEdit;
    mUseLabel = new QLabel("用户");
    mUseLabel->setBuddy(mUserLine);

    mPwdLine = new QLineEdit;
    mPwdLabel = new QLabel("密码");
    mPwdLabel->setBuddy(mPwdLine);
    mPwdLine->setEchoMode(QLineEdit::Password);

    mBankLabel = new QLabel("银行");
    bankChoose = new QComboBox;
    mBankLabel->setBuddy(bankChoose);

    submit = new QPushButton("登录");
    signUp = new QPushButton("注册");
    submit->setEnabled(false);

    QHBoxLayout *userLayout = new QHBoxLayout;
    userLayout->addWidget(mUseLabel);
    userLayout->addWidget(mUserLine);

    QHBoxLayout *pwdLayout = new QHBoxLayout;
    pwdLayout->addWidget(mPwdLabel);
    pwdLayout->addWidget(mPwdLine);

    QHBoxLayout *bankLayout = new QHBoxLayout;
    bankLayout->addWidget(mBankLabel);
    bankLayout->addWidget(bankChoose);


    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(submit);
    buttonLayout->addWidget(signUp);

    QVBoxLayout *total = new QVBoxLayout;
    total->addWidget(proLabel);
    total->addLayout(bankLayout);
    total->addLayout(userLayout);
    total->addLayout(pwdLayout);
    total->addLayout(buttonLayout);


    setWindowTitle("login");
    setLayout(total);
    //ui->setupUi(this);

    initBank();

    connect(mUserLine,SIGNAL(textChanged(QString)),this,SLOT(onEnableSubmitBtn(QString)));
    connect(mPwdLine,SIGNAL(textChanged(QString)),this,SLOT(onEnableSubmitBtn(QString)));

    connect(submit,SIGNAL(clicked(bool)),this,SLOT(onSubmitClicked()));
    connect(signUp,SIGNAL(clicked(bool)),this,SLOT(onSignUpClicked()));

    this->setFixedSize(365,240);

}

Login::~Login()
{
    // delete ui;
}

void Login::initBank()
{
    int i=0;

    QFile file(path+"document\\bank.txt");
    if(!file.open(QFile::ReadOnly | QIODevice::Text)){

    }

    QTextStream readFile(&file);
    QString line = readFile.readLine();

    while(!line.isNull()){
        bankChoose->addItem(line,i);
        line = readFile.readLine();
    }

    file.close();
}

bool Login::isFindUser()
{
    string useName;
    string password;
    QString currentPath;

    useName = mUserLine->text().toStdString();
    password = mPwdLine->text().toStdString();

    switch(bankChoose->currentIndex()+1){
    case 0:currentPath = path+"document\\中国工商银行";break;
    case 1:currentPath = path+"document\\中国建设银行";break;
    case 2:currentPath = path+"document\\中国农业银行";break;
    case 3:currentPath = path+"document\\中国邮政储蓄";break;
    }

    QFile file(currentPath+"\\details.txt");
    file.close();
    return true;
}

void Login::onSignUpClicked()
{
    SignUp * sign = new SignUp;

    sign->setWindowModality(Qt::ApplicationModal);
    sign->show();

}

void Login::onSubmitClicked()
{
    UserControl * controller = new UserControl;
    QString user = mUserLine->text();
    QString password = mPwdLine->text();


    vector<UserDetail > allUsers;
    allUsers=controller->getAllUser(3);

//     mUserLine->setText(bankChoose->currentText());
//    UserDetail  newUser = controller->getUser(0);

//     mUserLine->setText(QString::fromStdString(allUsers->at(0)->getUser()));

    bank = bankChoose->currentIndex();
    userNumber = controller->findUser(user.toStdString(),password.toStdString());

    if(userNumber!=-1){
        //进入主界面
        MainInterface * itf =  new MainInterface;
        itf->show();
        this->close();
    }

    else{
        //输出错误
        if (!(QMessageBox::information(this,tr("login fail"),tr("login fail"),tr("OK"),tr("EXIT"))))
        {

        }
    }



    delete(controller);
}

void Login::onEnableSubmitBtn(const QString &text)
{
    CommonFunc * func = new CommonFunc;

    submit->setEnabled ((!mUserLine->text().isEmpty())&&(!mPwdLine->text().isEmpty())
                        &&func->isAllNumber(mUserLine->text())&&func->isAllNumber(mPwdLine->text())
                        &&mUserLine->text().length()==19&&mPwdLine->text().length()==6);
}


