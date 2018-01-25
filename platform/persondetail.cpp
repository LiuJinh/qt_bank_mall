#include "persondetail.h"
#include "ui_persondetail.h"

PersonDetail::PersonDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonDetail)
{
    ui->setupUi(this);
}

PersonDetail::~PersonDetail()
{
    delete ui;
}
