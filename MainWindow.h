#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Bucket;

/*! Выбор варианта излвечения из корзины
 */
enum Extract{ ByRotation = 0, TwoFirst = 1, TwoSecond = 2};

/*! Класс рабочего окна программы.
 *  В параметрах передаеются количество шаров для первой и второй корзины
 *  Цвета назначаются случайным образом
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int fBucket, int sBucket, QWidget *parent = nullptr);
    ~MainWindow();
    /*! Обновления статистики для первой корзины
     */
    void updateFirstBucket();
    /*! Обновление статистики для второй корзины
     */
    void updateSecondBucket();
    /*! Обновления вероятностей для извлечения двух шаров
     */
    void updateOverallProbability();
    /*! Извлечение двух шаров из первой корзины
     */
    void exctractFromFirst();
    /*! Извлечение двух шаров из второй корзины
     */
    void extractFromSecond();
    /*! Извлечение по одному шару из каждой корзины
     */
    void extractByRotation();
    /*! Отоброжения окна ошибки
     *  При отсутствии достаточного количества шаров для извлечения
     */
    void createError();
    /*! Вероятность извлечь 2 синих шара
     */
    double getTwoBlueBallProbability();
    /*! Вероятность извлечь 2 красных шара
     */
    double getTwoRedBallProbability();
    /*! Вероятность извлечь 1 красный и 1 синий шар
     */
    double getOvervallProbability();
private slots:
    /*! Кнопка перемещения шара из первой во вторую корзину
     */
    void on_moveBalltoSecondBucketButton_clicked();
    /*! Кнопка перемещения шара из второй в первую корзину
     */
    void on_moveBalltoFirstBucketButton_clicked();
    /*! Кнопка извлечения двух случайных шаров
     */
    void on_randomMoveButton_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<Bucket> firstBucket;
    std::shared_ptr<Bucket> secondBucket;
};
#endif // MAINWINDOW_H
