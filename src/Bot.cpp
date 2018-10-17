//
// Created by liams on 22/08/2016.
//

#include "Bot.h"

/**
 * Attibutes: (to differ bots, less predictable)
 * Aggression
 * Bluffing
 * Predictability
 * Intelligence
 * Experience?
 * Temprament
 * Balls
 *
 * AI:
 * -evaluate hand, make decision based on that
 * - will be too predictable, implement attributes eventually, then chat based on attributes
 * -look at potential hands on table to call other players bluff
 */

Bot::Bot(){

}

int Bot::getAction() {
    int a = rand() % 100;
    if(a<75)
        a=1;
    else if(a>=75)
        a=0;
    return a;
}
