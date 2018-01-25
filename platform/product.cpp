#include "product.h"

Product::Product()
{

}

float Product::getPrcie()
{
    return mPrice;
}

QString Product::getName()
{
    return mName;
}

int Product::getSurplus()
{
    return mSurplus;
}

QString Product::getImg()
{
    return mImage;
}

float Product::getDiscount()
{
    return mDiscount;
}

QString Product::getDetails()
{
    return mDetails;
}

void Product::setName(QString name)
{
    mName = name;
}

void Product::setPrice(float price)
{
    mPrice = price;
}

void Product::setSurplus(int surplus)
{
    mSurplus = surplus;
}

void Product::setImage(QString img)
{
    mImage = img;
}

void Product::setDiscount(float dis)
{
    mDiscount = dis;
}

void Product::setDetail(QString details)
{
    mDetails = details;
}

Book::Book()
{
    mPrice = 0;
    mSurplus=0;
    mDiscount=0.1;
}

float Book::getPrcie()
{
    return mPrice;
}

QString Book::getName()
{
    return mName;
}

int Book::getSurplus()
{
    return mSurplus;
}

QString Book::getImg()
{
    return mImage;
}

float Book::getDiscount()
{
    return mDiscount;
}

QString Book::getDetails()
{
    return mDetails;
}

void Book::setName(QString name)
{
    mName = name;
}

void Book::setPrice(float price)
{
    mPrice = price;
}

void Book::setSurplus(int surplus)
{
    mSurplus = surplus;
}

void Book::setImage(QString img)
{
    mImage = img;
}

void Book::setDiscount(float dis)
{
    mDiscount = dis;
}

void Book::setDetail(QString details)
{
    mDetails = details;
}

Clothing::Clothing()
{

}

float Clothing::getPrcie()
{
    return mPrice;
}

QString Clothing::getName()
{
    return mName;
}

int Clothing::getSurplus()
{
    return mSurplus;
}

QString Clothing::getImg()
{
    return mImage;
}

float Clothing::getDiscount()
{
    return mDiscount;
}

QString Clothing::getDetails()
{
    return mDetails;
}

void Clothing::setName(QString name)
{
    mName = name;
}

void Clothing::setPrice(float price)
{
    mPrice = price;
}

void Clothing::setSurplus(int surplus)
{
    mSurplus = surplus;
}

void Clothing::setImage(QString img)
{
    mImage = img;
}

void Clothing::setDiscount(float dis)
{
    mDiscount = dis;
}

void Clothing::setDetail(QString details)
{
    mDetails = details;
}

Food::Food()
{

}


float Food::getPrcie()
{
    return mPrice;
}

QString Food::getName()
{
    return mName;
}

int Food::getSurplus()
{
    return mSurplus;
}

QString Food::getImg()
{
    return mImage;
}

float Food::getDiscount()
{
    return mDiscount;
}

QString Food::getDetails()
{
    return mDetails;
}

void Food::setName(QString name)
{
    mName = name;
}

void Food::setPrice(float price)
{
    mPrice = price;
}

void Food::setSurplus(int surplus)
{
    mSurplus = surplus;
}

void Food::setImage(QString img)
{
    mImage = img;
}

void Food::setDiscount(float dis)
{
    mDiscount = dis;
}

void Food::setDetail(QString details)
{
    mDetails = details;
}

Appoint::Appoint()
{

}

bool Appoint::equal(Appoint otherAppoint)
{
    if(userNumber==otherAppoint.userNumber&&goodNumber==otherAppoint.goodNumber&&
            goodKind==otherAppoint.goodKind)
        return true;
    else
        return false;
}

void Appoint::changeChecked()
{
    isCheck = !isCheck;

}

void Appoint::minusAmount()
{
    amount--;
}

void Appoint::addAmount()
{
    amount++;
}
