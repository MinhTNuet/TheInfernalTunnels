#include "menu.h"

Menu::Menu(SDL_Texture* menuTex[], Mix_Chunk* menuSound[])
{
    sound_menu_1 = menuSound[0];
    sound_menu_2 = menuSound[1];
    menuBG = menuTex[0];

    playBtn.setButton(menuTex[1], 540, 330, 200, 48);
    exitBtn.setButton(menuTex[2], 540, 500, 200, 48);
    endBG.setButton(menuTex[3], 424, 250, 432, 250);
    restartBtn.setButton(menuTex[4], 582, 414, 120, 53);
}

bool Menu::checkMouse(const SDL_Rect& check)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    return(mouseX>=check.x && mouseX<=check.x+check.w) && (mouseY>=check.y && mouseY<=check.y+check.h) ;
}

void Menu::selectButton( button& check )
{
    if(checkMouse(*check.getBtnRect())){
        if(!check.selected)Mix_PlayChannel(-1, sound_menu_1, 0);
        check.selected = true;
    }
    else check.selected = false;
}


void Menu::renderMainMenuScreen()
{
    gamefunc::renderTexture(menuBG, NULL, NULL);
    gamefunc::renderTexture(playBtn.getBtnTex(), NULL, playBtn.getBtnRect());
    gamefunc::renderTexture(exitBtn.getBtnTex(), NULL, exitBtn.getBtnRect());
}

void Menu::handleInputMenu(SDL_Event& e, player& _Player, bool& isRunning)
{
    if(_Player.isDead())endgame = true;
    else restart = false;
    if(isEnd()){
        switch(e.type){
        case SDL_MOUSEBUTTONDOWN:
            if(checkMouse(*restartBtn.getBtnRect())){
                Mix_PlayChannel(-1, sound_menu_2, 0);
                restart = true;
                endgame = false;
            }
        }
    }
    if(isMenu()){
        endgame = false;
        renderMainMenuScreen();
        switch(e.type){
        case SDL_MOUSEBUTTONDOWN:
            if(checkMouse(*playBtn.getBtnRect())){
                Mix_PlayChannel(-1, sound_menu_2, 0);
                menu = false;
                isRunning = true;
            }
            if(checkMouse(*exitBtn.getBtnRect())){
                Mix_PlayChannel(-1, sound_menu_2, 0);
                menu = false;
            }
            break;
        }
    }
}

void Menu::renderEndMenuScreen(int score)
{
    int *w = new int, *h = new int;
    SDL_Color color = {255, 255, 255, 255};
    SDL_Texture* text = gamefunc::createTextTexture("Score: " + to_string(score), color);
    SDL_QueryTexture(text, NULL, NULL, w, h);

    gamefunc::renderTexture(endBG.getBtnTex(), NULL, endBG.getBtnRect());
    gamefunc::renderTexture(restartBtn.getBtnTex(), NULL, restartBtn.getBtnRect());
    gamefunc::renderTexture(text, NULL, 650-*w*3/4, 339, *w*1.25, *h*1.25);

    delete w, h;
    SDL_DestroyTexture(text);
}


