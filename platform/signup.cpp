#include "signup.h"
#include "ui_signup.h"
#include "commonfunc.h"
#include "usercontroller.h"

#include <QMessageBox>
#include <QDateTime>

SignUp::SignUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);

    ui->pwdLine->setEchoMode(QLineEdit::Password);
    ui->submitBtn->setEnabled(false);

    ui->label->setStyleSheet("QLabel {color : #8F8AA1; }");
    ui->label_2->setStyleSheet("QLabel {color : #8F8AA1; }");
    ui->label_3->setStyleSheet("QLabel {color : #8F8AA1; }");

    connect(ui->pwdLine,SIGNAL(textChanged(QString)),this,SLOT(onEnableSubmitBtn()));
    connect(ui->idLine,SIGNAL(textChanged(QString)),this,SLOT(onEnableSubmitBtn()));
    connect(ui->nameLine,SIGNAL(textChanged(QString)),this,SLOT(onEnableSubmitBtn()));

    connect(ui->submitBtn,SIGNAL(clicked(bool)),this,SLOT(onSubmitRequest()));
}
SignUp::~SignUp()
{
    delete ui;
}

void SignUp::onSubmitRequest(){
    bool isOk = true;
    bool isEver = false;
    UserController controller;


    UserDetail newUser;

    QVector<UserDetail> allUsers;
    allUsers = controller.getAllUser();


    for(int i=0;i<allUsers.size();i++){
        if(((UserDetail&)allUsers.at(i)).getId() == ui->idLine->text())
        {
            isEver = true;
            break;
        }
    }

    if(isEver)
        isOk = false;

    if(isOk == true){
        newUser.setId(ui->idLine->text());
        newUser.setName(ui->nameLine->text());
        newUser.setPassword(ui->pwdLine->text());


        QDateTime currenTime = QDateTime::currentDateTime();
        QString time = currenTime.toString("yyyymmss");
        QString back;
        QString forth;

        forth = QString::fromStdString(std::to_string(rand()%100));
        back = QString::fromStdString(std::to_string(rand()%10));
        newUser.setUser(forth+time+back);

        allUsers.push_back(newUser);

        controller.setAllUsers(allUsers);

        QMessageBox msgBox;
        msgBox.setText("User:"+newUser.getUser()+"\tPlease remember");
        msgBox.exec();

        this->close();

    }

    else{
        QMessageBox msgBox;
        msgBox.setText("您已注册过，申请失败");
        msgBox.exec();
    }


}

void SignUp::onEnableSubmitBtn()
{
    CommonFunc func;

    if(func.isAllNumber(ui->idLine->text())&&ui->idLine->text().length()==18
            &&ui->pwdLine->text().length()<=16&&ui->pwdLine->text().length()>=10
            &&!ui->nameLine->text().isEmpty())
        ui->submitBtn->setEnabled(true);
    else
        ui->submitBtn->setEnabled(false);
}
