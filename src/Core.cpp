//
// Created by liams on 07/09/2016.
//

#include "Core.h"

const int SCREEN_WIDTH = 800; //800
const int SCREEN_HEIGHT = 600; //600

Core::Core() {
    quit = false;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        quit = true;
    }
    else {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

        //Create window
        window = SDL_CreateWindow("POKER YOUR FACE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            quit = true;
        }
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                quit = true;
            }
            else {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    quit = true;
                }
                else {
                    //Init ttf
                    if( TTF_Init() == -1 ) {
                        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                        quit = true;
                    }
                    buttonState = -1;
                }
            }
        }
    }
}

bool Core::loadMedia() {
    bool success = true;
    if(!table.loadTexture("images/sun4.png", renderer)){
        success = false;
    }
    else{
        if(!gameButtons[0].loadButton("check170x150.png", renderer))
            success = false;
        gameButtons[0].setPosition(0, 450);
        if(!gameButtons[1].loadButton("call170x150.png", renderer))
            success = false;
        gameButtons[1].setPosition(0, 450);
        if(!gameButtons[2].loadButton("allin170x150.png", renderer))
            success = false;
        gameButtons[2].setPosition(0, 450);
        if(!gameButtons[3].loadButton("raise170x150.png", renderer))
            success = false;
        gameButtons[3].setPosition(0, 500);
        if(!gameButtons[4].loadButton("fold170x150.png", renderer))
            success = false;
        gameButtons[4].setPosition(0, 550);
        if(!gameButtons[5].loadButton("plus.png", renderer))
            success = false;
        gameButtons[5].setPosition(115, 502);
        gameButtons[5].singleSprite();
        if(!gameButtons[6].loadButton("minus.png", renderer))
            success = false;
        gameButtons[6].setPosition(5, 502);
        gameButtons[6].singleSprite();
        gameButtons[5].setActive(false);
        gameButtons[6].setActive(false);
    }
    return success;
}

void Core::mainLoop() {
    game = new GameLogic();

    if(!loadMedia() || !game->loadMedia(renderer)) //segfault here
        quit = true;

    while(!quit && game->amountOfActivePlayers()>1){
        SDL_Delay(1); //Give time back to system

        SDL_RenderClear(renderer);

        input();
        update();
        render();

        SDL_RenderPresent(renderer);
    }
    exit();
}

void Core::input(){
    while (SDL_PollEvent(&e) != 0 ) {
        switch(e.type){
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) { }
                break;
            case SDL_MOUSEBUTTONUP:
                handleInput(SDL_MOUSEBUTTONUP);
                break;
            case SDL_MOUSEBUTTONDOWN:
                handleInput(SDL_MOUSEBUTTONDOWN);
                break;
            case SDL_MOUSEMOTION:
                handleInput(SDL_MOUSEMOTION);
                break;
            default:;
        }
    }
    //gm.handleInput(&e);
}

void Core::handleInput(SDL_EventType type){
    for(int i=0;i<BUTTON_TOTAL;i++) {
        if(gameButtons[i].buttonActive()) {
            gameButtons[i].handleEvent(type);
        }
        if(gameButtons[i].isButtonPressed()) {
            buttonState = i;
            gameButtons[i].resetButtonPressed();
        }
    }
}

void Core::update(){
    int state = game->getButtonState(); //determines which button should be shown between check allin and call
    switch(state){
        case 0:
            gameButtons[0].setActive(true);
            gameButtons[1].setActive(false);
            gameButtons[2].setActive(false);
            break;
        case 1:
            gameButtons[0].setActive(false);
            gameButtons[1].setActive(true);
            gameButtons[2].setActive(false);
            break;
        case 2:
            gameButtons[0].setActive(false);
            gameButtons[1].setActive(false);
            gameButtons[2].setActive(true);
            break;
        default:
            std::cerr <<"ERROR with buttons";
            break;
    }

    /*if(buttonState==3){
        gameButtons[3].setActive(false);
        gameButtons[5].setActive(true);
        gameButtons[6].setActive(true);
    }*/

    if(buttonState!=-1)
        game->bet(buttonState);
    buttonState = -1;

    game->update();
}

void Core::render() {
    table.render(0, 0 , renderer);
    for(int i=0;i<BUTTON_TOTAL-2;i++)
        gameButtons[i].render(renderer);
    gameButtons[5].render(renderer, 45, 45);
    gameButtons[6].render(renderer, 45, 45);
    game->render(renderer);
}

void Core::exit() {
    for(int i=0;i<BUTTON_TOTAL;i++)
        gameButtons[i].free();
    table.free();
    game->exit();
    delete game;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;

    SDL_Quit();
    IMG_Quit();

}