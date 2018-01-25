#include "login.h"
#include "ui_login.h"
#include "commonfunc.h"
#include "signup.h"
#include "usercontroller.h"
#include "mainprofile.h"
#include <QMessageBox>
#include <QPixmap>

int userNumber = 0;
QString path = QDir::currentPath()+"\\..\\platForm\\EcommercePlatform\\";


Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    ui->pwdLine->setEchoMode(QLineEdit::Password);
    ui->loginBtn->setEnabled(false);

    ui->userLine->setStyleSheet("border-radius:10px;");
    ui->pwdLine->setStyleSheet("border-radius:10px;");

    QPixmap mPicture;
    mPicture.load(path+"icon\\password.png");
    ui->pwdLabel->setPixmap(mPicture);
    mPicture.load(path+"icon\\profile.png");
    ui->userLabel->setPixmap(mPicture);

    connect(ui->pwdLine,SIGNAL(textChanged(QString)),this,SLOT(onEnableSubmitBtn()));
    connect(ui->userLine,SIGNAL(textChanged(QString)),this,SLOT(onEnableSubmitBtn()));

    connect(ui->loginBtn,SIGNAL(clicked(bool)),this,SLOT(onSubmitClicked()));
    connect(ui->signUpBtn,SIGNAL(clicked(bool)),this,SLOT(onSignUpClicked()));
}

Login::~Login()
{
    delete ui;
}

void Login::onEnableSubmitBtn()
{
    CommonFunc func;

    if(func.isAllNumber(ui->userLine->text())&&ui->userLine->text().length()==11
            &&ui->pwdLine->text().length()<=16&&ui->pwdLine->text().length()>=10)
        ui->loginBtn->setEnabled(true);
    else
        ui->loginBtn->setEnabled(false);
}

void Login::onSignUpClicked(){
    SignUp * sign = new SignUp;

    sign->setWindowModality(Qt::ApplicationModal);
    sign->show();
}

void Login::onSubmitClicked(){
    UserController controller;
    QString user = ui->userLine->text();
    QString password = ui->pwdLine->text();


    QVector<UserDetail > allUsers;
    allUsers=controller.getAllUser();

    userNumber = controller.findUser(user,password);

    if(userNumber!=-1){
        //进入主界面
        MainProfile * mp =  new MainProfile;
        mp->show();
        this->close();
    }

    else{
        //输出错误
        if (!(QMessageBox::information(this,tr("login fail"),tr("login fail"),tr("OK"),tr("EXIT"))))
        {

        }
        else
            this->close();
    }

}
