#include "Ball.h"

Ball::Ball()
{
    this->radius = 10;
    this->x = Controller::getWidth() / 2;
    this->y = BOTTOM - radius;
    this->angle = 10;
    this->x_velocity = 0;
    this->y_velocity = 0;
    p_object = Controller::LoadTexture("ball_1.png");
}

Ball::Ball(const char *fileName)
{
    this->radius = 10;
    this->x = Controller::getWidth() / 2;
    this->y = BOTTOM - radius;
    this->angle = 10;
    this->x_velocity = 0;
    this->y_velocity = 0;
    p_object = Controller::LoadTexture(fileName);
}

Ball::~Ball()
{

}

void Ball::setX(float newX)
{
    this->x = newX;
}

void Ball::setY(float newY)
{
    this->y = newY;
}

float Ball::getX()
{
    return this->x;
}

float Ball::getY()
{
    return this->y;
}

void Ball::setXVelocity(int x_v)
{
    this->x_velocity = x_v;
}

void Ball::setYVelocity(int y_v)
{
    this->y_velocity = y_v;
}

void Ball::setAngle(int newAngle)
{
    angle = newAngle;
    if (newAngle <= minAngle)
        angle = minAngle;
    if (newAngle >= maxAngle)
        angle = maxAngle;
    float rad = (angle / 180) * PI;
    x_velocity = cos(rad) * 10;
    y_velocity = sin(rad) * 10;
}

float Ball::getAngle()
{
    return this->angle;
}

float Ball::getRadius()
{
    return this->radius;
}

void Ball::render()
{
    SDL_Rect renderquad = {getX() - getRadius(), getY() - getRadius(), getRadius() * 2, getRadius() * 2};
    SDL_RenderCopy(Controller::renderer, p_object, NULL, &renderquad);
}

bool Ball::update()
{
    x += x_velocity;
    y -= y_velocity;
    return collideWithWall();
}

bool Ball::collideWithBrick(float brickX, float brickY, float brickEdge, bool hasDecrease)
{
    float cX, cY;

    if (x < brickX)
    {
        cX = brickX;
    }
    else if (x > brickX + brickEdge)
    {
        cX = brickX + brickEdge;
    }
    else
    {
        cX = x;
    }

    if (y < brickY)
    {
        cY = brickY;
    }
    else if (y > brickY + brickEdge)
    {
        cY = brickY + brickEdge;
    }
    else
    {
        cY = y;
    }
    if ((x > brickX) && (x < brickX) && (y > brickY) && (y < brickY))
        return false;
    if (distanceSquared(x, y, cX, cY) < radius * radius)
    {
        if (x < cX && y < cY)
        {
            x_velocity = -abs(x_velocity);
            y_velocity = -abs(y_velocity);
            return true;
        }
        if (x < cX && y > cY)
        {
            x_velocity = abs(x_velocity);
            y_velocity = -abs(y_velocity);
            return true;
        }
        if (x > cX && y > cY)
        {
            x_velocity = abs(x_velocity);
            y_velocity = abs(y_velocity);
            return true;
        }
        if (x > cX && y > cY)
        {
            x_velocity = -abs(x_velocity);
            y_velocity = abs(y_velocity);
            return true;
        }
        if (x < cX)
        {
            x_velocity = -x_velocity;
            return true;
        }
        if (x > cX)
        {
            x_velocity = -x_velocity;
            return true;
        }
        if (y < cY)
        {
            y_velocity = -y_velocity;
            return true;
        }
        if (y > cY)
        {

            y_velocity = -y_velocity;
            return true;
        }
    }
    return false;
}

bool Ball::collideWithWall()
{
    bool temp = false;
    if (x <= getRadius())
    {
        x = getRadius();
        x_velocity = -x_velocity;
        temp = true;
    }
    if (x >= Controller::getWidth() - getRadius())
    {
        x = Controller::getWidth() - getRadius();
        x_velocity = -x_velocity;
        temp = true;
    }
    if (y <= TOP + getRadius())
    {
        y = TOP + getRadius();
        y_velocity = -y_velocity;
        temp = true;
    }
    if (y >= BOTTOM - getRadius())
    {
        y = BOTTOM - getRadius();
        x_velocity = 0;
        y_velocity = 0;
        temp = true;
    }
    return temp;
}

double Ball::distanceSquared(int x1, int y1, int x2, int y2)
{
    float deltaX = x2 - x1;
    float deltaY = y2 - y1;
    return deltaX * deltaX + deltaY * deltaY;
}
