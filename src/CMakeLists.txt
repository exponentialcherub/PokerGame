cmake_minimum_required(VERSION 3.5)
project(Summer_Project___Poker)

set(SDL2_Flags "-mwindows -Wl,--no-undefined -static-libgcc")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lSDL2 -lSDL2_image -lSDL2_ttf")

set(SDL2_ROOT     "C:/mingw-dev-lib/SDL2-2.0.4/i686-w64-mingw32")
set(SDL2_Includes "${SDL2_ROOT}/include/SDL2")
set(SDL2_LibDir   "${SDL2_ROOT}/lib")

set(SDL2IMAGE_ROOT "C:/mingw-dev-lib/SDL2_image-2.0.1/i686-w64-mingw32")
set(SDL2IMAGE_Includes "${SDL2IMAGE_ROOT}/include/SDL2")
set(SDL2IMAGE_LibDir "${SDL2IMAGE_ROOT}/lib")

set(SDL2TTF_ROOT "C:/mingw-dev-lib/SDL2_ttf-2.0.14/i686-w64-mingw32")
set(SDL2TTF_Includes "${SDL2TTF_ROOT}/include/SDL2")
set(SDL2TTF_LibDir "${SDL2TTF_ROOT}/lib")

include_directories(${SDL2_Includes} ${SDL2IMAGE_Includes} ${SDL2TTF_Includes})
link_directories(${SDL2_LibDir} ${SDL2IMAGE_LibDir} ${SDL2TTF_LibDir})

set(SOURCE_FILES GameLogic.cpp GameLogic.h Player.cpp Player.h Card.h Deck.cpp Deck.h Bot.cpp Bot.h Human.cpp Human.h GraphicsTest.cpp GraphicsTest.h GButton.cpp GButton.h GTexture.cpp GTexture.h main.cpp GraphicsMain.cpp GraphicsMain.h GCard.cpp GCard.h Core.cpp Core.h Hand.cpp Hand.h GText.cpp GText.h Pot.cpp Pot.h SidePot.cpp SidePot.h)
add_executable(Summer_Project___Poker ${SOURCE_FILES})

target_link_libraries(Summer_Project___Poker -lmingw32 SDL2main SDL2 SDL2_image SDL2_ttf)