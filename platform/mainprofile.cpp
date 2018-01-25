#include "mainprofile.h"
#include "ui_mainprofile.h"
#include "goodshow.h"
#include "allshow.h"
#include "choosecarddialog.h"
#include "usercontroller.h"
#include "personnel.h"
#include "login.h"

//#include <QtNetwork>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QIcon>

extern QString choice;
QString searchKey = "2";
int searchCate;
extern QString path;
extern int userNumber;

MainProfile::MainProfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainProfile)
{
    newDialog = new ChooseCardDialog;
    ui->setupUi(this);
    ui->tabWidget->setLayoutDirection(Qt::LeftToRight);
    createCornerBtn();

    setMinimumSize(1320, 880);
    setMaximumSize(1320, 880);

    label = new QLabel;
    label->setPixmap(mPicture);


    QHBoxLayout * total = new QHBoxLayout;
    total->addWidget(label);

    A =new AllShow;

    category = new QComboBox;
    bt = new ClickableLabel;
    addCard = new ClickableLabel;
    PersonnDetail = new ClickableLabel;
    inLine = new QLineEdit;
    inLine->setStyleSheet("border-radius:10px;");

    QPixmap mPicture;
    mPicture.load(path+"icon\\search.png");
    bt->setPixmap(mPicture);
    mPicture.load(path+"icon\\add1.png");
    addCard->setPixmap(mPicture);
    mPicture.load(path+"icon\\person.png");
    PersonnDetail->setPixmap(mPicture);

    QFile file(path+"init.txt");
    if(!file.open(QFile::ReadOnly | QIODevice::Text)){

    }

    QLabel * profit = new QLabel("全场每满100-10");
    profit->setStyleSheet("QLabel {color : #8F8AA1; }");

    QTextStream readFile(&file);
    QString line = readFile.readLine();

    line = readFile.readLine();
    while(!line.isNull()){
        category->addItem(line,0);
        line = readFile.readLine();
    }

    file.close();

    QWidget * cornerWidget = new QWidget;

    QHBoxLayout * hLayout = new QHBoxLayout;

    hLayout->addWidget(profit);
    hLayout->addWidget(inLine);
    hLayout->addWidget(bt);
    hLayout->addWidget(PersonnDetail);

    inLine->setMinimumWidth(400);
    inLine->setMinimumHeight(25);

//    cornerWidget->setFixedSize(20,50);
    cornerWidget->setContentsMargins(0,0,0,0);
    cornerWidget->setLayout(hLayout);

    ui->tabWidget->setCornerWidget(cornerWidget,Qt::TopRightCorner);


    connect(bt,SIGNAL(clicked()),this,SLOT(onSearchBtn()));
    connect(bt,SIGNAL(clicked()),A,SLOT(onShowSearch()));
    connect(addCard,SIGNAL(clicked()),this,SLOT(onAddCard()));
    connect(A,SIGNAL(renewCarts()),this,SLOT(getRenewCarts()));
    connect(PersonnDetail,SIGNAL(clicked()),this,SLOT(onPersonnel()));

    QIcon mIcon;
    QPixmap m;

    shoppingCart = new ShoppingCart;
    m.load(path+"icon\\mall.png");
    mIcon.addPixmap(m);
    ui->tabWidget->addTab(A,mIcon,"Mall");

    m.load(path+"icon\\cart1.png");
    mIcon.addPixmap(m);
    ui->tabWidget->addTab(shoppingCart,mIcon,"Cart");



    choice = "food";

    searchCate=0;

//    ui->gridLayout->addWidget(A,0,0,1,1);
    connect(shoppingCart,SIGNAL(buySuccess()),A,SLOT(renewShow()));
}

MainProfile::~MainProfile()
{
    delete ui;
}

void MainProfile::createCornerBtn()
{


}

void MainProfile::onSetSearchKey(QString key)
{

}

void MainProfile::onSearchBtn()
{
    searchKey = inLine->text();
    ui->tabWidget->setCurrentIndex(0);
}

void MainProfile::getRenewCarts()
{
    shoppingCart->renewMyCart();
}

void MainProfile::onAddCard()
{

    newDialog->setWindowModality(Qt::ApplicationModal);
    newDialog->show();

    connect(newDialog,SIGNAL(submit()),this,SLOT(sendAndGet()));

}

void MainProfile::sendAndGet()
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
        qDebug()<<"??";

    }
    else
        QMessageBox::information(this,tr("reminder"),tr("The card already exist!"),tr("OK"),tr("EXIT"));
}

void MainProfile::onBuySuccess()
{

}

void MainProfile::onPersonnel()
{
    Personnel * person = new Personnel;
    connect(person,SIGNAL(logout()),this,SLOT(onLogout()));
    person->setWindowModality(Qt::ApplicationModal);
    person->show();
}

void MainProfile::onLogout()
{
    this->close();
    Login * l =  new Login;
    l->show();
}


