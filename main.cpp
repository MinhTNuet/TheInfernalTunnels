#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>
#include "Game.h"

using namespace std;


int main( int argc, char* argv[] )
{
    SDL_Event e;
    Game gameMain;
    if(!gameMain.init()) return 0;
    else{
        gameMain.setTileClip();
        gameMain.load_map();
        gameMain.createPlayer();
        while(true){
            SDL_PollEvent(&e);
            gameMain.runGame(e);
        }
    }
    gameMain.clearMedia();
    gamefunc::destroyTexture();
}
