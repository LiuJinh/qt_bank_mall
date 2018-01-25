#include "gooddetaildialog.h"
#include "ui_gooddetaildialog.h"

#include  <QPixmap>
#include <QFont>

GoodDetailDialog::GoodDetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoodDetailDialog)
{
    ui->setupUi(this);

    QFont newFont;
    newFont.setStrikeOut(true);

    ui->priceLabel->setStyleSheet("QLabel {color : #847CA1; }");
    ui->discountLabel->setStyleSheet("QLabel {color : #847CA1; }");
    ui->detailLabel->setStyleSheet("QLabel {color : #847CA1; }");
    ui->cutLabel->setStyleSheet("QLabel {color : #847CA1; }");
    ui->nameLable->setStyleSheet("QLabel {color : #847CA1; }");
    ui->priceLabel->setFont(newFont);
    ui->detailLabel->setWordWrap(true);
    ui->detailLabel->setAlignment(Qt::AlignTop);
    connect(ui->cancelBtn,SIGNAL(clicked(bool)),this,SLOT(onCloseBtn()));
}

GoodDetailDialog::~GoodDetailDialog()
{
    delete ui;
}

void GoodDetailDialog::setImage(QString imagePath)
{
    QPixmap mPicture;
    mPicture.load(imagePath);
    ui->imageLabel->setPixmap(mPicture);
}

void GoodDetailDialog::setName(QString name)
{
    ui->nameLable->setText(name);
}

void GoodDetailDialog::setPrice(QString price)
{
    ui->priceLabel->setText(price);
}

void GoodDetailDialog::setDiscount(QString discount)
{
    ui->discountLabel->setText(discount);
}

void GoodDetailDialog::setDetail(QString detail)
{
    ui->detailLabel->setText(detail);
}

void GoodDetailDialog::setCut(QString cut)
{
    ui->cutLabel->setText(cut);
}

void GoodDetailDialog::setSurplus(QString surplus)
{
    ui->cutLabel->setText("库存:"+surplus);
}

//void GoodDetailDialog::setEnableBuyBtn(QString surplus)
//{
//    if(surplus=="0"){
//        ui->buyBtn->setEnabled(false);
//    }
//    else
//        ui->buyBtn->setEnabled(true);
//}

void GoodDetailDialog::onCloseBtn()
{
    this->close();
}
