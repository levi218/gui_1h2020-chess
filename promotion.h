#ifndef PROMOTION_H
#define PROMOTION_H

#include <QDialog>

namespace Ui {
class Promotion;
}

class Promotion : public QDialog
{
    Q_OBJECT

public:
    explicit Promotion(QWidget *parent = 0);
    int getCheckedId();
    ~Promotion();

private:
    Ui::Promotion *ui;
};

#endif // PROMOTION_H
