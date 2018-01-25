#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product   //产品基类
{
public:
    Product();

    void setName(QString name);
    void setPrice(float price);
    void setSurplus(int surplus);
    void setImage(QString img);
    void setDiscount(float dis);
    void setDetail(QString details);


    float getPrcie();
    QString getName();
    int getSurplus();
    QString getImg();
    float getDiscount();
    QString getDetails();


public:
    int order;
protected:
    QString mName;
    float mPrice;
    int mSurplus;
    QString mImage;
    float mDiscount;
    QString mDetails;
};



class Book:public Product   //书籍类
{

public:
    Book();
    void setName(QString name);
    void setPrice(float price);
    void setSurplus(int surplus);
    void setImage(QString img);
    void setDiscount(float dis);
    void setDetail(QString details);


    float getPrcie();
    QString getName();
    int getSurplus();
    QString getImg();
    float getDiscount();
    QString getDetails();


private:
    QString mCate = "book";
};


class Clothing:public Product   //衣物类
{
public:
    Clothing();
    void setName(QString name);
    void setPrice(float price);
    void setSurplus(int surplus);
    void setImage(QString img);
    void setDiscount(float dis);
    void setDetail(QString details);


    float getPrcie();
    QString getName();
    int getSurplus();
    QString getImg();
    float getDiscount();
    QString getDetails();
private:
     QString mCate = "clothing";
};


class Food:public Product   //食品类
{
public:
    Food();
    void setName(QString name);
    void setPrice(float price);
    void setSurplus(int surplus);
    void setImage(QString img);
    void setDiscount(float dis);
    void setDetail(QString details);


    float getPrcie();
    QString getName();
    int getSurplus();
    QString getImg();
    float getDiscount();
    QString getDetails();
private:
     QString mCate = "food";
};


class Appoint{      //

public:
    Appoint();
    bool equal(Appoint otherAppoint);
    void changeChecked();
    void addAmount();
    void minusAmount();
public:
    bool isCheck;
    int userNumber;
    int goodNumber;
    int goodKind;
    int amount;
};

#endif // PRODUCT_H
