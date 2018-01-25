#ifndef CHOOSECARDTOBUY_H
#define CHOOSECARDTOBUY_H

#include <QDialog>

namespace Ui {
class ChooseCardToBuy;
}

class ChooseCardToBuy : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseCardToBuy(QWidget *parent = 0);
    ~ChooseCardToBuy();
    void setCards(QVector<QString> cards);
    QString getCard();
    QString getPassword();
signals:
    void submit();

private slots:
    void onBuyBtn();
    void onEnableBuyBtn();

private:
    Ui::ChooseCardToBuy *ui;
};

#endif // CHOOSECARDTOBUY_H
