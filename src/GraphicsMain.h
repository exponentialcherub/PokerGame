//
// Created by liams on 04/09/2016.
//

#ifndef SUMMER_PROJECT_POKER_GRAPHICSMAIN_H
#define SUMMER_PROJECT_POKER_GRAPHICSMAIN_H

#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <iostream>
#include "GTexture.h"
#include "GCard.h"
#include "GButton.h"
#include <SDL_ttf.h>

enum Buttons{
    CHECK_BUTTON,
    CALL_BUTTON,
    FOLD_BUTTON,
    RAISE_BUTTON,
    ALLIN_BUTTON,
    TOTAL_BUTTON,
};

class GraphicsMain {
private:
    GTexture table;

    GButton gameButtons[3];

    int buttonState;

public:
    GraphicsMain();
    bool loadMedia(SDL_Renderer*);
    void render(SDL_Renderer*);
    void handleInput(SDL_EventType);
    int getButtonState();
    void resetButtonState();

    void exit();
};


#endif //SUMMER_PROJECT_POKER_GRAPHICSMAIN_H
