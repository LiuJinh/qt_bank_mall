#ifndef TRANSFER_H
#define TRANSFER_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

class Transfer:public QDialog
{
    Q_OBJECT

public:
    Transfer();
    void initBank();

signals:

    int changeValue(int ch);
private slots:
    void onEnableTransBtn();
    void onTransBtn();
private:
    QLabel * bankLabel;
    QLabel * userLabel;
    QLabel * moneyLabel;

    QLineEdit *userLine;
    QLineEdit *moneyLine;
    QComboBox *bankBox;

    QPushButton *transBtn;
    QPushButton *quitBtn;
};

#endif // TRANSFER_H
