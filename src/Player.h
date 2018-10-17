//
// Created by liams on 15/06/2016.
//

#ifndef SUMMER_PROJECT_POKER_PLAYER_H
#define SUMMER_PROJECT_POKER_PLAYER_H


#include <iostream>
#include <SDL.h>
#include "Card.h"
#include "GCard.h"
#include "GText.h"
#include "Hand.h"


class Player {
public:
    Player();
    bool loadMedia(SDL_Renderer*);
    void free();

    int getMoney();
    void adjustMoney();
    std::string getName();
    void setName(std::string);
    int getID();
    void setID(int);
    GCard* getCards();
    void setCards(GCard, GCard);
    int getInGame();
    void setInGame(int);
    int getInRound();
    void setInRound(int);
    int getIsHuman();
    void setIsHuman(int);
    int getBet();
    void resetBet();
    void setTurn(bool);
    bool isBetting();
    void setBetting(bool);
    void setPositions(SDL_Point, SDL_Point);
    int getHandStrength();

    void check(int);
    void raise(int);
    void fold();
    void win(int);
    void checkHand(GCard[]);

    int getAction();
    int tempCPUAction();

    void renderCards(SDL_Renderer*, SDL_Rect[2], GTexture);
    void render(SDL_Renderer*, GText, GText);
    void printInfo();
private:
    std::string name;
    GTexture gName;
    int playerID;
    int money;
    int handStrength;
    GCard cards[2];
    SDL_Point position; //position of bet on table
    SDL_Rect playerInfo; //Area to render player info (name, money, picture, etc.)
    GTexture box;
    GTexture border;

    //change to bools
    int inGame;
    int inRound;
    int human; //1 if human, 0 if bot

    int decision; //-1 default 0 check 1 call 2 allin 3 raise 4 fold
    int bet; //function for resetBet?
    bool betting; //whether they are done betting yet or not
    bool turn; //whether its their turn or not

    void setAlpha(GText, GText);
};


#endif //SUMMER_PROJECT_POKER_PLAYER_H
