#include "TextObject.h"

TextObject ::TextObject()
{
    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255;
    texture = NULL;
}

TextObject ::~TextObject()
{

}

int TextObject::getWidth() const
{
    return width;
}
int TextObject::getHeight() const
{
    return height;
}

void TextObject::setText(const string &text)
{
    strVal = text;
}

string TextObject::getText() const
{
    return strVal;
}

bool TextObject::loadFromRenderText(TTF_Font *font, SDL_Renderer *des)
{
    Free();
    SDL_Surface *textSurface;
    textSurface = TTF_RenderText_Solid(font, strVal.c_str(), textColor);
    if (textSurface)
    {
        Free();
        texture = SDL_CreateTextureFromSurface(des, textSurface);
        width = textSurface->w;
        height = textSurface->h;

        SDL_FreeSurface(textSurface);
    }

    return texture != NULL;
}

void TextObject::Free()
{
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void TextObject::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    textColor.r = red;
    textColor.g = green;
    textColor.b = blue;
}

void TextObject::setColor(int type)
{
    if (type == RED_TEXT)
    {
        SDL_Color color = {255, 0, 0};
        textColor = color;
    }
    else if (type == WHITE_TEXT)
    {
        SDL_Color color = {255, 255, 255};
        textColor = color;
    }
    else if (type == BLACK_TEXT)
    {
        SDL_Color color = {0, 0, 0};
        textColor = color;
    }
}

void TextObject::renderText(SDL_Renderer *des, int xp, int yp, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_Rect renderquad = {xp, yp, width, height};
    if (clip != NULL)
    {
        renderquad.w = clip->w;
        renderquad.h = clip->h;
    }

    SDL_RenderCopyEx(des, texture, clip, &renderquad, angle, center, flip);
}
