//
// Created by liams on 01/09/2016.
//

#ifndef SUMMER_PROJECT_POKER_GTEXTURE_H
#define SUMMER_PROJECT_POKER_GTEXTURE_H

//#include <SDL_render.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

class GTexture {
public:
    GTexture();
    GTexture(const GTexture& other);
    ~GTexture();

    bool loadTexture(std::string, SDL_Renderer* = NULL);
    bool loadFromRenderedText(std::string, SDL_Color , TTF_Font*, SDL_Renderer* = NULL);
    void render(int,int, SDL_Renderer* = NULL);
    //For rotating image, includes crop
    void render(SDL_Rect* = NULL, SDL_Rect* = NULL, SDL_Renderer* = NULL, int = 0);

    SDL_Texture* getImage();
    SDL_Rect getRect();
    void setAlpha(Uint8);

    void free();

private:
    std::string name;
    SDL_Texture* texture;
    SDL_Rect renderSpace;
    unsigned int *count;
};


#endif //SUMMER_PROJECT_POKER_GTEXTURE_H
