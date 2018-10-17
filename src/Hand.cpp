//
// Created by liams on 08/09/2016.
//

#include "Hand.h"

const int TOTAL_CARDS = 7;

Hand::Hand(GCard tableCards[5], GCard playerCards[2]) {
    //memcpy(cards, oi, sizeof(cards));
    std::copy(tableCards, tableCards+5, cards);
    std::copy(playerCards, playerCards+2, cards+5);
    evaluate();
}

void Hand::evaluate() {
    handStrength = 1; //Royal Flush = 10, straight flush=9,..., high card=1
    //can base ai choices on this :)))))))

    //bubble sort
    GCard temp;
    int swapped = 1;
    for (int i = 0; i < TOTAL_CARDS; i++) {
        swapped = 0;
        for (int j = 0; j < 6; j++) {
            if (cards[j].getRank() > cards[j + 1].getRank()) {
                temp = cards[j];
                cards[j] = cards[j + 1];
                cards[j + 1] = temp;
                swapped = 1;
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
    for (int i = 0; i < TOTAL_CARDS; i++) {
        if (!k) {
            for (int j = 0; j < 7; j++) {
                if (cards[i].getRank() == cards[j].getRank() && i != j) {
                    a = cards[i].getRank();
                    k++;
                }
            }
        }
        else if (!x) {
            for (int j = 0; j < TOTAL_CARDS; j++) {
                if (cards[i].getRank() == cards[j].getRank() && i != j && cards[i].getRank() != a) {
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
            if ((cards[k].getRank() + 1) == cards[k + 1].getRank()) {
                x++;
            }
            else if (!(cards[k].getRank() == cards[k + 1].getRank()))
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
    for (int i = 0; i < TOTAL_CARDS; i++) {
        suitTally[cards[i].getSuit() - 1]++;
        if ((suitTally[cards[i].getSuit() - 1] == 5) && handStrength < 6) {
            int temp = y;
            while (cards[y + 1].getSuit() == cards[y].getSuit() && (y < (temp + 4)))
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
        for (int i = 0; i < TOTAL_CARDS; i++) {
            if (cards[i].getRank() < 15 && cards[i].getRank() > 9)
                tally[cards[i].getRank() - 10]++;
        }
        for (int i = 0; i < 5; i++) {
            if (tally[i] == 0)
                return;
        }
        handStrength = 10;
    }
}

int Hand::getHandStrength() {
    return handStrength;
}
