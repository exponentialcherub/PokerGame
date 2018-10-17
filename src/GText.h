//
// Created by liams on 19/09/2016.
//

#ifndef SUMMER_PROJECT_POKER_GTEXT_H
#define SUMMER_PROJECT_POKER_GTEXT_H

#include "GTexture.h"

class GText {
private:
    GTexture font;
    SDL_Rect crop;
    int position(char);
    int offset;
public:
    GText();
    void free();
    bool setFont(std::string,int, int, int,SDL_Renderer*);
    void render(int, int, int, std::string, SDL_Renderer*);
    GTexture getTexture();
};


#endif //SUMMER_PROJECT_POKER_GTEXT_H
