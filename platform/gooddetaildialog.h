#ifndef GOODDETAILDIALOG_H
#define GOODDETAILDIALOG_H

#include <QDialog>

namespace Ui {
class GoodDetailDialog;
}

class GoodDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GoodDetailDialog(QWidget *parent = 0);
    ~GoodDetailDialog();
    void setImage(QString imagePath);
    void setName(QString name);
    void setPrice(QString price);
    void setDiscount(QString discount);
    void setDetail(QString detail);
    void setCut(QString cut);
    void setSurplus(QString surplus);
//    void setEnableBuyBtn(QString surplus);

private slots:
    void onCloseBtn();
private:
    Ui::GoodDetailDialog *ui;
};

#endif // GOODDETAILDIALOG_H
