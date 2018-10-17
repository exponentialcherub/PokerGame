//
// Created by liams on 04/09/2016.
//

#include "Core.h"
#include "Pot.h"

int main(int argc, char *argv[] ){
    srand(time(NULL));
    Core c;
    c.mainLoop();


    //Testing pots
    Pot pot;
    std::vector< std::vector<int> > contributions;

    for(int i=0;i<5;i++){
        std::vector<int> temp;
        contributions.push_back(temp);
        contributions[i].push_back(i);
    }
    contributions[0].push_back(100);
    contributions[1].push_back(80);
    contributions[2].push_back(120);
    contributions[3].push_back(40);
    contributions[4].push_back(120);
    pot.fillPot(contributions);
    return 0;
}
