#include "choosecarddialog.h"
#include "ui_choosecarddialog.h"
#include "commonfunc.h"

ChooseCardDialog::ChooseCardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseCardDialog)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);

    ui->comboBox->addItem("中国工商银行",0);
    ui->comboBox->addItem("中国建设银行",0);
    ui->comboBox->addItem("中国农业银行",0);
    ui->comboBox->addItem("中国邮政储蓄",0);

    ui->label->setStyleSheet("QLabel {color : #8F8AA1; }");
    ui->label_2->setStyleSheet("QLabel {color : #8F8AA1; }");
    ui->label_3->setStyleSheet("QLabel {color : #8F8AA1; }");

    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(onEnableBtn()));
    connect(ui->lineEdit_2,SIGNAL(textChanged(QString)),this,SLOT(onEnableBtn()));

    connect(ui->okBtn,SIGNAL(clicked(bool)),this,SLOT(onSubmitBtn()));
    connect(ui->cancelBtn,SIGNAL(clicked(bool)),this,SLOT(close()));

    ui->okBtn->setEnabled(false);
}

ChooseCardDialog::~ChooseCardDialog()
{
    delete ui;
}

int ChooseCardDialog::getBank()
{
    return ui->comboBox->currentIndex();
}

QString ChooseCardDialog::getUserCard()
{
    return ui->lineEdit->text();
}

QString ChooseCardDialog::getCardPassword()
{
    return ui->lineEdit_2->text();
}

void ChooseCardDialog::onEnableBtn()
{
    CommonFunc func;
    if(func.isAllNumber(ui->lineEdit->text())&&ui->lineEdit->text().length()==19
            &&func.isAllNumber(ui->lineEdit_2->text())&&ui->lineEdit_2->text().length()==6)
        ui->okBtn->setEnabled(true);
    else
        ui->okBtn->setEnabled(false);
}

void ChooseCardDialog::onSubmitBtn()
{
    emit submit();
}



