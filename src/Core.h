//
// Created by liams on 07/09/2016.
//

#ifndef SUMMER_PROJECT_POKER_CORE_H
#define SUMMER_PROJECT_POKER_CORE_H

#include "GameLogic.h"
#include "GraphicsMain.h"

const int BUTTON_TOTAL = 7;

class Core {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event e;

    GameLogic* game;
    GTexture table;
    GButton gameButtons[BUTTON_TOTAL];
    int buttonState;

    bool quit;

    bool loadMedia();
    void handleInput(SDL_EventType);
    void input();
    void update();
    void render();

public:
    Core();

    void mainLoop();
    void exit();
};


#endif //SUMMER_PROJECT_POKER_CORE_H
