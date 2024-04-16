#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>
#include "Game.h"
#include "Timer.h"
using namespace std;

int main(int argc, char* argv[])
{
    SDL_Event e;
    Game gameMain;
    if(!gameMain.init())return 0;
    else{
        if(!gameMain.loadMedia() || !gameMain.loadMap() || !gameMain.createTimer())return 0;
        else{
            gameMain.setTileClip();
            if(!gameMain.createMap() || !gameMain.createPlayer() || !gameMain.createMonster())return 0;
            else {
                    cout<<1;
                gameMain.countDownTime();
                while(gameMain.isRunning()){
                    SDL_PollEvent(&e);
                    gameMain.runGame(e);
                }

            }
        }
    }
    gameMain.clearMedia();
    gamefunc::destroyTexture();
}
