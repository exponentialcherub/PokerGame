//
// Created by liams on 20/09/2016.
//

#ifndef SUMMER_PROJECT_POKER_POT_H
#define SUMMER_PROJECT_POKER_POT_H

//#include <vector>
#include "SidePot.h"
//#include "Player.h"
#include <iostream>
#include "GText.h"


class Pot {
private:
    int mainPot; //constested by everyone still in game
    std::vector<SidePot> sidePots; //map->playerid,
    GText* font;
public:
    Pot();
    void fillPot(std::vector< std::vector<int> >);
    void fillPot(std::vector<Player>* players);
    void distribute(std::vector<Player>* players);
    void emptyPot();

    void setFont(GText* font);

    void render(SDL_Renderer* renderer = NULL);
    void printPot();
};


#endif //SUMMER_PROJECT_POKER_POT_H
