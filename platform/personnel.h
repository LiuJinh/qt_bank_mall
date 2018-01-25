#ifndef PERSONNEL_H
#define PERSONNEL_H

#include "choosecarddialog.h"
#include "clickablelabel.h"

#include <QWidget>
#include <QLabel>

namespace Ui {
class Personnel;
}

class Personnel : public QWidget
{
    Q_OBJECT

public:
    explicit Personnel(QWidget *parent = 0);
    ~Personnel();
    void renewCard();

signals:
    void logout();
private slots:
    void onRemoveCard();
    void onAddCard();
    void sendAndGet();
    void onSave();
    void onSignout();
    void onSavePwd();
    void onEnableBtn();
    void onSuccessAdd();
    void onLogout();
private:
    Ui::Personnel *ui;
    QString toServerMessage;
    ChooseCardDialog * newDialog;
    bool isOpen;
    ClickableLabel * savePwd;
    ClickableLabel * label;
    bool isOk;
};

#endif // PERSONNEL_H
