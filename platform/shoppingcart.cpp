#include "shoppingcart.h"
#include "ui_shoppingcart.h"
#include "productcontrol.h"
#include "choosecardtobuy.h"
#include "usercontroller.h"
#include "applycardserver.h"

#include <QMessageBox>
#include <QDebug>
extern int userNumber;
extern QString path;
extern QVector<Appoint> buyAppoint;
ShoppingCart::ShoppingCart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShoppingCart)
{
    ui->setupUi(this);
    currentPage = 0;
    pay = new ClickableLabel;
    firstBtn = new ClickableLabel;
    finalBtn = new ClickableLabel;
    lastBtn = new ClickableLabel;
    nextBtn = new ClickableLabel;

    QPixmap mPicture;
    mPicture.load(path+"icon\\pay.png");
    pay->setPixmap(mPicture);
    mPicture.load(path+"icon\\dleft.png");
    firstBtn->setPixmap(mPicture);
    mPicture.load(path+"icon\\left.png");
    lastBtn->setPixmap(mPicture);
    mPicture.load(path+"icon\\right.png");
    nextBtn->setPixmap(mPicture);
    mPicture.load(path+"icon\\dright.png");
    finalBtn->setPixmap(mPicture);

    ui->radioButton->setVisible(false);

    ui->horizontalLayout_2->addWidget(firstBtn);
    ui->horizontalLayout_2->addWidget(lastBtn);
    ui->horizontalLayout_2->addWidget(nextBtn);
    ui->horizontalLayout_2->addWidget(finalBtn);
    ui->horizontalLayout->addWidget(pay);

    ui->label->setStyleSheet("QLabel {color : #8F8AA1; }");
    ui->label->setFont(QFont( "Timers" , 15 ,  QFont::Bold));
    ui->total->setStyleSheet("QLabel {color : #8F8AA1; }");
    ui->total->setFont(QFont( "Timers" , 12 ,  QFont::Bold));
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255,255,255));
    for(int i = 0;i<10;i++){
        CartDetail * newDetail = new CartDetail;
        newDetail->setPalette(palette);
        allCartsShow.push_back(newDetail);
        connect(allCartsShow.at(i)->deleteBtn,SIGNAL(clicked()),this,SLOT(onDeleteCart()));
        connect(allCartsShow.at(i),SIGNAL(click()),this,SLOT(renewMoney()));
        connect(allCartsShow.at(i),SIGNAL(renew()),this,SLOT(renew()));
        ui->gridLayout->addWidget(allCartsShow.at(i),(i%10)/5,(i%10)%5,1,1);
    }

    for(int i =0;i<10;i++){
        allCartsShow.at(i)->setVisible(false);
    }

    myAppoints = getMyAppoint();

    connect(firstBtn,SIGNAL(clicked()),this,SLOT(onFirstBtn()));
    connect(finalBtn,SIGNAL(clicked()),this,SLOT(onFinalBtn()));
    connect(lastBtn,SIGNAL(clicked()),this,SLOT(onLastBtn()));
    connect(nextBtn,SIGNAL(clicked()),this,SLOT(onNextBtn()));
    connect(pay,SIGNAL(clicked()),this,SLOT(onBuyBtn()));

    connect(ui->radioButton,SIGNAL(toggled(bool)),this,SLOT(onIsChecked()));

    showCartDetail(myAppoints);
}

ShoppingCart::~ShoppingCart()
{
    delete ui;
}

void ShoppingCart::showCartDetail(QVector<Appoint> allAppoints)
{

    ui->radioButton->setChecked(false);
    for(int i =0;i<10;i++){
        allCartsShow.at(i)->setVisible(true);
        allCartsShow.at(i)->isChoosed = false;
    }

    int i = currentPage * 10;

    QPixmap mPicture;

    QVector<Appoint>::Iterator iter = allAppoints.begin();
    for(;i<(currentPage+1)*10&&i<allAppoints.size();i++){

        GoodShow * temp = getGoodShow(allAppoints.at(i));

        if(temp!=NULL){
            mPicture.load(temp->goodPic->text());
            allCartsShow.at(i%10)->newGoodShow->goodPic->setPixmap(mPicture);
            allCartsShow.at(i%10)->newGoodShow->goodName->setText(temp->goodName->text());
            allCartsShow.at(i%10)->newGoodShow->goodSurplus->setText(temp->goodSurplus->text());
            allCartsShow.at(i%10)->newGoodShow->goodPrice->setText(temp->goodPrice->text());
            allCartsShow.at(i%10)->newGoodShow->nowPrice->setText(temp->nowPrice->text());
            allCartsShow.at(i%10)->newGoodShow->number = allAppoints.at(i).goodNumber;
            allCartsShow.at(i%10)->newGoodShow->kind = allAppoints.at(i).goodKind;
            allCartsShow.at(i%10)->newGoodShow->setBtnUnVisible();
            allCartsShow.at(i%10)->nowAmount->setText(QString::number(allAppoints.at(i).amount));
            allCartsShow.at(i%10)->amount = allAppoints.at(i).amount;
            allCartsShow.at(i%10)->surplus = temp->goodSurplus->text();
            delete(temp);
        }
        else{
            allAppoints.erase(iter+i);
            i--;
        }

    }

    ui->radioButton->setChecked(false);
    if(i<(currentPage+1)*10){
        for(;i<(currentPage+1)*10;i++)
            allCartsShow.at(i%10)->setVisible(false);
    }

//    ui->radioButton->setChecked(false);
//    int j = currentPage*10;
//    i =0;

//    for(;j<(currentPage+1)*10;j++){
//        for(;i<buyAppoint.size();i++){
//            if(((Appoint&)allAppoints.at(j)).equal(buyAppoint.at(i))){
//                i++;
//                allCartsShow.at(j%10)->newRadioBtn->setChecked(true);
//                break;
//            }
//        }

//    }
    ui->label->setText("Present:"+QString::number(currentPage+1)+"，Total:"+QString::number(allAppoints.size()/10+(allAppoints.size()%10==0?0:1)));
    if(allAppoints.size() ==0 ){
        ui->label->setText("No goods");
    }

    myAppoints=getMyAppoint();
}

QVector<Appoint> ShoppingCart::getMyAppoint()
{
    ProductControl controller;
    QVector<Appoint> appoints,allAppoint;
    allAppoint = controller.getAllAppoints();
    for(int i = 0;i<allAppoint.size();i++){
        if(userNumber == allAppoint.at(i).userNumber){
            appoints.push_back(allAppoint.at(i));
        }
    }
    return appoints;
}

GoodShow * ShoppingCart::getGoodShow(Appoint appoint)
{
    ProductControl controller;

    Book mBook;
    Food mFood;
    Clothing mClothing;

//    QVector<Food > a/*llFoods =  controller.getAllFoods();*/
    GoodShow * newGoodShow = new GoodShow;

    switch (appoint.goodKind) {
    case 0:
        mFood=(Food &) controller.getAllFoods().at(appoint.goodNumber);

        newGoodShow->goodPic->setText(path+"food\\images\\"+mFood.getImg());
        newGoodShow->goodName->setText(mFood.getName());
        newGoodShow->goodSurplus->setText("库存:"+QString::number(mFood.getSurplus()));
        newGoodShow->goodPrice->setText("原价:"+QString::number(mFood.getPrcie()));
        newGoodShow->nowPrice->setText("折后:"+QString::number(mFood.getPrcie()*mFood.getDiscount()));
        newGoodShow->number = mFood.order;
        newGoodShow->kind = appoint.goodKind;

        break;

    case 1:
        mClothing=(Clothing &) controller.getAllClothing().at(appoint.goodNumber);

        newGoodShow->goodPic->setText(path+"clothing\\images\\"+mClothing.getImg());
        newGoodShow->goodName->setText(mClothing.getName());
        newGoodShow->goodSurplus->setText("库存:"+QString::number(mClothing.getSurplus()));
        newGoodShow->goodPrice->setText("原价:"+QString::number(mClothing.getPrcie()));
        newGoodShow->nowPrice->setText("折后:"+QString::number(mClothing.getPrcie()*mClothing.getDiscount()));
        newGoodShow->number = mClothing.order;
        newGoodShow->kind = appoint.goodKind;

        break;


    case 2:
        mBook=(Book &) controller.getAllBooks().at(appoint.goodNumber);

        newGoodShow->goodPic->setText(path+"book\\images\\"+mBook.getImg());
        newGoodShow->goodName->setText(mBook.getName());
        newGoodShow->goodSurplus->setText("库存:"+QString::number(mBook.getSurplus()));
        newGoodShow->goodPrice->setText("原价:"+QString::number(mBook.getPrcie()));
        newGoodShow->nowPrice->setText("折后:"+QString::number(mBook.getPrcie()*mBook.getDiscount()));
        newGoodShow->number = mBook.order;
        newGoodShow->kind = appoint.goodKind;

        break;
    default:
        break;
    }

    if(newGoodShow->goodSurplus->text()!="0")
        return newGoodShow;
    else return NULL;
}


void ShoppingCart::onFirstBtn()
{
    int temp = currentPage;
    buyAppoint.clear();
    currentPage = 0;
    showCartDetail(myAppoints);
    if(currentPage != temp){
        ui->total->setText("0");
        renewColor();
    }
}

void ShoppingCart::onFinalBtn()
{
    int temp = currentPage;
    buyAppoint.clear();
    currentPage = (myAppoints.size()/10)-(myAppoints.size()%10==0?1:0);
    showCartDetail(myAppoints);
    if(currentPage != temp){
        ui->total->setText("0");
        renewColor();
    }
}

void ShoppingCart::onLastBtn()
{
    int temp = currentPage;
    buyAppoint.clear();
    if(currentPage==0)
        ;
    else{
        currentPage--;
    }

    if(currentPage != temp){
        ui->total->setText("0");
        renewColor();
    }

    showCartDetail(myAppoints);
}

void ShoppingCart::onNextBtn()
{
    int temp = currentPage;
    buyAppoint.clear();
    if(currentPage<((myAppoints.size()/10)-(myAppoints.size()%10==0?1:0))){
        currentPage++;
    }
    showCartDetail(myAppoints);


    if(currentPage != temp){
        ui->total->setText("0");
        renewColor();
    }
}

void ShoppingCart::onDeleteCart()
{
    renewMyCart();
}

void ShoppingCart::onBuyBtn()
{
    UserController controller;
    renewtotalMoney();

    QVector<UserDetail> allUsers = controller.getAllUser();

    UserDetail me = allUsers.at(userNumber);

    newChoose = new ChooseCardToBuy;
    newChoose->setCards(me.getCard());
    newChoose->setWindowModality(Qt::ApplicationModal);
    newChoose->show();

    connect(newChoose,SIGNAL(submit()),this,SLOT(onBuySubmit()));
}

void ShoppingCart::onIsChecked()
{
    if(ui->radioButton->isChecked()){
        emit setChecked();
    }
    else{
        emit setUnChecked();
    }
}

void ShoppingCart::onJudgeChecked()
{
    if(ui->radioButton->isChecked()==true)
        ui->radioButton->setChecked(false);
}

void ShoppingCart::onBuySubmit()
{

    ProductControl controller;
    QString goods = "";
    QVector<Book> allMyBooks=controller.getAllBooks();
    QVector<Clothing> allMyClothing=controller.getAllClothing();
    QVector<Food> allMyFoods=controller.getAllFoods();

    QVector<Appoint> allAppoints = controller.getAllAppoints();
    QVector<Appoint>::iterator iter;

    bool isErase = false;

    qDebug()<<buyAppoint.size();
    int temp = buyAppoint.size();
    for(int j = 0;j<buyAppoint.size();j++){

        qDebug()<<j;
        isErase = false;
        switch (buyAppoint.at(j).goodKind){
        case 0:if(((Food &)allMyFoods.at(buyAppoint.at(j).goodNumber)).getSurplus()<buyAppoint.at(j).amount){
                goods+=((Food &)allMyFoods.at(buyAppoint.at(j).goodNumber)).getName()+',';
                isErase = true;
            }

                break;
        case 1:if(((Clothing&)allMyClothing.at(buyAppoint.at(j).goodNumber)).getSurplus()<buyAppoint.at(j).amount){
                goods+=((Clothing&)allMyClothing.at(buyAppoint.at(j).goodNumber)).getName()+',';
                isErase = true;
            }

                break;
        case 2:if(((Book&)allMyBooks.at(buyAppoint.at(j).goodNumber)).getSurplus()<buyAppoint.at(j).amount){
                goods+=((Book&)allMyBooks.at(buyAppoint.at(j).goodNumber)).getName()+',';
                isErase = true;
            }
                break;
        }
        if(isErase){
            buyAppoint.erase(buyAppoint.begin()+j);
            j--;

        }

    }

    qDebug()<<buyAppoint.size();
    renewtotalMoney();
    ui->total->setText("Money:$"+QString::number(totalMoney));

    if(goods!="")
        QMessageBox::information(this,tr("login fail"),goods+tr("购买时失败，库存不足!"),tr("OK"));

    QString toServerMessage = "";

    toServerMessage +="buy\\"+newChoose->getCard()+"\\"+newChoose->getPassword()
                +"\\"+QString::number(totalMoney)+"\\";


    ApplyCardServer * mserver = new ApplyCardServer;

    mserver->setMessage(toServerMessage);

    connect(mserver,SIGNAL(successBuy()),this,SLOT(onSuccessBuy()));
}

void ShoppingCart::onSuccessBuy()
{
    ProductControl controller;

    QVector<Book> allMyBooks=controller.getAllBooks();
    QVector<Clothing> allMyClothing=controller.getAllClothing();
    QVector<Food> allMyFoods=controller.getAllFoods();

    QVector<Appoint> allAppoints = controller.getAllAppoints();
    QVector<Appoint>::iterator iter;
    for(int j = 0;j<buyAppoint.size();j++){
        for(iter=allAppoints.begin();iter<allAppoints.end();iter++){
            if(iter->equal(buyAppoint.at(j)))
            {
                allAppoints.erase(iter);
                break;
            }
        }

        switch (buyAppoint.at(j).goodKind){
        case 0:if(((Food &)allMyFoods.at(buyAppoint.at(j).goodNumber)).getSurplus()>=buyAppoint.at(j).amount)
                ((Food&)allMyFoods.at(buyAppoint.at(j).goodNumber)).setSurplus(((Food &)allMyFoods.at(buyAppoint.at(j).goodNumber)).getSurplus()-buyAppoint.at(j).amount);break;
        case 1:if(((Clothing&)allMyClothing.at(buyAppoint.at(j).goodNumber)).getSurplus()>=buyAppoint.at(j).amount)
                ((Clothing&)allMyClothing.at(buyAppoint.at(j).goodNumber)).setSurplus(((Clothing&)allMyClothing.at(buyAppoint.at(j).goodNumber)).getSurplus()-buyAppoint.at(j).amount);break;
        case 2:if(((Book&)allMyBooks.at(buyAppoint.at(j).goodNumber)).getSurplus()>=buyAppoint.at(j).amount)
                ((Book&)allMyBooks.at(buyAppoint.at(j).goodNumber)).setSurplus(((Book&)allMyBooks.at(buyAppoint.at(j).goodNumber)).getSurplus()-buyAppoint.at(j).amount);break;

        }
    }

    controller.setAllBooks(allMyBooks);
    controller.setAllClothing(allMyClothing);
    controller.setAllFoods(allMyFoods);
    controller.setAllAppoint(allAppoints);
    newChoose->close();
    renewMyCart();
    emit buySuccess();
    renew();
}

void ShoppingCart::renewMoney()
{
    renewtotalMoney();
    ui->total->setText("Money:$"+QString::number(totalMoney));
}
   
void ShoppingCart::renewMyCart()
{
    myAppoints = getMyAppoint();
    renew();
    showCartDetail(myAppoints);
}

void ShoppingCart::renewColor()
{
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255,255,255));
    for(int i = 0;i<10;i++){
        allCartsShow.at(i)->setPalette(palette);

    }
}

void ShoppingCart::renewtotalMoney()
{
    totalMoney=0;
    for(int i = 0;i<buyAppoint.size();i++){
        ProductControl controller;
        Book myIdealBook;
        Clothing myIdealClothing;
        Food myIdealFood;

        switch (buyAppoint.at(i).goodKind){
        case 0:
            myIdealFood = controller.getAllFoods().at(buyAppoint.at(i).goodNumber);
            totalMoney+=myIdealFood.getDiscount()*myIdealFood.getPrcie()*(buyAppoint.at(i)).amount;
            break;

        case 1:
            myIdealClothing = controller.getAllClothing().at(buyAppoint.at(i).goodNumber);
            totalMoney+=myIdealClothing.getDiscount()*myIdealClothing.getPrcie()*(buyAppoint.at(i)).amount;
            break;

        case 2:
            myIdealBook = controller.getAllBooks().at(buyAppoint.at(i).goodNumber);
            totalMoney+=myIdealBook.getDiscount()*myIdealBook.getPrcie()*(buyAppoint.at(i)).amount;
            break;
        }
    }
    totalMoney -= ((int)totalMoney/100)*10;
}

void ShoppingCart::renew()
{
    renewColor();
    buyAppoint.clear();
    renewtotalMoney();

    ui->total->setText("Money:$"+QString::number(totalMoney));
}


