#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}
/*! Класс начального окна
 *  Необходим для заполнения кориз шарами
 */
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    int getFirstBucketValue() const;
    int getSecondBucketValue() const;

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
