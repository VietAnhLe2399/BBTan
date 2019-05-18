#ifndef TEXTOBJECT_H_INCLUDED
#define TEXTOBJECT_H_INCLUDED

#include "BaseObject.h"

class TextObject : public BaseObject
{
public:
    TextObject();
    ~TextObject();

    enum textColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
    };

    bool loadFromRenderText(TTF_Font *font, SDL_Renderer *des);
    void Free();

    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setColor(int type);

    void renderText(SDL_Renderer *des, int xp, int yp,
                    SDL_Rect *clip = NULL, double angle = 0.0,
                    SDL_Point *center = NULL,
                    SDL_RendererFlip flip = SDL_FLIP_NONE);

    int getWidth() const;
    int getHeight() const;

    void setText(const string &);
    string getText() const;

private:
    string strVal;
    SDL_Color textColor;
    SDL_Texture *texture;
    int width;
    int height;
};

#endif // TEXTOBJECT_H_INCLUDED
