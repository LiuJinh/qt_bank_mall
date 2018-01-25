#include "allshow.h"
#include "ui_allshow.h"
#include "productcontrol.h"

#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

extern QString path;
extern QString searchKey;
extern int searchCate;
QString choice;

AllShow::AllShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllShow)
{
   ui->setupUi(this);

   currentPage = 0;


//   init();

   foodLabel = new ClickableLabel;
   clothingLabel = new ClickableLabel;
   bookLabel = new ClickableLabel;

   firstBtn = new ClickableLabel;
   finalBtn = new ClickableLabel;
   lastBtn = new ClickableLabel;
   nextBtn = new ClickableLabel;

   foodLabel->resize(30,30);
   QPixmap mPicture;
   mPicture.load(path+"icon\\food1.png");
   foodLabel->setPixmap(mPicture);
   mPicture.load(path+"icon\\clothing1.png");
   clothingLabel->setPixmap(mPicture);
   mPicture.load(path+"icon\\book1.png");
   bookLabel->setPixmap(mPicture);

   mPicture.load(path+"icon\\dleft.png");
   firstBtn->setPixmap(mPicture);
   mPicture.load(path+"icon\\left.png");
   lastBtn->setPixmap(mPicture);
   mPicture.load(path+"icon\\right.png");
   nextBtn->setPixmap(mPicture);
   mPicture.load(path+"icon\\dright.png");
   finalBtn->setPixmap(mPicture);

   ui->label->setStyleSheet("QLabel {color : #8F8AA1; }");
   ui->label->setFont(QFont( "Timers" , 15 ,  QFont::Bold));

   ui->horizontalLayout->addWidget(firstBtn);
   ui->horizontalLayout->addWidget(lastBtn);
   ui->horizontalLayout->addWidget(nextBtn);
   ui->horizontalLayout->addWidget(finalBtn);


   ui->verticalLayout->addWidget(foodLabel);
   ui->verticalLayout->addWidget(clothingLabel);
   ui->verticalLayout->addWidget(bookLabel);

   connect(firstBtn,SIGNAL(clicked()),this,SLOT(onFirstBtn()));
   connect(finalBtn,SIGNAL(clicked()),this,SLOT(onFinalBtn()));
   connect(lastBtn,SIGNAL(clicked()),this,SLOT(onLastBtn()));
   connect(nextBtn,SIGNAL(clicked()),this,SLOT(onNextBtn()));

   connect(foodLabel,SIGNAL(clicked()),this,SLOT(exhibitFood()));
   connect(clothingLabel,SIGNAL(clicked()),this,SLOT(exhibitClothing()));
   connect(bookLabel,SIGNAL(clicked()),this,SLOT(exhibitBook()));

   for(int i = 0;i<8;i++){
       GoodShow * newGoodShow = new GoodShow;
       connect(newGoodShow,SIGNAL(renewCart()),this,SLOT(getRenewCart()));
       allGoodsShow.push_back(newGoodShow);
       ui->gridLayout->addWidget(allGoodsShow.at(i),(i%8)/4,(i%8)%4,1,1);
   }

   for(int j = 0;j<8;j++)
       allGoodsShow.at(j)->setVisible(false);

}

AllShow::~AllShow()
{
    delete ui;
}

void AllShow::init()
{

    QString currentPath = path +"init.txt";


    QFile file(currentPath);
    if(!file.open(QFile::ReadOnly|QIODevice::Text)){
        qDebug()<<"something wrong";
    }

    QTextStream rd(&file);
    QString line = rd.readLine();
    line = rd.readLine();

    while(!line.isNull()){
       QPushButton * newPushBtn = new QPushButton;
       newPushBtn->setText(line);
       newPushBtn->resize(80,20);
       ui->verticalLayout->addWidget(newPushBtn);
       line = rd.readLine();

    }

    file.close();
}

void AllShow::showProducts(QVector<Book> allBooks)
{

    QPixmap mPicture;
    mPicture.load(path+"icon\\food1.png");
    foodLabel->setPixmap(mPicture);
    mPicture.load(path+"icon\\clothing1.png");
    clothingLabel->setPixmap(mPicture);
    mPicture.load(path+"icon\\book2.png");
    bookLabel->setPixmap(mPicture);

    int i =currentPage*8;

    for(int j = 0;j<8;j++)
        allGoodsShow.at(j)->setVisible(true);

    for(;i<allBooks.size()&&i<(currentPage+1)*8;i++){
        mPicture.load(path+"book\\images\\"+((Book&)allBooks.at(i)).getImg());

        allGoodsShow.at(i%8)->goodPic->setPixmap(mPicture);
        allGoodsShow.at(i%8)->goodName->setText(((Book&)allBooks.at(i)).getName());
        allGoodsShow.at(i%8)->addGood->setText("购买");
        allGoodsShow.at(i%8)->goodSurplus->setText("库存:"+QString::number(((Book&)allBooks.at(i)).getSurplus()));
        allGoodsShow.at(i%8)->goodPrice->setText("原价:"+QString::number(((Book&)allBooks.at(i)).getPrcie()));
        allGoodsShow.at(i%8)->nowPrice->setText("折后:"+QString::number(((Book&)allBooks.at(i)).getPrcie()*((Book&)allBooks.at(i)).getDiscount()));
        allGoodsShow.at(i%8)->number = ((Book&)allBooks.at(i)).order;
        allGoodsShow.at(i%8)->kind = mCate;
        allGoodsShow.at(i%8)->enableBuyBtn();
    }

    if(i<(currentPage+1)*8){
        for(;i<(currentPage+1)*8;i++)
            allGoodsShow.at(i%8)->setVisible(false);
    }


    ui->label->setText("Present:"+QString::number(currentPage+1)+"，Total:"+QString::number(allBooks.size()/8+(allBooks.size()%8==0?0:1)));

    if(allBooks.size()==0)
        ui->label->setText("No such book");
}

void AllShow::showProducts(QVector<Food> allFoods)
{
    QPixmap mPicture;
    mPicture.load(path+"icon\\food2.png");
    foodLabel->setPixmap(mPicture);
    mPicture.load(path+"icon\\clothing1.png");
    clothingLabel->setPixmap(mPicture);
    mPicture.load(path+"icon\\book1.png");
    bookLabel->setPixmap(mPicture);

    int i =currentPage*8;

    for(int j = 0;j<8;j++)
        allGoodsShow.at(j)->setVisible(true);

    for(;i<allFoods.size()&&i<(currentPage+1)*8;i++){
        mPicture.load(path+"food\\images\\"+((Food &)allFoods.at(i)).getImg());

        allGoodsShow.at(i%8)->goodPic->setPixmap(mPicture);
        allGoodsShow.at(i%8)->goodName->setText(((Food &)allFoods.at(i)).getName());
        allGoodsShow.at(i%8)->addGood->setText("购买");
        allGoodsShow.at(i%8)->goodSurplus->setText("库存:"+QString::number(((Food&)allFoods.at(i)).getSurplus()));
        allGoodsShow.at(i%8)->goodPrice->setText("原价:"+QString::number(((Food &)allFoods.at(i)).getPrcie()));
        allGoodsShow.at(i%8)->nowPrice->setText("折后:"+QString::number(((Food&)allFoods.at(i)).getPrcie()*((Food&)allFoods.at(i)).getDiscount()));
        allGoodsShow.at(i%8)->number = ((Food &)allFoods.at(i)).order;
        allGoodsShow.at(i%8)->kind = mCate;
        allGoodsShow.at(i%8)->enableBuyBtn();
    }

    if(i<(currentPage+1)*8){
        for(;i<(currentPage+1)*8;i++)
            allGoodsShow.at(i%8)->setVisible(false);
    }


    ui->label->setText("Present:"+QString::number(currentPage+1)+"，Total:"+QString::number(allFoods.size()/8+(allFoods.size()%8==0?0:1)));

    if(allFoods.size()==0)
        ui->label->setText("No such food");

}

void AllShow::showProducts(QVector<Clothing> allClothing)
{
    QPixmap mPicture;
    mPicture.load(path+"icon\\food1.png");
    foodLabel->setPixmap(mPicture);
    mPicture.load(path+"icon\\clothing2.png");
    clothingLabel->setPixmap(mPicture);
    mPicture.load(path+"icon\\book1.png");
    bookLabel->setPixmap(mPicture);

    int i =currentPage*8;

    for(int j = 0;j<8;j++)
        allGoodsShow.at(j)->setVisible(true);

    for(;i<allClothing.size()&&i<(currentPage+1)*8;i++){
        mPicture.load(path+"clothing\\images\\"+((Clothing&)allClothing.at(i)).getImg());

        allGoodsShow.at(i%8)->goodPic->setPixmap(mPicture);
        allGoodsShow.at(i%8)->goodName->setText(((Clothing&)allClothing.at(i)).getName());
        allGoodsShow.at(i%8)->addGood->setText("购买");
        allGoodsShow.at(i%8)->goodSurplus->setText("库存:"+QString::number(((Clothing&)allClothing.at(i)).getSurplus()));
        allGoodsShow.at(i%8)->goodPrice->setText("原价:"+QString::number(((Clothing&)allClothing.at(i)).getPrcie()));
        allGoodsShow.at(i%8)->nowPrice->setText("折后:"+QString::number(((Clothing&)allClothing.at(i)).getPrcie()*((Clothing&)allClothing.at(i)).getDiscount()));
        allGoodsShow.at(i%8)->number = ((Clothing&)allClothing.at(i)).order;
        allGoodsShow.at(i%8)->kind = mCate;
        allGoodsShow.at(i%8)->enableBuyBtn();
    }

    if(i<(currentPage+1)*8){
        for(;i<(currentPage+1)*8;i++)
            allGoodsShow.at(i%8)->setVisible(false);
    }

    ui->label->setText("Present:"+QString::number(currentPage+1)+"，Total:"+QString::number(allClothing.size()/8+(allClothing.size()%8==0?0:1)));

    if(allClothing.size()==0)
        ui->label->setText("No such clothing");
}


void AllShow::exhibitFood()
{
    mCate = 0;
    mAllFoods.clear();
    ProductControl controller;
    mAllFoods = controller.getAllFoods();
    currentPage = 0;
    showProducts(mAllFoods);
}

void AllShow::exhibitClothing()
{
    mCate = 1;
    mAllClothing.clear();
    ProductControl controller;
    mAllClothing = controller.getAllClothing();
    currentPage = 0;
    showProducts(mAllClothing);
}

void AllShow::exhibitBook()
{
    mCate = 2;
    mAllBooks.clear();
    ProductControl controller;
    mAllBooks = controller.getAllBooks();
    currentPage = 0;
    showProducts(mAllBooks);
}

void AllShow::onShowSearch()
{
    QVector<Book> allBook;
    QVector<Food> allFood;
    QVector<Clothing> allClothing;

    QVector<Food> suitFoods;
    QVector<Book> suitBooks;
    QVector<Clothing> suitClothing;
    ProductControl controller;

    currentPage = 0;

    switch (mCate) {
    case 0:

        allFood = controller.getAllFoods();

        for(int i = 0;i<allFood.size();i++){
            if(((Food &)allFood.at(i)).getName().contains(searchKey))
                suitFoods.push_back(allFood.at(i));
        }
        mAllFoods.clear();
        mAllFoods = suitFoods;
        mCate = 0;
        showProducts(suitFoods);
        ui->label->setText("Present:"+QString::number(currentPage+1)+"，Total:"+QString::number(suitFoods.size()/8+(suitFoods.size()%8==0?0:1)));
        if(suitFoods.size() ==0 ){
            ui->label->setText("No such food");
        }
        break;


    case 1:

        allClothing = controller.getAllClothing();

        for(int i = 0;i<allClothing.size();i++){
            if(((Clothing &)allClothing.at(i)).getName().contains(searchKey))
                suitClothing.push_back(allClothing.at(i));
        }
        mAllClothing.clear();
        mAllClothing = suitClothing;
        mCate = 1;
        showProducts(suitClothing);
        ui->label->setText("Present:"+QString::number(currentPage+1)+"，Total:"+QString::number(suitClothing.size()/8+(suitClothing.size()%8==0?0:1)));

        if(suitClothing.size() ==0 ){
            ui->label->setText("No such clothing");
        }
        break;

    case 2:

        allBook = controller.getAllBooks();

        for(int i = 0;i<allBook.size();i++){
            if(((Book &)allBook.at(i)).getName().contains(searchKey))
                suitBooks.push_back(allBook.at(i));
        }
        mAllBooks.clear();
        mAllBooks = suitBooks;
        mCate = 2;
        showProducts(suitBooks);
        ui->label->setText("Present:"+QString::number(currentPage+1)+"，Total:"+QString::number(suitBooks.size()/8+(suitBooks.size()%8==0?0:1)));
        if(suitBooks.size() ==0 ){
            ui->label->setText("No such book");
        }

        break;

    default:
        break;
    }



}

void AllShow::onFirstBtn()
{
    currentPage = 0;
    switch (mCate) {
    case 0:showProducts(mAllFoods);break;
    case 1:showProducts(mAllClothing);break;
    case 2:showProducts(mAllBooks);break;
    default:
        break;
    }
}

void AllShow::onFinalBtn()
{


    switch (mCate) {
    case 0:currentPage = mAllFoods.size()/8-((mAllFoods.size()%8==0?1:0));showProducts(mAllFoods);break;
    case 1:currentPage = mAllClothing.size()/8-((mAllClothing.size()%8==0?1:0));showProducts(mAllClothing);break;
    case 2:currentPage = mAllBooks.size()/8-((mAllBooks.size()%8==0?1:0));showProducts(mAllBooks);break;
    default:
        break;
    }
}

void AllShow::onLastBtn()
{
    if(currentPage==0)
        ;
    else{
        currentPage--;
    }
    switch (mCate) {
    case 0:showProducts(mAllFoods);break;
    case 1:showProducts(mAllClothing);break;
    case 2:showProducts(mAllBooks);break;
    default:
        break;
    }
}

void AllShow::onNextBtn()
{
    switch (mCate) {
    case 0:
        if(currentPage<((mAllFoods.size()/8)-((mAllFoods.size()%8)==0?1:0))){
            currentPage++;
        }
        showProducts(mAllFoods);break;
    case 1:
        if(currentPage<((mAllClothing.size()/8)-((mAllClothing.size()%8)==0?1:0))){
            currentPage++;
        }
        showProducts(mAllClothing);break;
    case 2:
        if(currentPage<((mAllBooks.size()/8)-((mAllBooks.size()%8)==0?1:0))){
            currentPage++;
        }
        showProducts(mAllBooks);break;
    default:
        break;
    }
}

void AllShow::getRenewCart()
{
    emit renewCarts();
}

void AllShow::renewShow()
{
    ProductControl controller;
    switch (mCate) {
    case 0:mAllFoods = controller.getAllFoods();showProducts(mAllFoods);break;
    case 1:mAllClothing = controller.getAllClothing();showProducts(mAllClothing);break;
    case 2:mAllBooks = controller.getAllBooks();showProducts(mAllBooks);break;
    default:
        break;
    }
}

