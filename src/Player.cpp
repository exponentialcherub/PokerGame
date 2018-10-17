//
// Created by liams on 15/06/2016.
//

#include "Player.h"
//#include "Core.h"

/*
 * Player info :
 * -name
 * -decision
 * -winner
 * -money
 * -bet(on table)
 * -picture
 */

const std::string names[20] = {"Edmond", "Wayne", "Rafael", "Walter", "Wiley", "Theo", "Chang", "Tony", "Grant", "Omar",
                          "Louise", "Jenny", "Tasha", "Teresa", "Amanda", "Peggy", "Britta", "Nichol", "Iris",
                          "Maggie"};


Player::Player() {
    money = 1000;
    inGame = 1;
    human = 0; //initially sets them as a bot
    inRound = 1;
    name = names[rand() % 20];
    position.x = 0;
    position.y = 0;
    betting = false;
    turn = false;
    bet = 0;
    playerInfo.x = 0;
    playerInfo.y = 0;
    playerInfo.w = 70;
    playerInfo.h = 100;
}

bool Player::loadMedia(SDL_Renderer* renderer){
    bool success = true;
    TTF_Font* font = TTF_OpenFont("ttf/OpenSans-Bold.ttf", 12);
    if(font==NULL)
        success = false;
    else{
        SDL_Color color = {0xFF, 0xFF, 0xFF};
        if(!gName.loadFromRenderedText(name, color, font, renderer))
            success = false;
        else{
            if(!box.loadTexture("images/playerbox.png", renderer))
                success = false;
            else{
                box.setAlpha(200);
                if(!border.loadTexture("images/playerborder.png", renderer))
                    success = false;
            }

        }
    }

    TTF_CloseFont(font);
    return success;
}

int Player::getMoney() {
    return money;
}

void Player::adjustMoney() {
    money -= bet;
}

int Player::getAction() {
    int action;
    while (!(std::cin >> action)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input, please enter another value." << std::endl;
    }
    return action;
}

int Player::tempCPUAction() {
    int a = rand() % 100;
    if (a < 75)
        a = 1;
    else if (a >= 75)
        a = 0;
    return a;
}

std::string Player::getName() {
    return name; //segfault here
}

void Player::setName(std::string thisName) {
    name = thisName;
}

int Player::getID() {
    return playerID;
}

void Player::setID(int id){
    playerID = id;
}

GCard *Player::getCards() {
    return cards;
}

void Player::setCards(GCard card1, GCard card2) {
    cards[0] = card1;
    cards[1] = card2;
}

void Player::renderCards(SDL_Renderer *renderer, SDL_Rect renderSpace[2], GTexture cardTexture) {
    cards[0].render(cardTexture, renderer, &renderSpace[0], -10);
    cards[1].render(cardTexture, renderer, &renderSpace[1], 10);
}

void Player::render(SDL_Renderer *renderer, GText moneyFont, GText decisionFont) {
    if(inGame) {
        setAlpha(moneyFont, decisionFont);

        std::string betString = "$" + std::to_string(bet);
        moneyFont.render(position.x, position.y, 16, betString, renderer);
        SDL_RenderSetViewport(renderer, &playerInfo);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, 0);
        SDL_Rect background = {0, 0, playerInfo.w, playerInfo.h};
        box.render(&background,NULL, renderer);
        if(turn)
            border.render(&background, NULL, renderer);
        switch (decision) {
            case -1:
                gName.render(2, 0, renderer);
                break;
            case 0:
                decisionFont.render(8, 0, 16, "CHECK", renderer);
                break;
            case 1:
                decisionFont.render(8, 0, 16, "CALL", renderer);
                break;
            case 2:
                decisionFont.render(8, 0, 16, "ALL-IN", renderer);
                break;
            case 3:
                decisionFont.render(8, 0, 16, "RAISE", renderer);
                break;
            case 4:
                decisionFont.render(8, 0, 16, "FOLD", renderer);
                break;
            case 5:
                decisionFont.render(8,0,16,"WINNER",renderer);
            default:
                gName.render(2, 0, renderer);
                break;
        }
        std::string moneyString = "$" + std::to_string(money-bet);
        moneyFont.render(15, 85, 16, moneyString, renderer);
        SDL_RenderSetViewport(renderer, NULL);
    }
}

void Player::setAlpha(GText moneyFont, GText decisionFont) {
    if(inRound){
        box.setAlpha(200);
        gName.setAlpha(255);
        moneyFont.getTexture().setAlpha(255);
        decisionFont.getTexture().setAlpha(255);
    }
    else{
        moneyFont.getTexture().setAlpha(100);
        decisionFont.getTexture().setAlpha(100);
        gName.setAlpha(100);
        box.setAlpha(100);
    }
}

int Player::getInGame() {
    return inGame;
}

void Player::setInGame(int thisInGame) {
    inGame = thisInGame;
}

int Player::getInRound() {
    return inRound;
}

void Player::setInRound(int thisInRound) {
    inRound = thisInRound;
}

int Player::getIsHuman() {
    return human;
}

void Player::setIsHuman(int thisHuman) {
    human = thisHuman;
}

int Player::getBet() {
    return bet;
}

void Player::resetBet() {
    bet = 0;
}

bool Player::isBetting() {
    return betting;
}

void Player::setBetting(bool b) {
    if(b){
        if(inGame && inRound)
            betting = true;
        else
            betting = false;
    }
    decision = -1;
}

void Player::setTurn(bool a) {
    turn = a;
}

void Player::setPositions(SDL_Point betPosition, SDL_Point playerPosition) {
    position = betPosition;
    playerInfo.x = playerPosition.x;
    playerInfo.y = playerPosition.y;
}

void Player::check(int currentBet) {
    if (betting) {
        if (money < currentBet) {
            bet = money;
            decision = 2;
        }
        else {
            bet = currentBet;
            (currentBet ? decision = 1:decision = 0);
        }
        betting = false;
        turn = false;
    }
}

void Player::raise(int theRaise) {
    if (betting) {
        bet = theRaise;
        betting = false;
        decision = 3;
        turn = false;
    }
}

void Player::fold() {
    if (betting) {
        inRound = 0;
        betting = false;
        decision = 4;
        turn = false;
    }
}

void Player::win(int pot) {
    money += pot;
    decision = 5;
}

void Player::printInfo() {
    if (inGame)
        std::cout << "|| " << name << " Money: $" << money - bet << " Bet: $" << bet << (inRound ? " in" : " out") <<
        "||     ";
}

void Player::checkHand(GCard cardsOnTable[]) {
    Hand hand(cardsOnTable, cards);
    hand.evaluate();
    handStrength = hand.getHandStrength();
}

int Player::getHandStrength() {
    return handStrength;
}

void Player::free(){
    box.free();
    border.free();
}