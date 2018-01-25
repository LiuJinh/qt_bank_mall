#ifndef CHOOSECARDDIALOG_H
#define CHOOSECARDDIALOG_H

#include <QDialog>

namespace Ui {
class ChooseCardDialog;
}

class ChooseCardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseCardDialog(QWidget *parent = 0);
    ~ChooseCardDialog();
    int getBank();
    QString getUserCard();
    QString getCardPassword();

signals:
    void submit();
private slots:
    void onEnableBtn();
    void onSubmitBtn();
private:
    Ui::ChooseCardDialog *ui;
};

#endif // CHOOSECARDDIALOG_H
