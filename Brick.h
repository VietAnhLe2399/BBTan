#ifndef BRICK_H_INCLUDED
#define BRICK_H_INCLUDED

#include <SDL.h>
#include <cmath>
#include "Controller.h"
#include "Draw.h"
#include "BaseObject.h"
#include <iostream>

#define distance 2
#define beginDistance 10

class Brick : public BaseObject
{
public:
    Brick(int, int);
    virtual ~Brick();
    void render(SDL_Renderer*);
    void update();
    bool collide(bool);
    float getX();
    float getY();
    float getEdge();
    int gethardlevel();
protected:

private:
    float x,y,edge;
    int hardLevel;
    Mix_Chunk* sound;
};

#endif // BRICK_H_INCLUDED
