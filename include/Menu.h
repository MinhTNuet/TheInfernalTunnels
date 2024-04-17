#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>
#include "gamefunc.h"
#include "player.h"

using namespace std;

struct button{
    SDL_Texture* btnTex = NULL;
    SDL_Rect* btnRect = NULL;
    bool selected = false;

    button(){;}
    void setButton( SDL_Texture* image, int _x, int _y, int _w, int _h ){
        btnTex = image;
        btnRect = new SDL_Rect;
        btnRect->x = _x;
        btnRect->y = _y;
        btnRect->w = _w;
        btnRect->h = _h;
    }
    SDL_Texture* getBtnTex(){return btnTex;}
    SDL_Rect* getBtnRect(){return btnRect;}
};


class Menu {
public:
    Menu(SDL_Texture* menuTex[], Mix_Chunk* menuSound[]);
    void selectButton(button& check);
    bool checkMouse(const SDL_Rect& check);
    void handleInputMenu(SDL_Event& e, player& _Player, bool& isGameRunning);
    void renderMainMenuScreen();
    void renderEndMenuScreen(int score);

    bool isMenu(){return menu;}
    bool isEnd(){return endgame;}
    bool isRestart(){return restart;}
    bool isRunning(){return menu || endgame;}
private:
    button playBtn;
    button exitBtn;
    button restartBtn;
    button backBtn;
    button endBG;
    SDL_Texture* menuBG = NULL;
    Mix_Chunk* sound_menu_1 = NULL;
    Mix_Chunk* sound_menu_2 = NULL;
    bool menu = true, endgame = false, restart = false;
};

#endif // MENU_H
