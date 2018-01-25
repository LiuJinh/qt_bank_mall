#ifndef ALLSHOW_H
#define ALLSHOW_H

#include"goodshow.h"
#include"product.h"
#include "clickablelabel.h"

#include <QWidget>
#include <QGridLayout>

namespace Ui {
class AllShow;
}

class AllShow : public QWidget
{
    Q_OBJECT

public:
    explicit AllShow(QWidget *parent = 0);
    ~AllShow();
    void init();
    void showProducts(QVector<Book> allBooks);
    void showProducts(QVector<Food> allFoods);
    void showProducts(QVector<Clothing> allClothing);


private slots:
    void exhibitFood();
    void exhibitClothing();
    void exhibitBook();
    void onShowSearch();
    void onFirstBtn();
    void onFinalBtn();
    void onLastBtn();
    void onNextBtn();
    void getRenewCart();
    void renewShow();

signals:
    void renewCarts();
    int exhibitCate();

private:
    Ui::AllShow *ui;
    QGridLayout * totalLayout;
    int currentPage;
    QVector<GoodShow*> allGoodsShow;
    QVector<Book> mAllBooks;
    QVector<Food> mAllFoods;
    QVector<Clothing> mAllClothing;
    int mCate=0;

    ClickableLabel * foodLabel;
    ClickableLabel * clothingLabel;
    ClickableLabel * bookLabel;

    ClickableLabel * firstBtn;
    ClickableLabel * finalBtn;
    ClickableLabel * lastBtn;
    ClickableLabel * nextBtn;

};

#endif // ALLSHOW_H
