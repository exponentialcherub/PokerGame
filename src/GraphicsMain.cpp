//
// Created by liams on 04/09/2016.
//

#include "GraphicsMain.h"

const int SCREEN_WIDTH = 800; //800
const int SCREEN_HEIGHT = 600; //600

GraphicsMain::GraphicsMain() {
    buttonState = -1;
}

bool GraphicsMain::loadMedia(SDL_Renderer* renderer){
    bool success = true;
    if(!table.loadTexture("images/sun4.jpg", renderer)){
        success = false;
    }
    else{
        if(!gameButtons[0].loadButton("check.png", renderer))
            success = false;
        gameButtons[0].setPosition(0, 400);
        if(!gameButtons[1].loadButton("raise.png", renderer))
            success = false;
        gameButtons[1].setPosition(0, 425);
        if(!gameButtons[2].loadButton("fold.png", renderer))
            success = false;
        gameButtons[2].setPosition(0, 450);
        /*if(!gameButtons[3].loadButton("call.png", renderer))
            success = false;
        if(!gameButtons[4].loadButton("allin.png", renderer))
            success = false;*/
    }
    return success;
}

void GraphicsMain::render(SDL_Renderer* renderer){
    table.render(0, 0 , renderer);
    for(int i=0;i<3;i++)
        gameButtons[i].render(renderer);
}

void GraphicsMain::handleInput(SDL_EventType type){
    for(int i=0;i<3;i++) {
        gameButtons[i].handleEvent(type);
        if(gameButtons[i].isButtonPressed() ) {
            buttonState = i;
            gameButtons[i].resetButtonPressed();
        }
    }
}

int GraphicsMain::getButtonState() {
    return buttonState;
}

void GraphicsMain::resetButtonState() {
    buttonState = -1;
}

void GraphicsMain::exit() {
    for(int i=0;i<3;i++)
        gameButtons[i].free();
    table.free();
}