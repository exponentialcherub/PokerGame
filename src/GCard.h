//
// Created by liams on 05/09/2016.
//

#ifndef SUMMER_PROJECT_POKER_GCARD_H
#define SUMMER_PROJECT_POKER_GCARD_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "GTexture.h"

class GCard {
private:
    int rank;
    int suit;
    SDL_Rect rect;

    /*****Card Animation*******/
    int timePassed;
    int width; // value changes while card turn over is animated
    bool animating;
    bool backOfCard;
    bool widthSet; // Checks if width has been set to starting value yet
    /**************************/

public:
    GCard();
    GCard(int,int);

    void render(GTexture, SDL_Renderer* = NULL, SDL_Rect* = NULL, int = 0);

    int getRank();
    int getSuit();
    bool getAnimating();
    void setValues(int,int);
};


#endif //SUMMER_PROJECT_POKER_GCARD_H
