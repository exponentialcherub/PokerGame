//
// Created by liams on 05/09/2016.
//

#include "GCard.h"

const int CARD_WIDTH = 81;
const int CARD_HEIGHT = 117.4;

const SDL_Rect rBackOfCard = {0, 4*CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT};

GCard::GCard() {
    rank = -1;
    suit = -1;
    rect.w = 0;
    rect.h = 0;
    rect.x = 0;
    rect.y = 0;
    timePassed = SDL_GetTicks();
    width = 0;
    animating = true;
    backOfCard = true;
    widthSet = false;
}

GCard::GCard(int r, int s) {
    rank = r;
    suit = s;
    rect.w = CARD_WIDTH;
    rect.h = CARD_HEIGHT;
    rect.x = rank*CARD_WIDTH;
    rect.y = suit*CARD_HEIGHT;
    timePassed = SDL_GetTicks();
    width = 0;
    animating = true;
    backOfCard = true;
    widthSet = false;
}

void GCard::render(GTexture spriteSheet, SDL_Renderer* renderer, SDL_Rect* rSpace, int angle) {
    if(!widthSet) {
        width = rSpace->w;
        widthSet = true;
    }
    if(animating) {
        int _time = SDL_GetTicks();
        int difference = _time - timePassed;
        if(backOfCard) {
            if (width <=0) {
                backOfCard = false;
                width = 0;
                timePassed = SDL_GetTicks();
            }
            if (difference > 10) {
                width -= ((rSpace->w) / 30);
                timePassed = SDL_GetTicks();
            }

            SDL_Rect backRect = rBackOfCard;
            int x = rSpace->x + rSpace->w/2 - width/2;
            SDL_Rect nSpace = {x, rSpace->y, width, rSpace->h};
            spriteSheet.render(&nSpace, &backRect, renderer, angle);
            return;
        }
        else{
            if (width >= rSpace->w) {
                animating = false;
            }
            if (difference > 10) {
                width += (rSpace->w) / 30;
                timePassed = SDL_GetTicks();
            }

            int x = rSpace->x + rSpace->w/2 - width/2;
            SDL_Rect nSpace = {x, rSpace->y, width, rSpace->h};
            spriteSheet.render(&nSpace, &rect, renderer, angle);
            return;
        }
    }

    spriteSheet.render(rSpace, &rect, renderer, angle);
}

int GCard::getRank() {
    return rank;
}

int GCard::getSuit() {
    return suit;
}

bool GCard::getAnimating() {
    return animating;
}

void GCard::setValues(int s, int r) {
    timePassed = SDL_GetTicks();
    suit = s;
    rank = r;
    rect.w = CARD_WIDTH;
    rect.h = CARD_HEIGHT;
    rect.x = (rank-2)*CARD_WIDTH;
    rect.y = (suit-1)*CARD_HEIGHT;
}