#ifndef CARTDETAIL_H
#define CARTDETAIL_H

#include "clickablelabel.h"

#include <QWidget>
#include <goodshow.h>
#include <QRadioButton>
#include <QPushButton>

class CartDetail:public QWidget
{
        Q_OBJECT
public:
    CartDetail();
    CartDetail(GoodShow * goodShow);
    void mousePressEvent(QMouseEvent* event);
    void setAppointOrder();

public:
    int amount;
    QString surplus;
    GoodShow * newGoodShow;
    int myAppointOrder;
    ClickableLabel * deleteBtn;
    bool isChoosed;
    ClickableLabel * add;
    ClickableLabel * minus;
    QLabel * nowAmount;

signals:
    void click();
    void inclick();
    void renew();
//private:


private slots:
    void ondeleteBtn();
    void dealWith();
    void addAppoint();
    void removeAppoint();

};

#endif // CARTDETAIL_H
