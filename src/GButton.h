//
// Created by liams on 01/09/2016.
//


#ifndef SUMMER_PROJECT_POKER_GBUTTON_H
#define SUMMER_PROJECT_POKER_GBUTTON_H

#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "GTexture.h"

enum ButtonSprite{
    SPRITE_MOUSE_OUT,
    SPRITE_MOUSE_OVER,
    SPRITE_MOUSE_DOWN,
    SPRITE_TOTAL,
};

class GButton {
private:
    SDL_Point position;
    SDL_Rect spriteClips[SPRITE_TOTAL];
    GTexture spriteSheet;
    ButtonSprite currentSprite;
    bool buttonPressed;
    bool buttonHeld;
    bool active;

public:
    GButton();

    bool loadButton(std::string, SDL_Renderer* = NULL);
    void setPosition(int,int);
    //void setSize(int, int);

    void handleEvent(SDL_EventType);
    void render(SDL_Renderer*);
    void render(SDL_Renderer*, int, int);
    bool isButtonPressed();
    void resetButtonPressed();
    bool buttonActive();
    void setActive(bool);
    void singleSprite();

    void free();
};


#endif //SUMMER_PROJECT_POKER_GBUTTON_H
