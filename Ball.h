#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "Controller.h"
#include <SDL.h>
#include <cmath>
#include "Draw.h"
#include <vector>
#include "BaseObject.h"
#include "Brick.h"

#define PI 3.14159265

const int minAngle = 15;
const int maxAngle = 165;

class Ball : public BaseObject
{
public:
    Ball();
    Ball(const char *);
    virtual ~Ball();

    void render();
    bool update();
    void setX(float);
    void setY(float);
    float getX();
    float getY();
    float getRadius();
    void setAngle(int);
    float getAngle();
    bool collideWithWall();
    bool collideWithBrick(float, float, float, bool);
    double distanceSquared(int, int, int, int);
    void setXVelocity(int);
    void setYVelocity(int);

protected:
private:
    float x, y, radius;
    float angle;
    float x_velocity, y_velocity;
};

#endif // BALL_H_INCLUDED
