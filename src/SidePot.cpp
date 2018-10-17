//
// Created by liams on 21/09/2016.
//

#include "SidePot.h"

SidePot::SidePot() {
    pot = 0;
}

void SidePot::fillPot(int amount) {
    pot += amount;
}

void SidePot::addPlayer(int id) {
    playerID.push_back(id);
}

int SidePot::getAmount() {
    return pot;
}

std::vector<int> SidePot::getPlayerIDs(){
    return playerID;
}

void SidePot::distribute(std::vector<Player> *players) {
    int highest = -1;
    for(int i=0;i<playerID.size();i++){
        if((highest == -1 || (*players)[playerID[i]].getHandStrength()>(*players)[highest].getHandStrength())) {
            if((*players)[i].getInRound())
                highest = i;
        }
    }
    (*players)[highest].win(pot);
}

void SidePot::printPot(int index){
    std::cout << "SIDE POT " << index << ": " << pot << std::endl;
}