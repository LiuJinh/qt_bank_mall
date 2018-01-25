#ifndef PERSONDETAIL_H
#define PERSONDETAIL_H

#include <QWidget>

namespace Ui {
class PersonDetail;
}

class PersonDetail : public QWidget
{
    Q_OBJECT

public:
    explicit PersonDetail(QWidget *parent = 0);
    ~PersonDetail();

private:
    Ui::PersonDetail *ui;
};

#endif // PERSONDETAIL_H
