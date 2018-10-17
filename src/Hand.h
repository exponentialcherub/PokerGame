//
// Created by liams on 08/09/2016.
//

#ifndef SUMMER_PROJECT_POKER_HAND_H
#define SUMMER_PROJECT_POKER_HAND_H

#include <iostream>
#include "GCard.h"


class Hand {
private:
    GCard cards[7];
    int handStrength;


    void compareHands(Hand);
public:
    Hand(GCard[5], GCard[2]);
    void evaluate();
    int getHandStrength();
};


#endif //SUMMER_PROJECT_POKER_HAND_H
