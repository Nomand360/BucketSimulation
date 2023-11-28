#include "MainWindow.h"
#include "Dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog dialog;
    const auto result = dialog.exec();
    int firstBucket;
    int secondBucket;
    if(result == QDialog::Accepted){
        firstBucket = dialog.getFirstBucketValue();
        secondBucket = dialog.getSecondBucketValue();

    }else{
        return a.exec();
    }
    MainWindow w(firstBucket, secondBucket);
    w.show();

    return a.exec();
}
