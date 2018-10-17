#include "GameLogic.h"

//9 players tournament**
/* To implement**:
 * {figuring out winner
 * comparing specific hands ->> kicker cards etc
 * split pot for equal hands
 * splitting pot/}
 * options for all-in depending on circumsgtances   /
 * all players go out it crashes /
 * -money somehow /
 * different starting players for each turn /
 * under the gun adjust for less players and players that are out (check for 2 players)
 * when they are allin ->cant bet /
 * convertcards not working completely still
 * skipping turns in later rounds?? maybe to do with applying under the gun?? (check this)
 * replace 9 with constant (amount of players)  /
 * maybe have class for pot /
 * use list or vector so i can use bots and human classes, then can just remove and add
 *                       players to list (might not work and also a lot of moving around,
 *                       may involve using virtual functions)??
 * less getters and setters in player, give it more to do "tell not ask"
 * BOT INTELIGNENCE -- bot subclass..
 *
 * -------gui-----------*
 * scrollbar for raise or buttons(+ -) or just + - buttons
 * different buttons for different circumstances  /
 * pot money on table (ttf)    /
 * player info (see player)
 * timer evntually (line across bottom that gets shorter), small line on other players for their go's
 * make buttons translucent when it is not your turn
 * card animations /
 * dark screen when annoucing winner, announce winner, winning hand, animate splitting pot
 * no gold outline when player starting, also skips over next player when user is starting player
 * turn cards over one at a time /
 * animate cards being dealt, spin cards 180 degrees
 * player pictures
 * players chatting (bot ai)
 * menu eventually
 */

const int PLAYER_TOTAL = 9;
const SDL_Point BET_POSITIONS[9] = {{400, 400},
                                    {300, 390},
                                    {220, 350},
                                    {220, 250},
                                    {300, 210},
                                    {500, 210},
                                    {550, 250},
                                    {550, 350},
                                    {500, 390}};
const SDL_Point PLAYER_POSITIONS[9] = {{370, 450},
                                       {200, 435},
                                       {50,  350},
                                       {50,  180},
                                       {250, 80},
                                       {490, 80},
                                       {690, 180},
                                       {690, 350},
                                       {540, 435}};

GameLogic::GameLogic() {
    //std::cout << "Please enter your name." << std::endl;
    std::string name = "Liam";
    //cin >> name;
    Player human; players.push_back(human);
    players[0].setName(name);
    players[0].setIsHuman(1);

    for(int i=0; i<PLAYER_TOTAL-1;i++){
        Player player;
        players.push_back(player);
    }

    underTheGun = rand() % 9;
    roundOver = false;
    round = START;
    currentPlayer = 0;
    currentBet = 0;
    currentRaise = 0;
    smallBlind = 20;
    bigBlind = 40;
    for (int i = 0; i < 5; i++)
        cardsOnTable[i] = resetCard();

    for (int i = 0; i < PLAYER_TOTAL; i++) {
        players[i].setPositions(BET_POSITIONS[i], PLAYER_POSITIONS[i]);
        players[i].setID(i);
    }

    for (int i = 0; i < 5; i++) {
        cardPositions[i].w = 30;
        cardPositions[i].h = 45;
        cardPositions[i].x = 316 + 35 * i;
        cardPositions[i].y = 250;
    }
    for (int i = 0; i < 2; i++) {
        handPosition[i].w = 81;
        handPosition[i].h = 117;
        handPosition[i].x = 650 + i * 40;
        handPosition[i].y = 500;
    }

    timePassed = 0;
    pausedTicks = 0;
    delay = 1000;

    newRound();
}

std::string GameLogic::convertCards(GCard cards[], int sizeOfArray) {
    //int length = sizeOfArray / sizeof(GCard);
    //shouldnt need this class soon anyway so length is as long as it will need to be, ignore errors
    int length = 5;
    std::stringstream sstm;
    for (int i = 0; i < length; i++) {
        if (cards[i].getRank() == -1 && cards[i].getSuit() == -1)
            break;
        if (cards[i].getRank() == 14)
            sstm << 'A';
        else if (cards[i].getRank() == 11)
            sstm << 'J';
        else if (cards[i].getRank() == 12)
            sstm << 'Q';
        else if (cards[i].getRank() == 13)
            sstm << 'K';
        else
            sstm << (cards[i].getRank());

        if (cards[i].getSuit() == 1)
            sstm << 'S';
        else if (cards[i].getSuit() == 2)
            sstm << 'H';
        else if (cards[i].getSuit() == 3)
            sstm << 'C';
        else if (cards[i].getSuit() == 4)
            sstm << 'D';
        sstm << " ";
    }
    return sstm.str();
}

void GameLogic::dealCards() {
    for (int i = 0; i < 9; i++) {
        if (players[i].getInGame()) {
            GCard a = deck.hitMe();
            GCard b = deck.hitMe();
            players[i].setCards(a, b);
        }
    }
}

void GameLogic::flop() {
    for (int i = 0; i < 3; i++) {
        cardsOnTable[i] = deck.hitMe();
    }
    round = FLOP;
}

void GameLogic::turn() {
    cardsOnTable[3] = deck.hitMe();
    round = TURN;
}

void GameLogic::river() {
    cardsOnTable[4] = deck.hitMe();
    round = RIVER;
}

/*
 * Need to be able to compare equal hands
 */
int GameLogic::evaluateHand(GCard hand[]) {
    int handStrength = 1; //Royal Flush = 10, straight flush=9,..., high card=1
    //can base ai choices on this :)))))))

    //bubble sort
    GCard temp;
    bool swapped;
    for (int i = 0; i < 7; i++) {
        swapped = false;
        for (int j = 0; j < 6; j++) {
            if (hand[j].getRank() > hand[j + 1].getRank()) {
                temp = hand[j];
                hand[j] = hand[j + 1];
                hand[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }


    //check for pair, two pairs, triple and full house
    int k = 0; //when k is 1->pair, 2->trip, 3->quad
    int x = 0; //same for x eg 1 and 1 would mean two pairs
    char a;
    for (int i = 0; i < 7; i++) {
        if (!k) {
            for (int j = 0; j < 7; j++) {
                if (hand[i].getRank() == hand[j].getRank() && i != j) {
                    a = hand[i].getRank();
                    k++;
                }
            }
        }
        else if (!x) {
            for (int j = 0; j < 7; j++) {
                if (hand[i].getRank() == hand[j].getRank() && i != j && hand[i].getRank() != a) {
                    x++;
                }
            }
        }
    }
    if (k == 3 || x == 3)
        handStrength = 8;
    else if ((k == 2 && x == 1) || (k == 1 && x == 2))
        handStrength = 7;
    else if (k == 2 || x == 2)
        handStrength = 4;
    else if (k == 1 && x == 1)
        handStrength = 3;
    else if (k == 1 || x == 1)
        handStrength = 2;
    else if (k == 0 && x == 0)
        handStrength = 1;
    else
        std::cout << "ERROR" << std::endl;

    //check for straight
    int y; // this value is where the straight starts
    for (int i = 0; i < 3; i++) {
        x = 0;
        k = i;
        while (x < 4) {
            if ((hand[k].getRank() + 1) == hand[k + 1].getRank()) {
                x++;
            }
            else if (!(hand[k].getRank() == hand[k + 1].getRank()))
                break;
            k++;
        }
        if (x == 4 && handStrength < 5) {
            handStrength = 5;
            y = i;
            break;
        }
        else {
            y = 0;
        }
    }

    //check for flush and straight flush
    int suitTally[4] = {0, 0, 0, 0};
    for (int i = 0; i < 7; i++) {
        suitTally[hand[i].getSuit() - 1]++;
        if ((suitTally[hand[i].getSuit() - 1] == 5) && handStrength < 6) {
            int temp = y;
            while (hand[y + 1].getSuit() == hand[y].getSuit() && (y < (temp + 4)))
                y++;
            //cout << y << " " << temp << endl;
            if (handStrength == 5 && y == temp + 4) {
                handStrength = 9;
                break;
            }
            else {
                handStrength = 6;
                break;
            }
        }
    }

    //check for royal flush
    int tally[5] = {0, 0, 0, 0};
    if (handStrength == 9) {
        for (int i = 0; i < 7; i++) {
            if (hand[i].getRank() < 15 && hand[i].getRank() > 9)
                tally[hand[i].getRank() - 10]++;
        }
        for (int i = 0; i < 5; i++) {
            if (tally[i] == 0)
                return handStrength;
        }
        handStrength = 10;
    }

    return handStrength;
}

/*
 * function used when the human player presses a button/places a bet
 */
void GameLogic::bet(int decision, int raise) {
    if (currentPlayer == 0) {
        if (decision == -1)
            return;
        else if (decision == 0 || decision == 1 || decision == 2)
            players[currentPlayer].check(currentBet);
        else if (decision == 3) {
            for (int i = 0; i < PLAYER_TOTAL; i++) {
                players[i].setBetting(true);
            }
            currentRaise = raise - currentBet;
            currentBet = raise;
            players[currentPlayer].raise(raise);
        }
        else if (decision == 4)
            players[currentPlayer].fold();
    }
}

void GameLogic::fillPot() {
    pot_.fillPot(&players);
    pot_.printPot();

    for (int i = 0; i < 9; i++) {
        players[i].adjustMoney();
        //pot += players[i].getBet();
        players[i].resetBet();
    }
    currentBet = 0;
    currentRaise = 0;
}

void GameLogic::printTable(int turn) {
    std::cout << std::endl;
    for (int i = 0; i < 9; i++) {
        std::cout << (i == currentPlayer ? "**" : "");
        players[i].printInfo();
    }
    std::cout << "\n" << "Cards on table: " << convertCards(cardsOnTable, sizeof(Card) * turn) << std::endl;
    //std::cout << "Pot: $" << pot << std::endl;
    std::cout << std::endl;
}

void GameLogic::updateMaxBet() {
    for (int i = 0; i < 9; i++) {
        int a = players[i].getMoney();
        if (a > maxBet && i != currentPlayer)
            maxBet = a;
    }
    if ((players[currentPlayer].getMoney() - players[currentPlayer].getBet()) < maxBet)
        maxBet = players[currentPlayer].getMoney();
}

void GameLogic::updateMinBet() {
    if (currentRaise == 0)
        minBet = currentBet + bigBlind;
    else
        minBet = currentBet + currentRaise;
}

void GameLogic::getPlayerActions() {
    currentPlayer = underTheGun;
    for (int i = 0; i < 9; i++) {
        if (players[currentPlayer].getInRound() &&
            (players[currentPlayer].getMoney() != players[currentPlayer].getBet())) {
            //for when there's 1 person left --> they win the pot
            if (playersInRound() == 1) {
                fillPot();
                return;
            }

            if (players[currentPlayer].getIsHuman()) {
                std::cout << "Your cards: " << convertCards(players[currentPlayer].getCards(), 2 * sizeof(Card)) <<
                "\nCheck (1)/Raise (2)/Fold (3)." << std::endl; //is convertcards working?, arguements correct?
                int action = players[currentPlayer].getAction();
                if (action == 1) {
                    players[currentPlayer].check(currentBet);
                }
                else if (action == 2) {
                    std::cout << "How much would you like to raise by? "
                            "(Min $" << minBet << "  " << "Max $" << maxBet << ")" << std::endl;
                    //maxbet not entirely correct ATM
                    int raise = players[currentPlayer].getAction();
                    while (raise > maxBet || raise < minBet) {
                        std::cout << "Value is out of range, please enter another. "
                                "(Min $" << minBet << "  " << "Max $" << maxBet << ")" << std::endl;
                        raise = players[currentPlayer].getAction();
                    }
                    //raiseBet(raise);
                    i = 0;
                }
                else if (action == 3) {
                    players[currentPlayer].fold();
                }
                printTable(5);
            }
            else {
                int action = players[currentPlayer].tempCPUAction();
                if (action) {
                    players[currentPlayer].check(currentBet);
                }
                else {
                    players[currentPlayer].fold();
                }
            }
        }
        currentPlayer = (currentPlayer + 1) % 9;
        updateMaxBet();
        updateMinBet();
    }
    fillPot();
}

GCard GameLogic::resetCard() {
    GCard card;
    card.setValues(-1, -1);
    return card;
}

void GameLogic::newRound() {
    for (int i = 0; i < PLAYER_TOTAL; i++) {
        if (players[i].getMoney() == 0 && players[i].getInGame()) {
            players[i].setInGame(0);
            std::cout << players[i].getName() << " is out!" << std::endl;
        }
    }

    for (int i = 0; i < PLAYER_TOTAL; i++) {
        players[i].setBetting(true);
        players[i].setTurn(false);
    }

    underTheGun = (underTheGun + 1) % 9;
    while (!players[underTheGun].getInGame())
        underTheGun = (underTheGun + 1) % 9;

    bigBlindPlayer = underTheGun;
    do {
        bigBlindPlayer--;
        if (bigBlindPlayer == -1)
            bigBlindPlayer = 8;
    }
    while (!players[bigBlindPlayer].getInGame());

    smallBlindPlayer = bigBlindPlayer;
    do {
        smallBlindPlayer--;
        if (smallBlindPlayer == -1)
            smallBlindPlayer = 8;
    }
    while (!players[smallBlindPlayer].getInGame());
    //std::cout << bigBlindPlayer << "   " << smallBlindPlayer;
    players[bigBlindPlayer].raise(bigBlind);
    players[bigBlindPlayer].setBetting(true);
    players[smallBlindPlayer].raise(smallBlind);
    players[smallBlindPlayer].setBetting(true);
    currentPlayer = underTheGun;
    currentBet = bigBlind;
    deck.shuffle();
    dealCards();
    players[currentPlayer].setTurn(true);

    if (currentPlayer == 0)
        paused = true;
    else
        paused = false;
}

void GameLogic::clearTable() {
    //pot = 0;
    pot_.emptyPot();
    for (int i = 0; i < 9; i++) {
        //players[i].setCards(resetCard(), resetCard());
        players[currentPlayer].resetBet();
    }
    for (int i = 0; i < 5; i++)
        cardsOnTable[i] = resetCard();
    for (int i = 0; i < 9; i++) {
        if (players[i].getInGame())
            players[i].setInRound(1);
        else
            players[i].setInRound(0);
    }
}

int GameLogic::getButtonState() {
    int buttonState = -1;
    if (currentBet == 0)
        buttonState = 0;
    else if (currentBet > 0) {
        buttonState = 1;
        if (players[0].getMoney() < currentBet)
            buttonState = 2;
    }
    return buttonState;
}

int GameLogic::amountOfActivePlayers() {
    int activePlayers = 0;
    for (int i = 0; i < 9; i++) {
        if (players[i].getInGame() == 1)
            activePlayers++;
    }
    return activePlayers;
}

int GameLogic::playersInRound() {
    int playersIn = 0;
    for (int i = 0; i < 9; i++) {
        if (players[i].getInRound())
            playersIn++;
    }
    return playersIn;
}

bool GameLogic::playersBetting() {
    for (int i = 0; i < 9; i++) {
        if (players[i].isBetting())
            return true;
    }
    return false;
}

std::string GameLogic::determineHand(int handStrength) {
    std::string hand;
    switch (handStrength) {
        case 1:
            hand = "High Card";
            break;
        case 2:
            hand = "Pair";
            break;
        case 3:
            hand = "Two Pairs";
            break;
        case 4:
            hand = "Three of a Kind";
            break;
        case 5:
            hand = "Straight";
            break;
        case 6:
            hand = "Flush";
            break;
        case 7:
            hand = "Full House";
            break;
        case 8:
            hand = "Four of a Kind";
            break;
        case 9:
            hand = "Straight Flush";
            break;
        case 10:
            hand = "Royal Flush";
            break;
        default:
        std::cout << "ERROR: hand strength out of range" << std::endl;
    }
    return hand;
}

/*
 * compare equal hands
 */
void GameLogic::checkWinningHand() {
    int winner = -1;
    //int handStrengths[PLAYER_TOTAL];
    std::vector< int > strengths;
    if (playersInRound() == 1) {
        for (int i = 0; i < PLAYER_TOTAL; i++) {
            if (players[i].getInRound()) {
                winner = i;
                break;
            }
        }
        std::cout << players[winner].getName() << " wins the pot!!" << std::endl;
    }
    else {
        for (int i = 0; i < PLAYER_TOTAL; i++) {
            Hand hand(cardsOnTable, players[i].getCards()); //make hand a variable in player, access hand strength from there
            hand.evaluate();
            //handStrengths[i] = hand.getHandStrength();
            strengths.push_back(hand.getHandStrength());
            if (players[i].getInRound()) {

                //if ((winner == -1 || handStrengths[i] > handStrengths[winner]))
                //    winner = i;
                if((winner == -1) || strengths[i] > strengths[winner])
                    winner = i;
            }
        }
        std::cout << players[winner].getName() << " wins the pot!!\n" << "Winning hand: " <<
        determineHand(strengths[winner]) << strengths[winner]
        << "\n";
        std::cout << convertCards(cardsOnTable, sizeof(cardsOnTable)) <<
        convertCards(players[winner].getCards(), 2 * sizeof(Card)) << "\n" << std::endl;
    }
    //players[winner].win(1000);

    pot_.distribute(&players);

}

void GameLogic::playGame() {
    for (int i = 0; i < 9; i++) {
        if (players[i].getIsHuman()) {
            std::cout << "Please enter your name." << std::endl;
            std::string name;
            std::cin >> name;
            players[i].setName(name);
        }
    }
    underTheGun = rand() % 9;
    currentBet = bigBlind;
    clearTable();
    while (amountOfActivePlayers() > 1) {
        int bigBlindPlayer;
        int smallBlindPlayer;
        int j = (underTheGun - 1) % 9;
        for (int i = 0; i < 9; i++) {
            if (players[j].getInGame())
                bigBlindPlayer = j;
            if (players[j - 1].getInGame())
                smallBlindPlayer = j - 1;
            j = (j - 1) % 9;
        }
        players[bigBlindPlayer].raise(bigBlind);
        players[smallBlindPlayer].raise(smallBlind);
        /*if (underTheGun == 0) {
            playerBets[8] = bigBlind;
            playerBets[7] = smallBlind;
        }
        else if (underTheGun == 1) {
            playerBets[0] = bigBlind;
            playerBets[8] = smallBlind;
        }
        else {
            playerBets[underTheGun - 1] = bigBlind;
            playerBets[underTheGun - 2] = smallBlind;
        }*/
        currentBet = bigBlind;
        deck.shuffle();
        dealCards();
        std::cout << "Round " << round << std::endl;
        printTable(0);
        getPlayerActions();

        flop();
        printTable(3);
        getPlayerActions();

        turn();
        printTable(4);
        getPlayerActions();

        river();
        printTable(5);
        getPlayerActions();

        printTable(5);
        checkWinningHand();
        for (int i = 0; i < 9; i++) {
            if (players[i].getMoney() == 0 && players[i].getInGame()) {
                players[i].setInGame(0);
                std::cout << players[i].getName() << " is out!" << std::endl;
            }
        }
        clearTable();

        underTheGun = (underTheGun + 1) % 9;
        while (!players[underTheGun].getInGame())
            underTheGun = (underTheGun + 1) % 9;

    }

    int winner = -1;
    for (int i = 0; i < 9; i++) {
        if (players[i].getInGame()) {
            winner = i;
            break;
        }
    }
    std::cout << "Winner is " << players[winner].getName() << "! B-ANTA" << std::endl;

}

bool GameLogic::loadMedia(SDL_Renderer *renderer) {
    bool success = true;
    if (!cardsSpriteSheet.loadTexture("images/cards1.gif", renderer)) {
        success = false;
    }
    else {
        if (!moneyFont.setFont("images/moneyfont.bmp", 64, 64, 8, renderer))
            success = false;
        else {
            pot_.setFont(&moneyFont);
            if (!decisionFont.setFont("images/font.bmp", 64, 64, 8, renderer))
                success = false;
            else {
                for (int i = 0; i < PLAYER_TOTAL; i++) {
                    if (!players[i].loadMedia(renderer))
                        success = false;
                }
            }
        }
    }
    return success;
}

void GameLogic::update() {
    if (!players[currentPlayer].isBetting()) {
        do {
            currentPlayer = (currentPlayer + 1) % PLAYER_TOTAL;
        }
        while (!players[currentPlayer].getInRound());
        players[currentPlayer].setTurn(true);
        if (currentPlayer == 0)
            paused = true;
        else
            paused = false;

        //players[currentPlayer].setBetting(true);
        //updatepot
        updateMinBet();
        updateMaxBet();

        /*printTable(5);
        if (players[currentPlayer].getIsHuman()) {
            cout << "Your cards: " << convertCards(players[currentPlayer].getCards(), 2 * sizeof(Card)) <<
            "\nCheck (1)/Raise (2)/Fold (3)." << endl;
        }*/
    }
    if (paused)
        timePassed = SDL_GetTicks();

    if (playersInRound() == 1) {
        fillPot();
        roundOver = true;
        checkWinningHand();
    }
    else if (!players[currentPlayer].getIsHuman() && (SDL_GetTicks() - delay) > timePassed &&
             SDL_GetTicks() > delay) { //bot action
        timePassed = SDL_GetTicks();
        //This can be done in player class??????
        int action = players[currentPlayer].tempCPUAction();
        if (action) {
            players[currentPlayer].check(currentBet);
        }
        else {
            players[currentPlayer].fold();
        }
    }
    if (!playersBetting()) {
        //flop, turn or river
        currentPlayer = smallBlindPlayer;
        while (!players[currentPlayer].getInRound())
            currentPlayer = (currentPlayer + 1) % PLAYER_TOTAL;

        for (int i = 0; i < PLAYER_TOTAL; i++) {
            //if (players[i].getInRound())
            players[i].setBetting(true);
            players[i].checkHand(cardsOnTable);
        }
        if (round == START) {
            fillPot();
            flop();
        } else if (round == FLOP) {
            fillPot();
            turn();
        } else if (round == TURN) {
            fillPot();
            river();
        } else if (round == RIVER) {
            fillPot();
            roundOver = true;
            checkWinningHand();
        }
    }
    if (roundOver) {
        roundOver = false;
        round = START;
        clearTable();
        newRound();
    }
}

void GameLogic::render(SDL_Renderer *renderer) {
    players[0].renderCards(renderer, handPosition, cardsSpriteSheet);
    for (int i = 0; i < 9; i++) {
        players[i].render(renderer, moneyFont, decisionFont);
    }
    for (int i = 0; i < round; i++) {
        cardsOnTable[i].render(cardsSpriteSheet, renderer, &cardPositions[i]);
        if(cardsOnTable[i].getAnimating())
            break;
    }
    pot_.render(renderer);
}

void GameLogic::exit() {
    cardsSpriteSheet.free();
    moneyFont.free();
    decisionFont.free();
    for (int i = 0; i < PLAYER_TOTAL; i++)
        players[i].free();
}
