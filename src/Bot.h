//
// Created by liams on 22/08/2016.
//

#ifndef SUMMER_PROJECT_POKER_BOT_H
#define SUMMER_PROJECT_POKER_BOT_H

#include "Player.h"

class Bot: public Player {
public:
    Bot();
    int getAction();
};


#endif //SUMMER_PROJECT_POKER_BOT_H
