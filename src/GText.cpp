//
// Created by liams on 19/09/2016.
//

#include "GText.h"

GText::GText() {
    crop.x = 0;
    crop.y = 0;
    crop.w = 0;
    crop.h = 0;
    offset = 0;
}

bool GText::setFont(std::string path, int width, int height, int offset, SDL_Renderer* renderer) {
    this->offset = offset;
    crop.w = width;
    crop.h = height;
    return font.loadTexture(path, renderer);
}

//For just numbers
void GText::render(int x, int y, int fontSize, std::string text, SDL_Renderer* renderer) {
    SDL_Rect renderSpace = {0,y,fontSize,fontSize};

    for(unsigned int i = 0; i<text.size();i++) {
        crop.x = position(text.at(i));
        renderSpace.x = x + i * (fontSize - offset);
        font.render(&renderSpace, &crop, renderer);
    }
}

int GText::position(char c) {
    int ascii = (unsigned char) c - 32;
    return crop.w*ascii;
}

GTexture GText::getTexture() {
    return font;
}

void GText::free() {
    font.free();
}