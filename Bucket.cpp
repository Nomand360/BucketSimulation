#include "Bucket.h"

Bucket::Bucket(int ballcounts) : redBallsCount(0), blueBallsCount(0)
{
    std::uniform_int_distribution<int> ball_color{Red, Blue};
    for(int i = 0; i < ballcounts; i++){
        auto ball = std::make_shared<Ball>(ball_color(gen));
        ballIncrement(ball);
        balls.emplace_back(ball);
    }
}

std::shared_ptr<Ball> Bucket::takeBallFromBucket()
{
    if(balls.empty()){
        return nullptr;
    }
    std::shared_ptr<Ball> ball;
    if(balls.size() > 1){
        std::uniform_int_distribution<int> elem{0, static_cast<int>(balls.size() - 1)};
        auto i = elem(gen);
        auto it = balls.begin();
        std::advance(it, i);
        ball = *it;
        balls.erase(it);
    }else{
        auto it = balls.begin();
        ball = *it;
        balls.erase(it);
    }
    ballDecrement(ball);
    return ball;
}

void Bucket::extractBall()
{
    std::uniform_int_distribution<int> elem{0, static_cast<int>(balls.size() - 1)};
    auto i = elem(gen);
    auto it = balls.begin();  
    std::advance(it, i);
    auto ball = *it;
    ballDecrement(ball);
    balls.erase(it);
}

void Bucket::putBallToBucket(std::shared_ptr<Ball> &ball)
{
    ballIncrement(ball);
    balls.emplace_back(ball);
}

void Bucket::ballIncrement(const std::shared_ptr<Ball> &ball)
{
    if(ball->getColor() == Red){
        redBallsCount++;
    }
    else{
        blueBallsCount++;
    }
}

void Bucket::ballDecrement(const std::shared_ptr<Ball> &ball)
{
    if(ball->getColor() == Red){
        redBallsCount--;
    }
    else{
        blueBallsCount--;
    }
}

double Bucket::getBlueBallProbability() const
{
    return (double)blueBallsCount / (double)balls.size() * 100.f;
}

double Bucket::getRedBallProbability() const
{
    return (double)redBallsCount / (double)balls.size() * 100.f;
}
