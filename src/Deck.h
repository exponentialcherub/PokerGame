//
// Created by liams on 21/08/2016.
//

#ifndef SUMMER_PROJECT_POKER_DECK_H
#define SUMMER_PROJECT_POKER_DECK_H

#include "Card.h"
#include "GCard.h"
#include <cstdlib>

class Deck {
public:
    Deck();
    void shuffle(); //set top to 0 in this
    GCard hitMe();
private:
    GCard deck[52]; //0-12 spades   13-25 hearts   26-38 clubs  39-51 diamonds
    int top;
};


#endif //SUMMER_PROJECT_POKER_DECK_H
