#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "Bucket.h"
#include <QMessageBox>

MainWindow::MainWindow(int fBucket, int sBucket, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    firstBucket = std::make_shared<Bucket>(fBucket);
    secondBucket = std::make_shared<Bucket>(sBucket);
    updateFirstBucket();
    updateSecondBucket();
    updateOverallProbability();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateFirstBucket()
{
    ui->firstBucketBallsCount->setText(QString::number(firstBucket->ballsCount()));
    ui->firstBucketBlueBallsCount->setText(QString::number(firstBucket->getBlueBallsCount()));
    ui->firstBucketRedBallsCount->setText(QString::number(firstBucket->getRedBallsCount()));
    ui->firstBucketBlueProbability->setText(QString::number(firstBucket->getBlueBallProbability(), 'g', 3) + '%');
    ui->firstBucketRedProbability->setText(QString::number(firstBucket->getRedBallProbability(), 'g', 3) + '%');
}

void MainWindow::updateSecondBucket()
{
    ui->secondBucketBallsCount->setText(QString::number(secondBucket->ballsCount()));
    ui->secondBucketBlueBallsCount->setText(QString::number(secondBucket->getBlueBallsCount()));
    ui->secondBucketRedBallsCount->setText(QString::number(secondBucket->getRedBallsCount()));
    ui->secondBucketBlueProbability->setText(QString::number(secondBucket->getBlueBallProbability(), 'g', 3) + '%');
    ui->secondBucketRedProbability->setText(QString::number(secondBucket->getRedBallProbability(), 'g', 3) + '%');
}

void MainWindow::updateOverallProbability()
{
    ui->twoBlueProbability->setText(QString::number((getTwoBlueBallProbability() * 100.f), 'g', 3) + '%');
    ui->twoRedProbability->setText(QString::number((getTwoRedBallProbability() * 100.f), 'g', 3) + '%');
    ui->oneBlueOneRedProbability->setText(QString::number((getOvervallProbability() * 100.f), 'g', 3) + '%');
}

void MainWindow::exctractFromFirst()
{
    firstBucket->extractBall();
    firstBucket->extractBall();
    updateFirstBucket();
    updateOverallProbability();
}

void MainWindow::extractFromSecond()
{
    secondBucket->extractBall();
    secondBucket->extractBall();
    updateSecondBucket();
    updateOverallProbability();
}

void MainWindow::extractByRotation()
{
    firstBucket->extractBall();
    secondBucket->extractBall();
    updateFirstBucket();
    updateSecondBucket();
    updateOverallProbability();
}

void MainWindow::createError()
{
    QMessageBox::critical(nullptr, "Ошибка", "Недостаточно шаров для извлечения!");
}

double MainWindow::getTwoBlueBallProbability()
{
    double ans = (double)(firstBucket->getBlueBallsCount() + secondBucket->getBlueBallsCount()) / (double)(firstBucket->ballsCount() + secondBucket->ballsCount()) *
                 (double)(firstBucket->getBlueBallsCount() + secondBucket->getBlueBallsCount() - 1) / (double)(firstBucket->ballsCount() + secondBucket->ballsCount() - 1);
    return ans;
}

double MainWindow::getTwoRedBallProbability()
{
    double ans = (double)(firstBucket->getRedBallsCount() + secondBucket->getRedBallsCount()) / (double)(firstBucket->ballsCount() + secondBucket->ballsCount()) *
                 (double)(firstBucket->getRedBallsCount() + secondBucket->getRedBallsCount() - 1) / (double)(firstBucket->ballsCount() + secondBucket->ballsCount() - 1);
    return ans;
}

double MainWindow::getOvervallProbability()
{
    return 1.f - getTwoBlueBallProbability() - getTwoRedBallProbability();
}


void MainWindow::on_moveBalltoSecondBucketButton_clicked()
{
    if(firstBucket->ballsCount() > 0){
        if(auto ball = firstBucket->takeBallFromBucket()){
            secondBucket->putBallToBucket(ball);
            updateFirstBucket();
            updateSecondBucket();
            updateOverallProbability();
            if(ball->getColor() == BallColor::Red){
                ui->firstBucketLastMoved->setText("извлекли красный шар");
            }
            else{
                ui->firstBucketLastMoved->setText("извлекли синий шар");
            }
        }
        else{
            QMessageBox::critical(nullptr, "Ошибка", "Ошибка перемещения!");
        }
    }
    else{
        QMessageBox::critical(nullptr, "Ошибка", "Первая корзина пуста!");
    }
}


void MainWindow::on_moveBalltoFirstBucketButton_clicked()
{
    if(secondBucket->ballsCount() > 0){
        if(auto ball = secondBucket->takeBallFromBucket()){
            firstBucket->putBallToBucket(ball);
            updateFirstBucket();
            updateSecondBucket();
            updateOverallProbability();
            if(ball->getColor() == BallColor::Red){
                ui->secondBucketLastMoved->setText("извлекли красный шар");
            }
            else{
                ui->secondBucketLastMoved->setText("извлекли синий шар");
            }
        }
        else{
            QMessageBox::critical(nullptr, "Ошибка", "Ошибка перемещения!");
        }
    }
    else{
        QMessageBox::critical(nullptr, "Ошибка", "Вторая корзина пуста!");
    }

}


void MainWindow::on_randomMoveButton_clicked()
{
    std::random_device random;
    std::mt19937 gen{random()};
    std::uniform_int_distribution<int> extract_select{ByRotation, TwoSecond};
    auto rand = extract_select(gen);
    switch(rand){
        case ByRotation:{
            if(firstBucket->ballsCount() > 0 && secondBucket->ballsCount() > 0){
                extractByRotation();
            }
            else if(firstBucket->ballsCount() == 0 && secondBucket->ballsCount() > 1){
                extractFromSecond();
            }
            else if(secondBucket->ballsCount() == 0 && firstBucket->ballsCount() > 1){
                exctractFromFirst();
            }
            else{
                createError();
            }

            break;
        }
        case TwoFirst:{
            if(firstBucket->ballsCount() > 1){
                exctractFromFirst();
            }
            else if(secondBucket->ballsCount() > 1){
                extractFromSecond();
            }
            else if(firstBucket->ballsCount() > 0 && secondBucket->ballsCount() > 0){
                extractByRotation();
            }
            else{
                createError();
            }
            break;
        }
        case TwoSecond:{
            if(secondBucket->ballsCount() > 1){
                extractFromSecond();
            }
            else if(firstBucket->ballsCount() > 1){
                exctractFromFirst();
            }
            else if(firstBucket->ballsCount() > 0 && secondBucket->ballsCount() > 0){
                extractByRotation();
            }
            else{
                createError();
            }
            break;
        }
    }
}

