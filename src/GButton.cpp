//
// Created by liams on 01/09/2016.
//

#include "GButton.h"

GButton::GButton() {
    //width = 0;
    //height = 0;
    position.x = 0;
    position.y = 0;
    currentSprite = SPRITE_MOUSE_OUT;
    buttonPressed = false;
    buttonHeld = false;
    active = true;
}

bool GButton::loadButton(std::string name, SDL_Renderer* renderer){
    bool success = spriteSheet.loadTexture("images/buttons/"+name, renderer);
    for(int i=0;i<SPRITE_TOTAL;i++){
        spriteClips[i].x = 0;
        spriteClips[i].y = (i*spriteSheet.getRect().h)/SPRITE_TOTAL;
        spriteClips[i].w = spriteSheet.getRect().w;
        spriteClips[i].h = spriteSheet.getRect().h/SPRITE_TOTAL;
    }
    return success;
}

void GButton::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

/*void GButton::setSize(int w, int h) {
    width = w;
    height = h;
}*/

void GButton::handleEvent(SDL_EventType type) {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );

        //Check if mouse is in button
        bool inside = true;

        if( x < position.x ) {
            inside = false;
        } else if( x > position.x + spriteClips[0].w ) {
            inside = false;
        } else if( y < position.y ) {
            inside = false;
        } else if( y > position.y + spriteClips[0].h ) {
            inside = false;
        }

        if( !inside ) {
            currentSprite = SPRITE_MOUSE_OUT;
        }
        else {
            //Set mouse over sprite
            switch( type )
            {
                case SDL_MOUSEMOTION:
                    currentSprite = SPRITE_MOUSE_OVER;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    currentSprite = SPRITE_MOUSE_DOWN;
                    buttonHeld = false;
                    break;
                case SDL_MOUSEBUTTONUP:
                    currentSprite = SPRITE_MOUSE_OVER;
                    if(buttonHeld==false)
                        buttonPressed = true;
                    buttonHeld = true;
                    break;
            }
        }
}

void GButton::render(SDL_Renderer* renderer) {
    if(active) {
        SDL_Rect renderSpace = {position.x, position.y, spriteClips[currentSprite].w, spriteClips[currentSprite].h};
        spriteSheet.render(&renderSpace, &spriteClips[currentSprite], renderer);
    }
}

void GButton::render(SDL_Renderer* renderer, int width, int height){
    if(active) {
        SDL_Rect renderSpace = {position.x, position.y, width, height};
        spriteSheet.render(&renderSpace, &spriteClips[currentSprite], renderer);
    }
}

bool GButton::isButtonPressed() {
    return buttonPressed;
}

void GButton::resetButtonPressed(){
    buttonPressed = false;
}

bool GButton::buttonActive() {
    return active;
}

void GButton::setActive(bool active){
    this->active = active;
}

void GButton::singleSprite() {
    for(int i=0;i<SPRITE_TOTAL;i++){
        spriteClips[i].x = 0;
        spriteClips[i].y = 0;
        spriteClips[i].w = spriteSheet.getRect().w;
        spriteClips[i].h = spriteSheet.getRect().h;
    }
}

void GButton::free(){
    spriteSheet.free();
}