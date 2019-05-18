#include "Brick.h"

Brick::Brick(int position, int hardLevel)
{
    this->edge = 60;
    this->y = TOP + edge + distance;
    this->sound = nullptr;

    switch (position)
    {
    case 1:
        this->x = beginDistance;
        break;
    case 2:
        this->x = edge + beginDistance + distance;
        break;
    case 3:
        this->x = edge * 2 + beginDistance + distance * 2;
        break;
    case 4:
        this->x = edge * 3 + beginDistance + distance * 3;
        break;
    case 5:
        this->x = edge * 4 + beginDistance + distance * 4;
        break;
    case 6:
        this->x = edge * 5 + beginDistance + distance * 5;
        break;
    case 7:
        this->x = edge * 6 + beginDistance + distance * 6;
        break;
    }
    this->hardLevel = hardLevel;
}

Brick::~Brick()
{

}

float Brick::getX()
{
    return this->x;
}

float Brick::getY()
{
    return this->y;
}

float Brick::getEdge()
{
    return this->edge;
}

void Brick::render(SDL_Renderer *renderer)
{
    Draw::drawSquare(renderer, static_cast<int>(x), static_cast<int>(y), edge, edge);
}

void Brick::update()
{
    y = y + edge + 2;
    if (y + edge >= BOTTOM - 10)
    {
        cout << "Game over" << endl;
    }
}

bool Brick::collide(bool isCollided)
{
    if (isCollided)
    {
        hardLevel--;
        sound = Mix_LoadWAV("audio//pop11.wav");
        Mix_PlayChannel(-1, sound, 0);
    }
    if (hardLevel == 0)
        return true;
    return false;
}

int Brick::gethardlevel()
{
    return this->hardLevel;
}
