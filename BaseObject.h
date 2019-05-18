#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <windows.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cstdio>
#include <iostream>

#define TOP 148
#define BOTTOM 724

using namespace std;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int &, const int &);
    SDL_Rect GetRect() const;
    SDL_Texture *GetObject() const;

    void loadImg(string path, SDL_Renderer *screen);
    void Render(SDL_Renderer *des, const SDL_Rect *clip = NULL);
    void Free();

protected:
    SDL_Texture *p_object;
    SDL_Rect rect;
};

#endif // BASEOBJECT_H_INCLUDED
