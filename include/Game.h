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
#include "Monster.h"
#include "Menu.h"

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
    bool createMonster();

    void updateGame();
    bool updateMap();
    void updateMonster();
    void getHighScore();
    void setHighScore();

    void render_Game();
    void render_Map();
    void render_Monster();
    void render_hp_Score();

    void playSound();
    void resetGame();
    void handleInputGame(SDL_Event &e);
    void clearMedia();

    void runGame(SDL_Event &e);
    bool isRunning() {return runningGame;}

private:
    bool runningGame = false;
    int scoreRun = 0, scoreMonster = 0, totalScore = 0, highScore = 0;
    int musicStatus = 0;

    SDL_Texture* tileSet = NULL;
    SDL_Texture* p_texture[7] = {NULL};
    SDL_Texture* monsterTex[2] = {NULL};
    SDL_Texture* menuTex[14] = {NULL};
    Mix_Chunk* menuSound[2] = {NULL};

    SDL_Texture* liveBar = NULL;
    SDL_Texture* heart = NULL;
    player* Player;
    Menu* menu;
    Mix_Music* menuMusic = NULL;
    Mix_Music* gameMusic = NULL;

    SDL_Rect camera = {64, 128, SCREEN_WIDTH, SCREEN_HEIGHT};
    vector <SDL_Rect> tileClip;
    vector<SDL_Rect> hp_pos;

    vector <map_enemy> total_map;
    deque <Map> list_map;
    vector<Monster*> monsterList;

};
#endif // GAME_H
