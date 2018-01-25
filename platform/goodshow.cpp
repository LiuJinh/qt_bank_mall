
#include "goodshow.h"
#include "productcontrol.h"
#include "shoppingcart.h"

#include <QDialog>
#include <QMessageBox>
#include <gooddetaildialog.h>
#include <QPixmap>
#include <QFont>


extern int userNumber;
extern QString path;
GoodShow::GoodShow()
{
    addGood = new QPushButton;
    goodPic =  new QLabel;
    goodName = new QLabel;
    goodPrice = new QLabel;
    nowPrice = new QLabel;
    goodSurplus = new QLabel;
    pr_btn = new QHBoxLayout;
    total = new QVBoxLayout;
    label_btn = new QHBoxLayout;

    QFont newFont;
    newFont.setStrikeOut(true);
    goodPrice->setFont(newFont);
    goodName->setFont(QFont( "Timers" , 10 ,  QFont::Bold) );

    pr_btn->addWidget(goodSurplus);
    pr_btn->addWidget(addGood);

    label_btn->addWidget(goodPrice);
    label_btn->addWidget(nowPrice);

    total->addWidget(goodPic);
    total->addWidget(goodName);
    total->addLayout(label_btn);
    total->addLayout(pr_btn);

    goodName->setStyleSheet("QLabel {color : #847CA1; }");
    goodPrice->setStyleSheet("QLabel {color : #847CA1; }");
    nowPrice->setStyleSheet("QLabel {color : #847CA1; }");
    goodSurplus->setStyleSheet("QLabel {color : #847CA1; }");

    setMaximumSize(200,300);
    setMinimumSize(200,300);
    setLayout(total);

    connect(this,SIGNAL(goodDetail()),this,SLOT(onGoodDetail()));
    connect(addGood,SIGNAL(clicked(bool)),this,SLOT(onBuyGood()));
}

QVector<GoodShow *> GoodShow::getAllGoods(QVector<Book> allProducts)
{
    QVector<GoodShow *>  allGood;
    for(int i = 0;i<allProducts.size();i++){
       GoodShow * newGood = new GoodShow;
       newGood->goodPrice->setText( QString("%1").arg(((Book&)allProducts.at(i)).getPrcie()));
       allGood.push_back(newGood);
    }

    return allGood;
}

void GoodShow::enableBuyBtn()
{
    if(goodSurplus->text()!="0"&&goodSurplus->text()!="库存:0")
        addGood->setEnabled(true);
    else
        addGood->setEnabled(false);
}

void GoodShow::setBtnUnVisible()
{
    addGood->setVisible(false);
}

void GoodShow::mousePressEvent(QMouseEvent *event)
{
    if(event->type() == QEvent::MouseButtonDblClick)
        emit goodDetail();
    else if(event->type() == QEvent::MouseButtonPress)
        emit click();
}

void GoodShow::onGoodDetail()
{
    GoodDetailDialog * newDialog = new GoodDetailDialog;
    ProductControl controller ;
    Food newFood;
    Clothing newClothing;
    Book newBook;


    switch (kind) {
    case 0:
        newFood = (Food&)controller.getAllFoods().at(number);
        newDialog->setImage(path+"food\\images\\"+newFood.getImg());
        newDialog->setName(newFood.getName());
        newDialog->setPrice("原价:"+QString::number(newFood.getPrcie()));
        newDialog->setDiscount("折后:"+QString::number(newFood.getDiscount()*newFood.getPrcie()));
        newDialog->setDetail(newFood.getDetails());
        newDialog->setSurplus(QString::number(newFood.getSurplus()));
//        newDialog->setEnableBuyBtn(QString::number(newFood.getSurplus()));
        break;

    case 1:
        newClothing = (Clothing&)(controller.getAllClothing().at(number));
        newDialog->setImage(path+"clothing\\images\\"+newClothing.getImg());
        newDialog->setName(newClothing.getName());
        newDialog->setPrice("原价:"+QString::number(newClothing.getPrcie()));
        newDialog->setDiscount("折后:"+QString::number(newClothing.getDiscount()*newClothing.getPrcie()));
        newDialog->setDetail(newClothing.getDetails());
        newDialog->setSurplus(QString::number(newClothing.getSurplus()));
//        newDialog->setEnableBuyBtn(QString::number(newClothing.getSurplus()));
        break;

    case 2:
        newBook = (Book &)controller.getAllBooks().at(number);
        newDialog->setImage(path+"book\\images\\"+newBook.getImg());
        newDialog->setName(newBook.getName());
        newDialog->setPrice("原价:"+QString::number(newBook.getPrcie()));
        newDialog->setDiscount("折后:"+QString::number(newBook.getDiscount()*newBook.getPrcie()));
        newDialog->setDetail(newBook.getDetails());
        newDialog->setSurplus(QString::number(newBook.getSurplus()));
//        newDialog->setEnableBuyBtn(QString::number(newBook.getSurplus()));
        break;
    default:
        break;
    }

    newDialog->setWindowModality(Qt::ApplicationModal);
    newDialog->show();
}

void GoodShow::onBuyGood()
{
    bool isFind = false;
    if (!(QMessageBox::information(this,tr("reminder"),tr("Are you sure buy it?"),tr("OK"),tr("EXIT"))))
    {


        ProductControl controller;
        QVector<Appoint> allAppoints = controller.getAllAppoints();

        Appoint newAppoint;
        newAppoint.userNumber = userNumber;
        newAppoint.goodNumber = number;
        newAppoint.goodKind = kind;
        newAppoint.amount = 1;
        for(int i =0;i<allAppoints.size();i++){
            if(newAppoint.equal(allAppoints.at(i))){
                if("库存:"+QString::number(((Appoint&)(allAppoints.at(i))).amount)==this->goodSurplus->text())
                    QMessageBox::information(this,tr("reminder"),tr("fail,no more goods"),tr("OK"),tr("EXIT"));
                else
                    ((Appoint&)(allAppoints.at(i))).addAmount();
                isFind=true;
            }
        }


    if(!isFind)
        allAppoints.push_back(newAppoint);
    controller.setAllAppoint(allAppoints);

    emit renewCart();
    }
    else
       ;
}






