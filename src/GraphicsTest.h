//
// Created by liams on 26/08/2016.
//

#ifndef SUMMER_PROJECT_POKER_GRAPHICSTEST_H
#define SUMMER_PROJECT_POKER_GRAPHICSTEST_H

#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <iostream>
#include "GTexture.h"
#include "GButton.h"


class GraphicsTest {
public:
    enum KeyPressSurfaces
    {
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_TOTAL
    };
    GraphicsTest();
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Surface* screenSurface;
    SDL_Surface* gCurrentSurface;
    SDL_Texture* gTexture;
    SDL_Texture* table;
    SDL_Texture* cardSpriteSheet;
    SDL_Texture* buttonSpriteSheet;

    SDL_Rect cards[52];
    SDL_Rect cardPositions[5];
    SDL_Rect handPosition[2];
    //SDL_Rect buttonSpriteClips[SPRITE_TOTAL];

    GButton aButton;


    bool init();
    bool loadMedia();
    void stretchToScreen(SDL_Surface*);
    void loop();
    SDL_Surface* loadSurface(std::string path);
    bool loadTexture(std::string path);

    void exit();
};





#endif //SUMMER_PROJECT_POKER_GRAPHICSTEST_H
