#ifndef BALL_H
#define BALL_H

/*! Цвет шара
 */
enum BallColor{Red = 0, Blue = 1};

/*! Класс моделирующий шар
 */
class Ball
{
public:
    explicit Ball(int c){
        color = (BallColor)c;
    }
    /*! Получить цвет шара
    */
    BallColor getColor() const{
        return color;
    }
private:
    BallColor color;
};

#endif // BALL_H
