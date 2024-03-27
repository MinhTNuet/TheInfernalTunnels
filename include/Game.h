#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>
#include "Map.h"
#include "gamefunc.h"
#include "Texture.h"
#include "player.h"

using namespace std;

class Game
{
public:
    bool init();
//  bool createMap();
    void setTileClip();

    bool createPlayer();

    void render_Game();
    void load_map();

    void render_Map();

    void clearMedia();
    bool isRunning() {return runningGame;}
private:
    bool runningGame = false;

    SDL_Texture* tileSet = NULL;
    SDL_Texture* p_texture[3] = {NULL};

    SDL_Rect camera = {200, 200, SCREEN_WIDTH, SCREEN_HEIGHT};
    vector <SDL_Rect> tileClip;

    player* Player;
    Map* mp;
};
#endif // GAME_H
