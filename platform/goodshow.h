#ifndef GOODSHOW_H
#define GOODSHOW_H
#include "product.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVector>

class GoodShow:public QWidget
{
    Q_OBJECT
public:
    GoodShow();
    QVector<GoodShow *> getAllGoods(QVector<Book> allProducts);
    void enableBuyBtn();
    void setBtnUnVisible();
    void mousePressEvent(QMouseEvent* event);

signals:
    void detailEvent(int num);
    void click();

private slots:
    void onGoodDetail();
    void onBuyGood();

signals:
    void renewCart();
    void goodDetail();

public:
    int number;
    int kind;
    QPushButton * addGood;
    QLabel * goodPic;
    QLabel * goodName;
    QLabel * goodPrice;
    QLabel * nowPrice;
    QLabel * goodSurplus;

    QHBoxLayout *pr_btn;
    QHBoxLayout *label_btn;
    QVBoxLayout *total;

};

#endif // GOODSHOW_H



