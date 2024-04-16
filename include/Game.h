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
#include "Timer.h"

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
    bool createTimer();

    void updateGame();
    bool updateMap();
    void updateMonster();
    void getHighScore();
    void setHighScore();

    void render_Game();
    void render_Map();
    void render_Monster();
    void render_hp_Score();
    void render_time();

    void playSound();
    void resetGame();
    void handleInputGame(SDL_Event &e);
    void clearMedia();

    void countDownTime();
    void runGame(SDL_Event &e);
    bool isRunning(){return menu->isRunning() || runningGame;}

private:
    bool runningGame = false;
    int scoreRun = 0, scoreMonster = 0, totalScore = 0, highScore = 0;
    int musicStatus = 0;

    SDL_Texture* liveBar = NULL;
    SDL_Texture* heart = NULL;
    SDL_Texture* tileSet = NULL;
    SDL_Texture* p_texture[7] = {NULL};
    SDL_Texture* monsterTex[2] = {NULL};
    SDL_Texture* menuTex[2] = {NULL};
    Mix_Chunk* p_sound[5] = {NULL};
    Mix_Chunk* menuSound[2] = {NULL};
    Mix_Music* menuMusic = NULL;
    Mix_Music* gameMusic = NULL;

    player* Player;
    Timer* time;
    Menu* menu;

    SDL_Rect camera = {64, 128, SCREEN_WIDTH, SCREEN_HEIGHT};
    vector <SDL_Rect> tileClip;
    vector<SDL_Rect> hp_pos;

    vector <map_enemy> total_map;
    deque <Map> list_map;
    vector<Monster*> monsterList;

};
#endif // GAME_H
