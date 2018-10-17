//
// Created by liams on 26/08/2016.
//

#include "GraphicsTest.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BUTTON_WIDTH = 50;
const int BUTTON_HEIGHT = 50;



class Button {
public:
    Button();

    void setPosition(int,int);
    void setSize(int, int);

    void handleEvent(SDL_Event* e);
    void render(SDL_Renderer*);

private:
    int width;
    int height;
    SDL_Point position;
    SDL_Rect spriteClips[SPRITE_TOTAL];

    ButtonSprite currentSprite;
};

GraphicsTest::GraphicsTest() {
    window = NULL;
    screenSurface = NULL;
    renderer = NULL;
    gTexture = NULL;
    gCurrentSurface = NULL;
    table = NULL;
}

bool GraphicsTest::init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        //Create window
        window = SDL_CreateWindow("POKER YOUR FACE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }
            else {
                //Get window surface
                screenSurface = SDL_GetWindowSurface(window);
            }
        }
        //SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0x00, 0x00 ) );
        //check errors
    }

    return success;
}

bool GraphicsTest::loadMedia() {
    bool success = true;

    loadTexture("images/sun3.jpg");
    table = gTexture;
    if (table == NULL) {
        printf("ERROR couldn't load table image SDL ERROR: %s", SDL_GetError());
        success = false;
    }
    else {
        if (!loadTexture("images/WZ9Od.gif"))
            success = false;
        else{
            cardSpriteSheet = gTexture;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 13; j++) {
                    cards[(13 * i) + j].x = j * 81;
                    cards[(13 * i) + j].y = i * 117.4;
                    cards[(13 * i) + j].w = 81;
                    cards[(13 * i) + j].h = 117.4;
                }
            }
            for (int i = 0; i < 5; i++) {
                cardPositions[i].w = 30;
                cardPositions[i].h = 45;
                cardPositions[i].x = 316 + 35 * i;
                cardPositions[i].y = 250;
            }
            for(int i=0;i<2;i++){
                handPosition[i].w = 81;
                handPosition[i].h = 117;
                handPosition[i].x = 650 + i*40;
                handPosition[i].y = 500;
            }
            if(!loadTexture("images/button.png"))
                success = false;
            else{
                for(int i = 0; i<4;i++){
                   // buttonSpriteClips[i].w = 300;
                    //buttonSpriteClips[i].h = 200;
                    //buttonSpriteClips[i].x =
                   // buttonSpriteClips[i].y =
                }
            }
        }
    }
    return success;

}

void GraphicsTest::stretchToScreen(SDL_Surface *stretchedSurface) {
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;
    SDL_BlitScaled(stretchedSurface, NULL, screenSurface, &stretchRect);
}

/*
 * From lazy foo
 */
SDL_Surface *GraphicsTest::loadSurface(std::string path) {
    //The final optimized image
    SDL_Surface *optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, NULL);
        if (optimizedSurface == NULL) {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

bool GraphicsTest::loadTexture(std::string path) {
    bool success = true;

    SDL_Surface *theSurface = NULL;
    theSurface = IMG_Load(path.c_str());
    if (theSurface == NULL) {
        printf("ERROR COULDNT LOAD SURFACE");
        success = false;
    }
    else {
        gTexture = SDL_CreateTextureFromSurface(renderer, theSurface);
        if (gTexture == NULL) {
            printf("ERROR COULD NOT LOAD TEXTURE SDL ERROR: ", SDL_GetError());
            success = false;
        }
    }
    SDL_FreeSurface(theSurface);
    return success;
}

void GraphicsTest::loop() {
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                //Select surfaces based on key press
                switch (e.key.keysym.sym) {
                    /*case SDLK_UP:
                        gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                        break;

                    case SDLK_DOWN:
                        gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                        break;

                    case SDLK_LEFT:
                        gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                        break;

                    case SDLK_RIGHT:
                        gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                        break;

                    default:
                        gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                        break;*/
                }
            }

        }
        //Clear screen
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, table, NULL, NULL);
        SDL_RenderCopyEx(renderer, cardSpriteSheet, &cards[16], &handPosition[0], -10, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, cardSpriteSheet, &cards[7], &handPosition[1], 10, NULL, SDL_FLIP_NONE);
        for (int i = 0; i < 5; i++)
            SDL_RenderCopy(renderer, cardSpriteSheet, &cards[i], &cardPositions[i]);
        //Update screen
        SDL_RenderPresent(renderer);
    }
}

void GraphicsTest::exit() {
    /*for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
    {
        SDL_FreeSurface( gKeyPressSurfaces[ i ] );
        gKeyPressSurfaces[ i ] = NULL;
    }*/
    SDL_DestroyTexture(cardSpriteSheet);
    SDL_DestroyTexture(gTexture);
    SDL_DestroyTexture(table);
    cardSpriteSheet = NULL;
    table = NULL;
    gTexture = NULL;

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;

    SDL_Quit();
    IMG_Quit();
}

void Button::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void Button::setSize(int w, int h) {
    width = w;
    height = h;
}

void Button::handleEvent(SDL_Event *e) {

}

void Button::render(SDL_Renderer* renderer) {
    SDL_Rect renderSpace = {position.x, position.y, width, height};

    //SDL_RenderCopy(renderer, currentheet, &spriteClips[currentSprite], &renderSpace);
}

/*int main(int argc, char *argv[]) {
    GraphicsTest test;
    if (!test.init())
        printf("Failed to setup GUI");
    else {
        if (!test.loadMedia())
            printf("Failed to load media");
        else
            test.loop();
    }
    test.exit();
}*/
