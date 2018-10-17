//
// Created by liams on 20/09/2016.
//

#include "Pot.h"

Pot::Pot() {
    mainPot = 0;
}

/*
 * Populates main pot and then creates a side pots if the pot is split. Each pot has player ids attached to them so it
 * knows which players are contesting each pot.
 */
void Pot::fillPot(std::vector< std::vector<int> > contribution) {
    int smallestBet = contribution[0][1];
    for (int i = 0; i < contribution.size(); i++) {
        if (contribution[i][1] < smallestBet)
            smallestBet = contribution[i][1];
    }
    for (int i = 0; i < contribution.size(); i++)
        mainPot += smallestBet;


    for (int i = 0; i < contribution.size(); i++) {
        contribution[i][1] -= smallestBet;
        if (contribution[i][1] == 0) {
            contribution.erase(contribution.begin() + i);
            i--;
        }
    }
    int counter = 0;
    while (contribution.size() != 0) {
        sidePots.push_back(SidePot());
        //repeat same as start of function but for side pots
        smallestBet = contribution[0][1];
        for (int i = 0; i < contribution.size(); i++) {
            if (contribution[i][1] < smallestBet)
                smallestBet = contribution[i][1];
        }
        for (int i = 0; i < contribution.size(); i++) {
            sidePots[counter].fillPot(smallestBet);
            sidePots[counter].addPlayer(contribution[i][0]);
        }

        for (int i = 0; i < contribution.size(); i++) {
            contribution[i][1] -= smallestBet;
            if (contribution[i][1] == 0) {
                contribution.erase(contribution.begin() + i);
                i--;
            }
        }
        counter++;
    }

    std::cout << " MAIN POT:  " << mainPot << std::endl;
    for(int i=0;i<sidePots.size();i++) {
        std::cout << "SIDE POT " << i + 1 << ":  " << sidePots[i].getAmount();
        for(int j=0;j<sidePots[i].getPlayerIDs().size();j++){
            std::cout<<"  " << sidePots[i].getPlayerIDs()[j];
        }
        std::cout << "\n";
    }
}

void Pot::fillPot(std::vector<Player>* players) {
    std::vector< std::vector<int> > contributions;
    //std::cout << "LOL" << (*players).size() << "HERE" << std::endl;
    int index = 0;
    for(int i=0; i<(*players).size(); i++){
        if((*players)[i].getInRound()) {
            std::vector<int> temp;
            contributions.push_back(temp);
            contributions[index].push_back((*players)[i].getID());
            contributions[index].push_back((*players)[i].getBet());
            index++;
        }
        std::cout << "LOL" << i << "HERE" << std::endl;
    }
    int smallestBet = contributions[0][1];

    for (int i = 0; i < contributions.size(); i++) {
        if (contributions[i][1] < smallestBet)
            smallestBet = contributions[i][1];
    }
    for (int i = 0; i < contributions.size(); i++)
        mainPot += smallestBet;

    for (int i = 0; i < contributions.size(); i++) {
        contributions[i][1] -= smallestBet;
        if (contributions[i][1] == 0) {
            contributions.erase(contributions.begin() + i);
            i--;
        }
    }
    int counter = 0;
    while (contributions.size() != 0) {
        sidePots.push_back(SidePot());
        //repeat same as start of function but for side pots
        smallestBet = contributions[0][1];
        for (int i = 0; i < contributions.size(); i++) {
            if (contributions[i][1] < smallestBet)
                smallestBet = contributions[i][1];
        }
        for (int i = 0; i < contributions.size(); i++) {
            sidePots[counter].fillPot(smallestBet);
            sidePots[counter].addPlayer(contributions[i][0]);
        }

        for (int i = 0; i < contributions.size(); i++) {
            contributions[i][1] -= smallestBet;
            if (contributions[i][1] == 0) {
                contributions.erase(contributions.begin() + i);
                i--;
            }
        }
        counter++;
    }
}

/*
 * Currently giving the wrong player money
 */
void Pot::distribute(std::vector<Player> *players) {
    int highest = -1;
    for(int i=0;i<(*players).size();i++){
        if((highest == -1 || (*players)[i].getHandStrength()>(*players)[highest].getHandStrength())) {
            if((*players)[i].getInRound())
                highest = i;
        }
    }
    (*players)[highest].win(mainPot);

    highest = -1;
    for(int i=0;i<sidePots.size();i++){
        sidePots[i].distribute(players);
    }
}

void Pot::emptyPot(){
    mainPot = 0;
    sidePots.clear();
}

void Pot::setFont(GText *theFont) {
    font = theFont;
}

void Pot::render(SDL_Renderer* renderer) {
    int total = 0;
    total += mainPot;
    for(int i=0;i<sidePots.size();i++){
        total += sidePots[i].getAmount();
    }
    std::string potString = "$" + std::to_string(total);
    (*font).getTexture().setAlpha(255);
    (*font).render(380, 300, 16, potString, renderer);
}

void Pot::printPot() {
    std::cout << "MAIN POT: " << mainPot << std::endl;
    for(int i=0; sidePots.size(); i++){
        sidePots[i].printPot(i);
    }
}