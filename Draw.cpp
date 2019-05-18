#include "Draw.h"

Draw::Draw()
{
    //ctor
}

Draw::~Draw()
{
    //dtor
}

void Draw::drawLine(SDL_Renderer *renderer, const int &x1, const int &y1, const int &x2, const int &y2)
{
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Draw::drawSquare(SDL_Renderer *renderer, const int &x, const int &y, const int &width, const int &height)
{
    SDL_RenderDrawLine(renderer, x, y, x + width, y);
    SDL_RenderDrawLine(renderer, x, y + 1, x + width, y + 1);
    SDL_RenderDrawLine(renderer, x, y + 2, x + width, y + 2);
    SDL_RenderDrawLine(renderer, x, y, x, y + height);
    SDL_RenderDrawLine(renderer, x + 1, y, x + 1, y + height);
    SDL_RenderDrawLine(renderer, x + 2, y, x + 2, y + height);
    SDL_RenderDrawLine(renderer, x, y + height, x + width, y + height);
    SDL_RenderDrawLine(renderer, x, y + height - 1, x + width, y + height - 1);
    SDL_RenderDrawLine(renderer, x, y + height - 2, x + width, y + height - 2);
    SDL_RenderDrawLine(renderer, x + width, y, x + width, y + height);
    SDL_RenderDrawLine(renderer, x + width - 1, y, x + width - 1, y + height);
    SDL_RenderDrawLine(renderer, x + width - 2, y, x + width - 2, y + height);
}
