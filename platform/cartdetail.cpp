#include "cartdetail.h"
#include "productcontrol.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPalette>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
QVector<Appoint> buyAppoint;
extern int userNumber;
extern QString path;
CartDetail::CartDetail()
{
    newGoodShow = new GoodShow;
    deleteBtn = new ClickableLabel;
    add = new ClickableLabel;
    minus = new ClickableLabel;
    nowAmount = new QLabel("1");
    QHBoxLayout * below = new QHBoxLayout;
    QVBoxLayout * total = new QVBoxLayout;

    setMaximumSize(220,340);
    setMinimumSize(220,340);

    below->addWidget(add);
    below->addWidget(nowAmount);
    below->addWidget(minus);
    below->addWidget(deleteBtn);

    deleteBtn->setMargin(10);
    total->addWidget(newGoodShow);
    total->addLayout(below);

    QPixmap mPicture;
    mPicture.load(path+"icon\\delete.png");
    deleteBtn->setPixmap(mPicture);
    mPicture.load(path+"icon\\add.png");
    add->setPixmap(mPicture);
    mPicture.load(path+"icon\\remove.png");
    minus->setPixmap(mPicture);



    connect(deleteBtn,SIGNAL(clicked()),this,SLOT(ondeleteBtn()));

    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255,255,255));

    setLayout(total);
    connect(newGoodShow,SIGNAL(click()),this,SLOT(dealWith()));
    connect(this,SIGNAL(inclick()),this,SLOT(dealWith()));

    connect(add,SIGNAL(clicked()),this,SLOT(addAppoint()));
    connect(minus,SIGNAL(clicked()),this,SLOT(removeAppoint()));

}

void CartDetail::mousePressEvent(QMouseEvent *event)
{

    if(event->type() == QMouseEvent::MouseButtonPress){
       emit inclick();
    }


}

void CartDetail::setAppointOrder()
{
    ProductControl controller;
    QVector<Appoint> allAppoints = controller.getAllAppoints();

    for(int i= 0;i<allAppoints.size();i++){
        if(allAppoints.at(i).userNumber==userNumber
                &&newGoodShow->number==allAppoints.at(i).goodNumber&&
                newGoodShow->kind==allAppoints.at(i).goodKind){
             myAppointOrder=i;
             break;
        }
    }
}

void CartDetail::ondeleteBtn()
{
    ProductControl controller;
    QVector<Appoint> allAppoints = controller.getAllAppoints();

    QVector<Appoint>::iterator iter;
    for(iter = allAppoints.begin();iter<allAppoints.end();iter++){
        if(iter->userNumber==userNumber&&
                newGoodShow->number==iter->goodNumber&&
                newGoodShow->kind==iter->goodKind)
        {
             allAppoints.erase(iter);
             break;
        }
    }

    isChoosed = false;
    emit renew();
    emit click();

    controller.setAllAppoint(allAppoints);
}

void CartDetail::dealWith()
{

    QPalette palette;

    if(isChoosed == false ){
        Appoint newAppoint;
        newAppoint.userNumber = userNumber;
        newAppoint.goodKind = newGoodShow->kind;
        newAppoint.goodNumber = newGoodShow->number;
        newAppoint.amount = amount;
        buyAppoint.push_back(newAppoint);
        isChoosed = true;
        palette.setColor(QPalette::Background, QColor(186,196,240));

    }
    else{
        for(QVector<Appoint>::iterator iter = buyAppoint.begin();iter<buyAppoint.end();iter++){
            if(iter->userNumber==userNumber&&
                    iter->goodKind==newGoodShow->kind&&
                    iter->goodNumber==newGoodShow->number)
            {
                 buyAppoint.erase(iter);
                 break;
            }
        }
        palette.setColor(QPalette::Background, QColor(255,255,255));
        isChoosed = false;
    }
    this->setPalette(palette);

    emit click();
}

void CartDetail::addAppoint()
{
    bool isFind = false;
    ProductControl controller;
    QVector<Appoint> allAppoints = controller.getAllAppoints();

    int i =0;
    for(;i<allAppoints.size();i++){
        if(((Appoint&)(allAppoints.at(i))).userNumber==userNumber&&
                ((Appoint&)(allAppoints.at(i))).goodKind==newGoodShow->kind&&
                ((Appoint&)(allAppoints.at(i))).goodNumber==newGoodShow->number){
            isFind = true;
            if("库存:"+QString::number(((Appoint&)(allAppoints.at(i))).amount)==surplus)
                QMessageBox::information(this,tr("reminder"),tr("fail,no more goods"),tr("OK"),tr("EXIT"));
            else{
                ((Appoint&)(allAppoints.at(i))).addAmount();
                amount++;
                controller.setAllAppoint(allAppoints);

            }


            break;
        }
    }



    if(isChoosed){
        for(int j = 0;j<buyAppoint.size();j++){
            if(((Appoint&)(buyAppoint.at(j))).userNumber==userNumber&&
                    ((Appoint&)(buyAppoint.at(j))).goodKind==newGoodShow->kind&&
                    ((Appoint&)(buyAppoint.at(j))).goodNumber==newGoodShow->number){
                isFind = true;
                if("库存:"+QString::number(((Appoint&)(buyAppoint.at(j))).amount)!=surplus){
                    ((Appoint&)(buyAppoint.at(j))).addAmount();
                    emit click();
                }
                break;
            }
        }
    }


    nowAmount->setText(QString::number(amount));

}

void CartDetail::removeAppoint()
{
    bool isFind = false;
    ProductControl controller;
    QVector<Appoint> allAppoints = controller.getAllAppoints();
    int i =0;
    for(;i<allAppoints.size();i++){
        if(((Appoint&)(allAppoints.at(i))).userNumber==userNumber&&
                ((Appoint&)(allAppoints.at(i))).goodKind==newGoodShow->kind&&
                ((Appoint&)(allAppoints.at(i))).goodNumber==newGoodShow->number){
            isFind = true;
            if(((Appoint&)(allAppoints.at(i))).amount==1)
                QMessageBox::information(this,tr("reminder"),tr("fail,please delete it"),tr("OK"),tr("EXIT"));
            else
            {
                ((Appoint&)(allAppoints.at(i))).minusAmount();
                controller.setAllAppoint(allAppoints);
                amount--;

            }

            break;
        }
    }

    if(isChoosed){
        for(int j = 0;j<buyAppoint.size();j++){
            if(((Appoint&)(buyAppoint.at(j))).userNumber==userNumber&&
                    ((Appoint&)(buyAppoint.at(j))).goodKind==newGoodShow->kind&&
                    ((Appoint&)(buyAppoint.at(j))).goodNumber==newGoodShow->number){
                isFind = true;
                if(((Appoint&)(buyAppoint.at(j))).amount!=1){
                    ((Appoint&)(buyAppoint.at(j))).minusAmount();
                    emit click();
                }
                break;
            }
        }
    }



    nowAmount->setText(QString::number(amount));
}



//CartDetail::CartDetail(GoodShow *goodShow)
//{
//    newGoodShow = goodShow;
//    newRadioBtn = new QRadioButton("??");
//    deleteBtn = new QPushButton(">>");

//    QHBoxLayout * below = new QHBoxLayout;

//    QVBoxLayout * total = new QVBoxLayout;

//    below->addWidget(newRadioBtn);
//    below->addWidget(deleteBtn);

//    total->addLayout(below);
//    total->addWidget(newRadioBtn);

//    setLayout(total);
//}
