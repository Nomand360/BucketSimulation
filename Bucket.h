#ifndef BUCKET_H
#define BUCKET_H
#include <list>
#include <memory>
#include <random>
#include "Ball.h"

/*! Класс моделирующий корзину с шарами
 */
class Bucket
{
public:
    explicit Bucket(int ballcounts);
    /*! Получить случайный шар из корзины
    */
    std::shared_ptr<Ball> takeBallFromBucket();
    /*! Удалить случайный шар из корзины
     */
    void extractBall();
    std::size_t ballsCount() const{
        return balls.size();
    }
    std::size_t getRedBallsCount () const {
        return redBallsCount;
    }
    std::size_t getBlueBallsCount () const {
        return blueBallsCount;
    }
    /*! Положить полученый шар в корзину
    */
    void putBallToBucket(std::shared_ptr<Ball> &ball);
    /*! Увеличение счетчика синих/красных шаров
    */
    void ballIncrement(const std::shared_ptr<Ball> &ball);
    /*! Уменьшение счетчика синих/красных шаров
    */
    void ballDecrement(const std::shared_ptr<Ball> &ball);
    /*! Вероятность вынуть синий шар
    */
    double getBlueBallProbability() const;
    /*! Вероятность вынуть красный шар
    */
    double getRedBallProbability() const;
private:
    /*! Счетчик красных шаров
    */
    int redBallsCount;
    /*! Счетчик синих шаров
    */
    int blueBallsCount;
    std::list<std::shared_ptr<Ball>> balls;
    std::random_device random;
    std::mt19937 gen{random()};
};

#endif // BUCKET_H
