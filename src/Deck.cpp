//
// Created by liams on 21/08/2016.
//

#include "Deck.h"

Deck::Deck() {
    top = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            deck[13*(i)+(j)].setValues(i+1, j+2);
            //deck[13 * (i) + (j)].rank = j + 1 + 1;
            //deck[13 * (i) + (j)].suit = i + 1;
            //deck[13 * (i) + (j)].spriteIndex = 13 * (i) + (j);
        }
    }
}

void Deck::shuffle() {
    int x;
    GCard tempCard;
    top = 0;

    for (int i = 0; i < 52; i++) {
        x = rand() % 52;
        tempCard = deck[i];
        deck[i] = deck[x];
        deck[x] = tempCard;
    }
}

GCard Deck::hitMe() {
    top++;
    return deck[top];
}
