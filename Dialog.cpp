#include "Dialog.h"
#include "ui_Dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

int Dialog::getFirstBucketValue() const
{
    return ui->spinBox->value();
}

int Dialog::getSecondBucketValue() const
{
    return ui->spinBox_2->value();
}
