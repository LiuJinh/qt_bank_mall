#include "choosecardtobuy.h"
#include "ui_choosecardtobuy.h"
#include "commonfunc.h"

ChooseCardToBuy::ChooseCardToBuy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseCardToBuy)
{
    ui->setupUi(this);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    connect(ui->exitBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->buyBtn,SIGNAL(clicked(bool)),this,SLOT(onBuyBtn()));
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(onEnableBuyBtn()));

    ui->label->setStyleSheet("QLabel {color : #8F8AA1; }");
    ui->label_2->setStyleSheet("QLabel {color : #8F8AA1; }");

    ui->buyBtn->setEnabled(false);
}

ChooseCardToBuy::~ChooseCardToBuy()
{
    delete ui;
}

void ChooseCardToBuy::setCards(QVector<QString> cards)
{
    for(int i = 0;i<cards.size();i++){
        ui->comboBox->addItem(cards.at(i),0);
    }
}

QString ChooseCardToBuy::getCard()
{
    return ui->comboBox->currentText();
}


QString ChooseCardToBuy::getPassword()
{
     return ui->lineEdit->text();
}

void ChooseCardToBuy::onBuyBtn()
{
    emit submit();
}

void ChooseCardToBuy::onEnableBuyBtn()
{
    CommonFunc func;
    if(func.isAllNumber(ui->lineEdit->text())&&ui->lineEdit->text().length()==6){
        ui->buyBtn->setEnabled(true);

    }
    else
        ui->buyBtn->setEnabled(false);
}

