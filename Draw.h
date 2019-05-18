#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#pragma once
#include <SDL.h>

class Draw
{
public:
    Draw();
    virtual ~Draw();
    static void drawLine(SDL_Renderer *, const int &x1, const int &y1, const int &x2, const int &y2);
    static void drawSquare(SDL_Renderer *, const int &x, const int &y, const int &width, const int &height);

protected:
private:
};

#endif // DRAW_H_INCLUDED
