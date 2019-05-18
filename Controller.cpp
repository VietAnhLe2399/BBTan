#include "Controller.h"

int Controller::WIDTH;
int Controller::HEIGHT;
int level = 1;
int highScoreMode1 = 0;
int highScoreMode2 = 0;
int highScore = 0;
bool nextLevel = false;
int xMouseMotion, yMouseMotion;
bool isBallLeft = false;
vector<Ball*> allBall;
vector<Brick*> allBrick;
int gameMode = 0;
bool changeBall = false;
int ballNumber = 1;
bool mouseAble = true;

TTF_Font *font_level = NULL;
TextObject level_game;
TTF_Font *font_highScore = NULL;
TextObject high_Score;
TTF_Font *font_brick = NULL;
TextObject brick_game;
BaseObject menu;
SDL_Texture *ballToChange;
BaseObject backgroundWhenPlay;
BaseObject gameover;

SDL_Renderer *Controller::renderer = nullptr;

Controller::Controller()
{
    //ctor
    //init the data
    this->window = nullptr;
    this->renderer = nullptr;
    this->end_loop = false;
    this->newGame = true;
    this->sound_ball = nullptr;
    this->sound_brick = nullptr;
    this->sound_menu = nullptr;
    this->sound_gameover = nullptr;
}

Controller::~Controller()
{
    //dtor
}

void Controller::setNewGame(bool isNewGame)
{
    this->newGame = isNewGame;
}

bool Controller::getNewGame()
{
    return this->newGame;
}

SDL_Texture *Controller::LoadTexture(const char *fileName)
{
    SDL_Texture *new_texture = NULL;
    SDL_Surface *load_surface = IMG_Load(fileName);
    if (load_surface != NULL)
    {
        new_texture = SDL_CreateTextureFromSurface(Controller::renderer, load_surface);
        SDL_FreeSurface(load_surface);
    }
    return new_texture;
}

void Controller::loadHighScore()
{
    ifstream infile;
    infile.open("highScore.txt");
    infile >> highScoreMode1 >> highScoreMode2;
    infile.close();
}

void Controller::storeHighScore(int newHighScoreMode1, int newHighScoreMode2)
{
    ofstream outfile;
    outfile.open("highScore.txt");
    outfile << newHighScoreMode1 << " " << newHighScoreMode2;
    outfile.close();
}

void Controller::initializeSDL(string program_name, const int &x, const int &y, const int &screenWidth, const int &screenHeight, const int &screenOption)
{
    WIDTH = screenWidth;
    HEIGHT = screenHeight;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        cout << "Can't Initialize the SDL Libraries" << SDL_GetError();
        end_loop = true;
        return;
    }

    window = SDL_CreateWindow(program_name.c_str(), x, y, screenWidth, screenHeight, screenOption);
    if (window == nullptr)
    {
        std::cout << "Can't create Window " << SDL_GetError();
        end_loop = true;
        return;
    }

    if (TTF_Init() == -1)
    {
        cout << "Can't Initialize TTF" << SDL_GetError();
        end_loop = true;
        return;
    }

    font_level = TTF_OpenFont("font//Freshman.ttf", 50);
    level_game.setColor(TextObject::WHITE_TEXT);
    font_brick = TTF_OpenFont("font//Freshman.ttf", 20);
    brick_game.setColor(TextObject::WHITE_TEXT);
    font_highScore = TTF_OpenFont("font//Square.ttf", 30);
    high_Score.setColor(TextObject::WHITE_TEXT);

    if (font_level == NULL || font_brick == NULL || font_highScore == NULL)
    {
        cout << "Fail to load font" << endl;
        end_loop = true;
        return;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        cout << "Fail to load audio" << endl;
        end_loop = true;
        return;
    }

    sound_ball = Mix_LoadWAV("audio//pop.wav");
    sound_brick = Mix_LoadWAV("audio//pop33.wav");
    sound_menu = Mix_LoadWAV("audio//intro1.wav");
    sound_gameover = Mix_LoadWAV("audio//kick.wav");

    if (sound_ball == nullptr || sound_brick == nullptr || sound_gameover == nullptr || sound_menu == nullptr)
    {
        end_loop = true;
        return;
    }

    renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr)
    {
        std::cout << "Can't create Renderer" << SDL_GetError();
        end_loop = true;
        return;
    }
    SDL_Delay(100);

    backgroundWhenPlay.loadImg("img/playbackground.png", renderer);

    showMenu();

    initObjects();
}

void Controller::initObjects()
{
    level = 1;

    loadHighScore();
    if (gameMode == 1)
        highScore = highScoreMode1;
    if (gameMode == 2)
        highScore = highScoreMode2;

    allBall.clear();
    // Init ball
    string tempBall = std::to_string(ballNumber);
    string link = "img/ball_" + tempBall + ".png";
    allBall.push_back(new Ball(link.c_str()));
    // Init Brick
    srand((int)time(0));
    int numberOfBrick = rand() % 6 + 1;
    vector<int> positions;
    for (int i = 0; i < 7; i++)
    {
        positions.push_back(i + 1);
    }
    random_shuffle(positions.begin(), positions.end());
    allBrick.clear();
    while (numberOfBrick > 0)
    {
        int position = positions[numberOfBrick - 1];
        Brick *brick = new Brick(position, level);
        allBrick.push_back(brick);
        numberOfBrick--;
    }
}

void Controller::update()
{
    // check collide of Ball
    for (auto ball : allBall)
    {
        ball->update();
        for (int j = (int)allBrick.size() - 1; j >= 0; j--)
        {
            bool isCollided = ball->collideWithBrick(allBrick[j]->getX(), allBrick[j]->getY(), allBrick[j]->getEdge(), true);
            if (allBrick[j]->collide(isCollided))
            {
                Mix_PlayChannel(-1, sound_brick, 0);
                allBrick.erase(allBrick.begin() + j);
                break;
            }
        }
    }

    for (auto ball : allBall)
    {
        if (ball->getY() + ball->getRadius() < BOTTOM)
        {
            isBallLeft = true;
            break;
        }
        else
        {
            isBallLeft = false;
        }
    }

    // update brick and ball
    if (!isBallLeft && nextLevel)
    {
        mouseAble = true;
        string ballToAdd = std::to_string(ballNumber);
        string link = "img/ball_" + ballToAdd + ".png";
        if (gameMode == 2)
        {
            allBall.push_back(new Ball(link.c_str()));
        }
        level++;
        for (auto brick : allBrick)
        {
            brick->update();
        }
        srand((int)time(0));
        vector<int> positions;
        for (int i = 0; i < 7; i++)
        {
            positions.push_back(i + 1);
        }
        random_shuffle(positions.begin(), positions.end());
        int numberOfBrick = rand() % 6 + 1;
        while (numberOfBrick > 0)
        {
            int position = positions[numberOfBrick - 1];
            if (gameMode == 1)
            {
                Brick *brick = new Brick(position, int(1 + level / 5));
                allBrick.push_back(brick);
                numberOfBrick--;
            }
            else if (gameMode == 2)
            {
                Brick *brick = new Brick(position, level);
                allBrick.push_back(brick);
                numberOfBrick--;
            }
        }
        nextLevel = false;
    }

    for (auto brick : allBrick)
    {
        if ((brick->getY() + brick->getEdge()) >= (BOTTOM - 30))
        {
            setNewGame(true);
            break;
        }
    }
}

int Controller::checkMode(const int &x, const int &y)
{
    if (x >= 50 && x <= 215 && y >= 520 && y <= 610)
    {
        return 1;
    }
    if (x >= 240 && x <= 400 && y >= 520 && y <= 610)
    {
        return 2;
    }
    if (x >= 50 && x <= 215 && y >= 625 && y <= 715)
    {
        return 3;
    }
    if (x >= 240 && x <= 400 && y >= 625 && y <= 715)
    {
        return 4;
    }
    return 0;
}

void Controller::showMenu()
{
    int xm = 0;
    int ym = 0;
    SDL_Event m_event;
    while (true)
    {
        SDL_RenderClear(renderer);
        menu.loadImg("img/menu.jpg", renderer);
        menu.Render(renderer, NULL);
        string tempBall = std::to_string(ballNumber);
        string link = "img/ball_" + tempBall + ".png";
        ballToChange = LoadTexture(link.c_str());
        SDL_Rect renderquad = {108, 645, 55, 55};
        SDL_RenderCopy(renderer, ballToChange, NULL, &renderquad);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
            {
                end_loop = true;
                return;
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                SDL_GetMouseState(&xm, &ym);
                int mode = checkMode(xm, ym);
                if (mode == 1)
                {
                    gameMode = 1;
                    Mix_PlayChannel(-1, sound_menu, 0);
                    return;
                }
                if (mode == 2)
                {
                    gameMode = 2;
                    Mix_PlayChannel(-1, sound_menu, 0);
                    return;
                }
                if (mode == 3)
                {
                    ballNumber++;
                    if (ballNumber > 22)
                        ballNumber = 1;
                    break;
                }
                if(mode == 4)
                {
                    close();
                }
            }
            break;
            default:
                break;
            }
        }

    }
    menu.Free();
    SDL_RenderClear(renderer);
    return;
}

void Controller::gameOverHandle()
{
    if (highScore < level)
        {
            highScore = level - 1;
            if (gameMode == 1)
                storeHighScore(highScore, highScoreMode2);
            if (gameMode == 2)
                storeHighScore(highScoreMode1, highScore);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        gameover.loadImg("img/gameover.png", renderer);
        gameover.Render(renderer, 0);
        // level and high score
        Uint32 level_g = level - 1;
        string str_level = to_string(level_g);
        level_game.setText(str_level);
        level_game.loadFromRenderText(font_level, renderer);
        level_game.renderText(renderer, 205, 245);
        Uint32 high_Score_g = highScore;
        string str_highScore = to_string(high_Score_g);
        high_Score.setText(str_highScore);
        high_Score.loadFromRenderText(font_level, renderer);
        high_Score.renderText(renderer, 195, 355);

        SDL_RenderPresent(renderer);
        Mix_PlayChannel(-1, sound_gameover, 0);
        SDL_Delay(2000);
        gameMode = 0;
        showMenu();
}

void Controller::render()
{
    if (getNewGame())
    {
        gameOverHandle();
    }

    if (!end_loop)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //render Background in game
        backgroundWhenPlay.Render(renderer, NULL);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Render high Score
        Uint32 high_Score_g = highScore;
        string str_highScore = "TOP " + to_string(high_Score_g);
        high_Score.setText(str_highScore);
        high_Score.loadFromRenderText(font_highScore, renderer);
        high_Score.renderText(renderer, Controller::getWidth() - 110, TOP / 10);

        // Render current Score
        Uint32 level_g = level;
        string str_level = to_string(level_g);
        level_game.setText(str_level);
        level_game.loadFromRenderText(font_level, renderer);
        level_game.renderText(renderer, Controller::getWidth() / 2 - 5, TOP / 10);

        // Draw ball direction
        if (!nextLevel && gameMode == 1)
            Draw::drawLine(renderer, static_cast<int>(allBall.at(0)->getX()),
                          static_cast<int>(allBall.at(0)->getY()),
                          static_cast<int>(xMouseMotion),
                          static_cast<int>(yMouseMotion));

        for (auto ball : allBall)
        {
            ball->render();
        }
        for (auto brick : allBrick)
        {
            brick->render(renderer);
            brick_game.Free();
            Uint32 brick_g = brick->gethardlevel();
            string str_hardlevel = to_string(brick_g);
            brick_game.setText(str_hardlevel);
            brick_game.loadFromRenderText(font_brick, renderer);
            brick_game.renderText(renderer, brick->getX() + 23.5, brick->getY() + 20);
        }
        SDL_RenderPresent(renderer);
    }
}

void Controller::handleEvent()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            end_loop = true;
            break;
        case SDL_MOUSEMOTION:
        {
            if (nextLevel == false)
                SDL_GetMouseState(&xMouseMotion, &yMouseMotion);
        }
        break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                isBallLeft = true;
                nextLevel = true;
                int xMouseDown, yMouseDown;
                SDL_GetMouseState(&xMouseDown, &yMouseDown);
                if (0 < xMouseDown && xMouseDown < 70 && 0 < yMouseDown && yMouseDown < 70)
                {
                    setNewGame(true);
                    break;
                }
                if(mouseAble){
                    mouseAble = false;
                    float xToCal = 0;
                    float yToCal = 0;
                    // Game Mode 1
                    if (gameMode == 1)
                    {
                        xToCal = abs(allBall.at(0)->getX() - xMouseDown);
                        yToCal = abs(allBall.at(0)->getY() - yMouseDown);
                        float ball0Angle = 0;
                        if (xMouseDown > allBall.at(0)->getX())
                        {
                            ball0Angle = atan(yToCal / xToCal) * 180 / PI;
                            allBall.at(0)->setAngle(ball0Angle);
                        }
                        if (xMouseDown < allBall.at(0)->getX())
                        {
                            ball0Angle = 180 - atan(yToCal / xToCal) * 180 / PI;
                            allBall.at(0)->setAngle(ball0Angle);
                        }
                        for (int i = 1; i < (int)allBall.size(); i++)
                        {
                            allBall.at(i)->setAngle(ball0Angle);
                            allBall.at(i)->setX(allBall.at(0)->getX());
                            allBall.at(i)->setY(allBall.at(0)->getY());
                        }
                    }
                    // Game Mode 2
                    if (gameMode == 2)
                    {
                        for (int i = 0; i < allBall.size(); i++)
                        {
                            xToCal = abs(allBall.at(i)->getX() - xMouseDown);
                            yToCal = abs(allBall.at(i)->getY() - yMouseDown);
                            if (xMouseDown > allBall.at(i)->getX())
                                allBall.at(i)->setAngle(atan(yToCal / xToCal) * 180 / PI);
                            if (xMouseDown < allBall.at(i)->getX())
                                allBall.at(i)->setAngle(180 - atan(yToCal / xToCal) * 180 / PI);
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    }
}

void Controller::close()
{
    SDL_DestroyWindow(this->window);
    this->window = nullptr;
    SDL_DestroyRenderer(this->renderer);
    this->renderer = nullptr;
    SDL_Quit();
}

SDL_Window *Controller::getWindow() const
{
    return this->window;
}

SDL_Renderer *Controller::getRenderer() const
{
    return this->renderer;
}

bool Controller::isEndLoop() const
{
    return this->end_loop;
}

void Controller::setEndLoop(const bool &end_loop)
{
    this->end_loop = end_loop;
}

int Controller::getWidth()
{
    return WIDTH;
}

int Controller::getHeight()
{
    return HEIGHT;
}
