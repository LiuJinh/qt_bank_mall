#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H
#include "product.h"
#include "cartdetail.h"
#include "shoppingcart.h"
#include "choosecardtobuy.h"
#include "clickablelabel.h"

#include <QWidget>
#include <QVector>


namespace Ui {
class ShoppingCart;
}

class ShoppingCart : public QWidget
{
    Q_OBJECT

public:
    explicit ShoppingCart(QWidget *parent = 0);
    ~ShoppingCart();
    void showCartDetail(QVector<Appoint> allAppoints);
    QVector<Appoint> getMyAppoint();
    GoodShow * getGoodShow(Appoint appoint);
    void renewMyCart();
    void renewColor();
    void renewtotalMoney();

signals:
    void setChecked();
    void setUnChecked();
    void buySuccess();

private slots:
    void renew();
    void onFirstBtn();
    void onFinalBtn();
    void onLastBtn();
    void onNextBtn();
    void onDeleteCart();
    void onBuyBtn();
    void onIsChecked();
    void onJudgeChecked();
    void onBuySubmit();
    void onSuccessBuy();
    void renewMoney();

private:
    QVector<CartDetail*> allCartsShow;
    QVector<Appoint> myAppoints;
    QVector<Appoint> submitAppoints;
    int currentPage;
    Ui::ShoppingCart *ui;
    float totalMoney;
    ChooseCardToBuy * newChoose;
    ClickableLabel * pay;
    ClickableLabel * firstBtn;
    ClickableLabel * finalBtn;
    ClickableLabel * lastBtn;
    ClickableLabel * nextBtn;
    ClickableLabel * addCard;
};

#endif // SHOPPINGCART_H
