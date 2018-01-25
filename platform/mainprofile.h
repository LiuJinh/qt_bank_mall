#ifndef MAINPROFILE_H
#define MAINPROFILE_H
#include "shoppingcart.h"
#include "choosecarddialog.h"
#include "applycardserver.h"
#include "allshow.h"

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
namespace Ui {
class MainProfile;
}

class MainProfile : public QWidget
{
    Q_OBJECT

public:
    explicit MainProfile(QWidget *parent = 0);
    ~MainProfile();
    void onDoServerGet();
private:
    void createCornerBtn();
    void init();

signals:
    void doServerGet();


private slots:
    void onSetSearchKey(QString key);
    void onSearchBtn();
    void getRenewCarts();
    void onAddCard();
    void sendAndGet();
    void onBuySuccess();
    void onPersonnel();
    void onLogout();

//    void onGetMess();

private:
    Ui::MainProfile *ui;

private:
    AllShow * A;
    ShoppingCart * shoppingCart;
    QComboBox * category ;
    ClickableLabel * bt ;
    ClickableLabel * addCard;
    ClickableLabel * PersonnDetail;
    QLineEdit * inLine;

    QPixmap mPicture;
    QLabel *label;

    ChooseCardDialog * newDialog ;
    QString toServerMessage;
    QString fromServerMessage;
    ApplyCardServer * server;

};

#endif // MAINPROFILE_H
