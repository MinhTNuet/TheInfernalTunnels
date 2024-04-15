#ifndef MENU_H
#define MENU_H

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "gamefunc.h"
#include "player.h"

using namespace std;

struct button{
    SDL_Texture* btnTex = NULL;
    SDL_Rect* btnRect = NULL;
    bool selected = false;
    button(){;}
    void setButton(SDL_Texture* image, int _x, int _y, int _w, int _h){
        btnTex = image;
        btnRect = new SDL_Rect;
        btnRect->x = _x;
        btnRect->y = _y;
        btnRect->w = _w;
        btnRect->h = _h;
    }
    SDL_Texture* getBtnTex() {return btnTex;}
    SDL_Rect* getBtnRect() {return btnRect;}
};

class Menu
{
private:
    button playBtn, exitBtn, okBtn, menuBtn, backBtn, retryBtn;
    button settingBG, pauseBG, endBG, arrow;
    button settingBtn[2];

    SDL_Texture* menuBG = NULL;
    SDL_Texture* tick = NULL;
    SDL_Texture* soundTex = NULL;
    SDL_Texture* musicTex = NULL;
    SDL_Texture* FSTex = NULL;
    Mix_Chunk* sound_menu_1 = NULL;
    Mix_Chunk* sound_menu_2 = NULL;
    bool menu = true, paused = false, endgame = false, retry = false, setting = false, tickS = true, tickM = true, fs = false;

public:
    Menu(SDL_Texture* menuTex[], Mix_Chunk* menuSound[]);
    void handleInput(SDL_Event& e, player& _Player, bool& isGameRunning);

    void renderArrow(button& check);
    void renderMainMenu();
    void renderPauseMenu();
    void renderSetting();
    void renderEndMenu(int score);

    void selectButton(button& check);
    bool checkMouse(const SDL_Rect& check);

    bool isMenu(){return menu;}
    bool isPause(){return paused;}
    bool isSetting(){return setting;}
    bool isEnd(){return endgame;}
    bool isRetry(){return retry;}
    bool soundOn(){return tickS;}
    bool musicOn(){return tickM;}
    bool isFullScr(){return fs;}

    bool isRunning(){return menu || paused || endgame || setting;}
};



#endif // MENU_H
