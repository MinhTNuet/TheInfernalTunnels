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
    Game(){;};
    bool init();
    bool loadMedia();
    bool loadMap();
    void setTileClip();

    bool createMap();
    bool createPlayer();

    void updateGame();
    bool updateMap();


    void render_Game();
    void load_map();
    void render_Map();

    void resetGame();
    void handleInputGame(SDL_Event &e);
    void clearMedia();

    void runGame(SDL_Event &e);
    bool isRunning() {return runningGame;}

private:
    bool runningGame = false;

    SDL_Texture* tileSet = NULL;
    SDL_Texture* p_texture[7] = {NULL};

    SDL_Rect camera = {64, 128, SCREEN_WIDTH, SCREEN_HEIGHT};
    vector <SDL_Rect> tileClip;

    player* Player;
    vector <map_enemy> total_map;
    deque <Map> list_map;

};
#endif // GAME_H
