#ifndef PRODUCTCONTROL_H
#define PRODUCTCONTROL_H


#include "product.h"


#include <QVector>
class ProductControl
{
public:
    ProductControl();

    QVector<Book> getAllBooks();        //获取书籍
    QVector<Food> getAllFoods();        //获取食品
    QVector<Clothing> getAllClothing();//获取衣物

    void setAllBooks(QVector<Book> allBooks);//设置书籍
    void setAllFoods(QVector<Food> allFoods);//设置食品
    void setAllClothing(QVector<Clothing> allClothing);//设置衣物

    QVector<Appoint> getAllAppoints();//获取订单
    void setAllAppoint(QVector<Appoint> allAppoints);//设置订单

};

#endif // PRODUCTCONTROL_H
