//
// Created by liams on 15/06/2016.
//

#ifndef SUMMER_PROJECT_POKER_GAMELOGIC_H
#define SUMMER_PROJECT_POKER_GAMELOGIC_H

#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "GCard.h"
#include "GText.h"
#include "Pot.h"

enum Turn{
    START = 0,
    FLOP = 3,
    TURN = 4,
    RIVER = 5,
};

class GameLogic{
public:
    GameLogic();
    void bet(int = -1, int = 0);
    void newRound();
    void exit();

    bool loadMedia(SDL_Renderer*);
    void update();
    void render(SDL_Renderer* renderer);

    void playGame();
    int getButtonState();
    int amountOfActivePlayers();
private:

    //Player players[9];
    std::string convertCards(GCard[], int); //wont be needed
    int currentPlayer;//player class?
    int underTheGun;
    int smallBlindPlayer;
    int bigBlindPlayer;
    int smallBlind;
    int bigBlind;
    int currentBet;
    int currentRaise;
    //int pot;
    int minBet;
    int maxBet;
    Turn round;
    bool roundOver;

    /***NEW_VARIABLES  REPLACEMENTS***/
    Pot pot_;
    std::vector<Player> players;
    /*********************************/

    GText moneyFont;
    GText decisionFont;

    /*-----Cards-----*/
    Deck deck;
    GCard cardsOnTable[5];
    SDL_Rect cardPositions[5];
    SDL_Rect handPosition[2];
    GTexture cardsSpriteSheet;
    /*---------------*/

    /*------BotTiming----*/
    Uint32 timePassed;
    Uint32 delay;
    Uint32 pausedTicks;
    bool paused;
    /*-------------------*/

    void dealCards();
    void flop();
    void turn();
    void river();
    int evaluateHand(GCard[]); //hand class?
    void updateMaxBet();
    void updateMinBet();
    void getPlayerActions();
    void printTable(int);//wont be needed
    int playersInRound();
    void checkWinningHand();
    std::string determineHand(int); //probably not needed with gui
    void clearTable();
    GCard resetCard();
    void fillPot();


    bool playersBetting();
};

#endif //SUMMER_PROJECT_POKER_GAMELOGIC_H
