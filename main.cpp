#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>
#include "Game.h"
using namespace std;
int main(int argc, char* argv[])
{
    SDL_Event event;
    Game mainGame;
    if(!mainGame.init())return 0;
    else {
        if(!mainGame.loadMedia() || !mainGame.loadMap())return 0;

    }
}
