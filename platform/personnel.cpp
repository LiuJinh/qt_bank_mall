#include "personnel.h"
#include "usercontroller.h"
#include "ui_personnel.h"
#include "clickablelabel.h"
#include "applycardserver.h"
#include <QMessageBox>
#include <QPixmap>
#include <QHBoxLayout>

extern int userNumber;
extern QString path;
Personnel::Personnel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Personnel)
{
    ui->setupUi(this);

    isOpen = false;
    isOk = false;
    UserController controller;
    UserDetail user = controller.getAllUser().at(userNumber);

   ui->lineEdit->setText(user.getUser());
   ui->lineEdit->setEnabled(false);
   ui->lineEdit_2->setText(user.getName());
   ui->lineEdit_3->setText(user.getId());
   ui->lineEdit_3->setEnabled(false);

   ui->lineEdit_4->setEchoMode(QLineEdit::Password);
   ui->lineEdit_5->setEchoMode(QLineEdit::Password);
   ui->lineEdit_6->setEchoMode(QLineEdit::Password);

   ClickableLabel * remove = new ClickableLabel("解除当前");
   ClickableLabel * add = new ClickableLabel("添加新卡");
   ClickableLabel * save = new ClickableLabel("保存");
   savePwd = new ClickableLabel("保存密码");
   label = new ClickableLabel;

   ClickableLabel * signout = new ClickableLabel("注销账户");
   ClickableLabel * logout = new ClickableLabel("logout");

   QPixmap mPicture;
   mPicture.load(path+"icon\\save.png");
   save->setPixmap(mPicture);

   mPicture.load(path+"icon\\error.png");
   label->setPixmap(mPicture);


   label->hide();

   remove->setStyleSheet("QLabel { color : #7086CF; }");
   add->setStyleSheet("QLabel {color : #7086CF; }");
   savePwd->setStyleSheet("QLabel {color : #888888; }");
   signout->setStyleSheet("QLabel {color : #7086CF; }");
   logout->setStyleSheet("QLabel {color : #7086CF; }");

   ui->label->setStyleSheet("QLabel {color : #8F8AA1; }");
   ui->label_2->setStyleSheet("QLabel {color : #8F8AA1; }");
   ui->label_3->setStyleSheet("QLabel {color : #8F8AA1; }");
   ui->label_4->setStyleSheet("QLabel {color : #8F8AA1; }");
   ui->label_5->setStyleSheet("QLabel {color : #8F8AA1; }");
   ui->label_6->setStyleSheet("QLabel {color : #8F8AA1; }");
   ui->label_7->setStyleSheet("QLabel {color : #8F8AA1; }");

   remove->setFont(QFont( "Timers" , 10 ,  QFont::Bold));
   add->setFont(QFont( "Timers" , 10 ,  QFont::Bold));

    ui->horizontalLayout_4->addWidget(remove);
    ui->horizontalLayout_4->addWidget(add);
    ui->horizontalLayout_2->addWidget(save);

    ui->horizontalLayout->addWidget(signout);
    ui->horizontalLayout->addWidget(logout);

    ui->horizontalLayout_5->addWidget(savePwd);

    ui->horizontalLayout_6->addWidget(label);


    for(int i = 0;i<user.getCard().size();i++){
        ui->comboBox->addItem(user.getCard().at(i),0);
    }

    connect(remove,SIGNAL(clicked()),this,SLOT(onRemoveCard()));
    connect(add,SIGNAL(clicked()),this,SLOT(onAddCard()));
    connect(save,SIGNAL(clicked()),this,SLOT(onSave()));
    connect(signout,SIGNAL(clicked()),this,SLOT(onSignout()));
    connect(logout,SIGNAL(clicked()),this,SLOT(onLogout()));
    connect(savePwd,SIGNAL(clicked()),this,SLOT(onSavePwd()));
    connect(ui->lineEdit_4,SIGNAL(textChanged(QString)),this,SLOT(onEnableBtn()));
    connect(ui->lineEdit_5,SIGNAL(textChanged(QString)),this,SLOT(onEnableBtn()));
    connect(ui->lineEdit_6,SIGNAL(textChanged(QString)),this,SLOT(onEnableBtn()));

    setMaximumSize(1000,500);
    setMinimumSize(1000,500);
}

Personnel::~Personnel()
{
    delete ui;
}

void Personnel::renewCard()
{
    UserDetail user;
    UserController controller ;
    user = controller.getAllUser().at(userNumber);

    ui->comboBox->clear();
    for(int i = 0;i<user.getCard().size();i++){
        ui->comboBox->addItem(user.getCard().at(i),0);
    }
}

void Personnel::onRemoveCard()
{
    if(ui->comboBox->count()>0)
    {
        UserController controller;
        QVector<UserDetail> allUsers = controller.getAllUser();

        QVector<QString> allCards = ((UserDetail&)allUsers.at(userNumber)).getCard();

        allCards.erase(allCards.begin()+ui->comboBox->currentIndex());

        ((UserDetail&)allUsers.at(userNumber)).setCard(allCards);

        controller.setAllUsers(allUsers);
        ui->comboBox->removeItem(ui->comboBox->currentIndex());
    }
}

void Personnel::onAddCard()
{
    newDialog =  new ChooseCardDialog;
    newDialog->setWindowModality(Qt::ApplicationModal);
    newDialog->show();

    connect(newDialog,SIGNAL(submit()),this,SLOT(sendAndGet()));

    renewCard();
}

void Personnel::sendAndGet()
{
    bool isExist = false;
    toServerMessage = "";

    UserController controller;
    UserDetail me = controller.getUser(userNumber);

    for(int i =0;i<me.getCard().size();i++){
        if(me.getCard().at(i)==newDialog->getUserCard())
            isExist = true;
    }

    if(!isExist)
    {
        toServerMessage +="addcard\\"+me.getId()+"\\"+QString::number(newDialog->getBank())
                +"\\"+newDialog->getUserCard()+"\\"+newDialog->getCardPassword()+"\\";

        ApplyCardServer * mserver = new ApplyCardServer;

        mserver->setMessage(toServerMessage);

        connect(mserver,SIGNAL(successAdd()),this,SLOT(onSuccessAdd()));
    }
    else
        QMessageBox::information(this,tr("reminder"),tr("The card already exist!"),tr("OK"),tr("EXIT"));

    renewCard();
}

void Personnel::onSave()
{
    UserController controller;
    QVector<UserDetail> allUsers = controller.getAllUser();
    ((UserDetail&)allUsers.at(userNumber)).setName(ui->lineEdit_2->text());
    controller.setAllUsers(allUsers);
    this->close();
}


void Personnel::onSignout()
{
    if (!(QMessageBox::information(this,tr("remind"),tr("Are you sure invalidate this one?"),tr("OK"),tr("EXIT"))))
    {
        UserController controller;
        QVector<UserDetail> allUsers = controller.getAllUser();
        allUsers.erase(allUsers.begin()+userNumber);
        controller.setAllUsers(allUsers);

        this->close();
        emit logout();
    }
}

void Personnel::onSavePwd()
{
    if(isOk == true){
        UserController controller;
        QVector<UserDetail> allUsers = controller.getAllUser();
        if(((UserDetail&)allUsers.at(userNumber)).getPassword()==ui->lineEdit_4->text()){
            ((UserDetail&)allUsers.at(userNumber)).setPassword(ui->lineEdit_5->text());
            controller.setAllUsers(allUsers);
            QMessageBox::information(this,tr("remind"),tr("Change succeed!"),tr("OK"),tr("EXIT"));
            this->close();
            emit logout();
        }
        else{
            QMessageBox::information(this,tr("remind"),tr("Password wrong!"),tr("OK"),tr("EXIT"));
        }

    }
}

void Personnel::onEnableBtn()
{
    if(ui->lineEdit_5->text().length()<=16&&ui->lineEdit_5->text().length()>=10&&
            ui->lineEdit_4->text().length()<=16&&ui->lineEdit_4->text().length()>=10&&
            ui->lineEdit_6->text().length()<=16&&ui->lineEdit_6->text().length()>=10&&
            ui->lineEdit_5->text()==ui->lineEdit_6->text()){
        savePwd->setStyleSheet("QLabel {color : #7086CF; }");
        isOk = true;
    }


    else{
        savePwd->setStyleSheet("QLabel {color : #888888; }");
        isOk = false;
    }

    if(ui->lineEdit_5->text()==ui->lineEdit_6->text())
        label->hide();
    else
        label->show();
}

void Personnel::onSuccessAdd()
{
    renewCard();
    newDialog->close();
}

void Personnel::onLogout()
{
    this->close();
    emit logout();
}
