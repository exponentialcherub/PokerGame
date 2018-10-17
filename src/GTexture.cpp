//
// Created by liams on 01/09/2016.
//

#include "GTexture.h"

GTexture::GTexture() {
    texture = NULL;
    renderSpace.w = 0;
    renderSpace.h = 0;
    count = new unsigned int(1);
}

GTexture::GTexture(const GTexture &other) {
    texture = other.texture;
    renderSpace = other.renderSpace;
    name = other.name;
    count = other.count;
    (*count)++;
}

GTexture::~GTexture(){
    (*count)--;
    if((*count) ==0) {
        free();
        delete count;
    }
}

SDL_Texture* GTexture::getImage() {
    return texture;
}

SDL_Rect GTexture::getRect() {
    return renderSpace;
}

void GTexture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(texture, alpha);
}

bool GTexture::loadTexture(std::string path, SDL_Renderer* renderer) {
    free();
    name = path;
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    SDL_Surface* tempSurface = IMG_Load(path.c_str());
    if(tempSurface==NULL){
        printf("ERROR can't load image %s", path.c_str());
    }
    else {
        SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 255, 0, 255));
        texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        if (texture == NULL) {
            printf("ERROR can't create texture from %s SDL ERROR: %s", path.c_str(), SDL_GetError());
        }
        else{
            renderSpace.w = tempSurface->w;
            renderSpace.h = tempSurface->h;
        }
        SDL_FreeSurface(tempSurface);
    }
    return texture != NULL;
}

bool GTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer ) {
    //Get rid of preexisting texture
    free();
    name = textureText;

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Blended( font, textureText.c_str(), textColor );
    if( textSurface == NULL ) {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else {
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == NULL ) {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else {
            renderSpace.w = textSurface->w;
            renderSpace.h = textSurface->h;
        }
        SDL_FreeSurface( textSurface );
    }
    return texture != NULL;
}

void GTexture::render( int x, int y, SDL_Renderer* renderer ) {
    //printf("%s",name.c_str());
    renderSpace.x = x;//segfault here
    renderSpace.y = y;

    //Render to screen
    SDL_RenderCopy( renderer, texture, NULL, &renderSpace);
}

void GTexture::render(SDL_Rect* clip, SDL_Rect* crop, SDL_Renderer* renderer, int angle){
    //printf("%s %s",name.c_str(), SDL_GetError());
    SDL_RenderCopyEx(renderer, texture, crop, clip, angle, NULL, SDL_FLIP_NONE);
}

void GTexture::free() {
    if(texture!=NULL){
        SDL_DestroyTexture(texture);
        texture = NULL;
        renderSpace.w = 0;
        renderSpace.h = 0;
        name = "";
    }
}