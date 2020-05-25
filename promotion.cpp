#include "promotion.h"
#include "ui_promotion.h"

Promotion::Promotion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Promotion)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->groupPieces->setId(ui->rdQueen,0);
    ui->groupPieces->setId(ui->rdRook,1);
    ui->groupPieces->setId(ui->rdBishop,2);
    ui->groupPieces->setId(ui->rdKnight,3);
}
int Promotion::getCheckedId(){
    return ui->groupPieces->checkedId();
}

Promotion::~Promotion()
{
    delete ui;
}
