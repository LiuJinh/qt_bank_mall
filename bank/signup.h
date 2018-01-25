#ifndef SIGNUP_H
#define SIGNUP_H


#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>


class SignUp:public QWidget
{

    Q_OBJECT

public:
    SignUp();
    void initBank();

signals:

private slots:
    void onEnableSignBtn();
    void onSubmitRequest();

private:
    QLabel *mName;
    QLabel *mId;
    QLabel *mPassword;
    QLabel *bankName;

    QLineEdit *nameLine;
    QLineEdit *idLine;
    QLineEdit *pwdLine;

    QComboBox *bankBox;
    QPushButton *sign;


};

#endif // SIGNUP_H
