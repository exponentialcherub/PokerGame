//
// Created by liams on 21/09/2016.
//

#ifndef SUMMER_PROJECT_POKER_SIDEPOT_H
#define SUMMER_PROJECT_POKER_SIDEPOT_H

#include <vector>
#include <iostream>
#include "Player.h"

class SidePot {
private:
    int pot;
    std::vector<int> playerID; //players contesting for this pot

public:
    SidePot();
    void fillPot(int);
    void addPlayer(int);
    int getAmount();
    std::vector<int> getPlayerIDs();

    void distribute(std::vector<Player>* players);

    void printPot(int);
};


#endif //SUMMER_PROJECT_POKER_SIDEPOT_H
