#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include <iostream>
#include <SDL.h>

#include <algorithm>
#include <vector>
#include <time.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "Ball.h"
#include "Brick.h"
#include "BaseObject.h"
#include "textobject.h"

class Controller
{
public:
    Controller();
    virtual ~Controller();
    void initializeSDL(std::string program_name, const int &x, const int &y, const int &width, const int &height, const int &screen_option);
    void render();
    void update();
    void handleEvent();
    void close();
    SDL_Window *getWindow() const;
    SDL_Renderer *getRenderer() const;
    bool isEndLoop() const;
    void setEndLoop(const bool &);
    void loadHighScore();
    void storeHighScore(int, int);

    void initObjects();
    void setNewGame(bool);
    bool getNewGame();
    void gameOverHandle();
    static int getWidth();
    static int getHeight();

    void showMenu();

    int checkMode(const int &x, const int &y);
    static SDL_Renderer *renderer;
    static SDL_Texture *LoadTexture(const char *fileName);

protected:
    static int WIDTH;
    static int HEIGHT;

private:
    SDL_Window *window;
    SDL_Event event;
    Mix_Chunk *sound_menu;
    Mix_Chunk *sound_ball;
    Mix_Chunk *sound_brick;
    Mix_Chunk *sound_gameover;
    bool end_loop;
    bool newGame;
};

#endif // CONTROLLER_H_INCLUDED
