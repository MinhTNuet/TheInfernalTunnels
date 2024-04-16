#include "Menu.h"

Menu::Menu(SDL_Texture* menuTex[], Mix_Chunk* menuSound[])
{
    sound_menu_1 = menuSound[0];
    sound_menu_2 = menuSound[1];
    menuBG = menuTex[0];
    tick = menuTex[1];

    playBtn.setButton(menuTex[2], 540, 330, 200, 48);
    settingBtn[0].setButton(menuTex[3], 540, 400, 200, 48);
    exitBtn.setButton(menuTex[4], 612, 500, 56, 54);

    pauseBG.setButton(menuTex[5], 494, 150, 292, 366);
    settingBtn[1].setButton(menuTex[6], 560, 330, 165, 53);
    menuBtn.setButton(menuTex[7], 560, 250, 165, 53);
    backBtn.setButton(menuTex[8], 582, 425, 120, 53);

    endBG.setButton(menuTex[9], 424, 250, 432, 246);
    retryBtn.setButton(menuTex[10], 582, 414, 120, 53);

    settingBG.setButton(menuTex[11], 529, 150, 222, 400);
    okBtn.setButton(menuTex[12], 600, 450, 86, 37);
    arrow.setButton(menuTex[13], 0, 0, 12, 21);

    soundTex = gamefunc::createTextTexture("Sound", {255, 255, 255, 255});
    musicTex = gamefunc::createTextTexture("Music", {255, 255, 255, 255});
    FSTex = gamefunc::createTextTexture("FullScreen", {255, 255, 255, 255});
}

void Menu::selectButton(button& check)
{
    if(checkMouse(*check.getBtnRect())){
        if(!check.selected)Mix_PlayChannel(-1, sound_menu_1, 0);
        check.selected = true;
        renderArrow(check);
    }
    else check.selected = false;
}

bool Menu::checkMouse(const SDL_Rect& check)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    return (mouseX>=check.x && mouseX<=check.x+check.w) && (mouseY>=check.y && mouseY<=check.y+check.h) ;
}

void Menu::handleInput(SDL_Event& e, player& _Player, bool& isRunning)
{
    if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
        if(paused) paused = false;
        else paused = true;
    }

    if(_Player.isDead())endgame = true;
    else retry = false;

    if(isEnd() && !isPause()){
        switch(e.type){
        case SDL_MOUSEBUTTONDOWN:
            if(checkMouse(*retryBtn.getBtnRect())){
                Mix_PlayChannel(-1, sound_menu_2, 0);
                retry = true;
                endgame = false;
                paused = false;
            }
            break;
        }
    }

    if(isMenu()){
        paused = false;
        endgame = false;
        renderMainMenu();
        if(!isSetting()){
            switch(e.type){
            case SDL_MOUSEBUTTONDOWN:
                if(checkMouse(*playBtn.getBtnRect())){
                    Mix_PlayChannel(-1, sound_menu_2, 0);
                    menu = false;
                    isRunning = true;
                }
                if(checkMouse(*settingBtn[0].getBtnRect())){
                    Mix_PlayChannel(-1, sound_menu_2, 0);
                    setting = true;
                }
                if(checkMouse(*exitBtn.getBtnRect()))menu = false;
                break;
            }
        }
    }
    if(isPause() && !isSetting()){
        renderPauseMenu();
        switch(e.type){
        case SDL_MOUSEBUTTONDOWN:
            if(checkMouse(*menuBtn.getBtnRect())){
                Mix_PlayChannel(-1, sound_menu_2, 0);
                menu = true;
            }
            if(checkMouse(*settingBtn[1].getBtnRect())){
                Mix_PlayChannel(-1, sound_menu_2, 0);
                setting = true;
            }
            if(checkMouse(*backBtn.getBtnRect())){
                Mix_PlayChannel(-1, sound_menu_2, 0);
                paused = false;
            }
            break;
        }
    }
    if(isSetting()){
        renderSetting();
        switch(e.type){
        case SDL_MOUSEBUTTONDOWN:
            if(checkMouse(*okBtn.getBtnRect())){
                Mix_PlayChannel(-1, sound_menu_2, 0);
                setting = false;
            }
            if(checkMouse({675, 320, 12, 14})){
                Mix_PlayChannel(-1, sound_menu_2, 0);
                if(tickM)tickM = false;
                else tickM = true;
            }
            if(checkMouse({675, 260, 12, 14})){
                Mix_PlayChannel(-1, sound_menu_2, 0);
                if(tickS)tickS = false;
                else tickS = true;
            }
            if(checkMouse({675, 380, 12, 14})){
                Mix_PlayChannel(-1, sound_menu_2, 0);
                if(fs){
                    gamefunc::quitWindowFS();
                    fs = false;
                }
                else{
                    gamefunc::setWindowFS();
                    fs = true;
                }
            }
        }
    }
}

void Menu::renderArrow(button& check)
{
    SDL_Rect* des = new SDL_Rect;
    des->x = check.getBtnRect()->x - 25;
    des->y = (check.getBtnRect()->y + check.getBtnRect()->h/2) - arrow.getBtnRect()->h/2;
    des->w = arrow.getBtnRect()->w;
    des->h = arrow.getBtnRect()->h;
    gamefunc::renderTexture(arrow.getBtnTex(), NULL, des);
}

void Menu::renderMainMenu()
{
    gamefunc::renderTexture(menuBG, NULL, NULL);
    gamefunc::renderTexture(playBtn.getBtnTex(), NULL, playBtn.getBtnRect());
    gamefunc::renderTexture(settingBtn[0].getBtnTex(), NULL, settingBtn[0].getBtnRect());
    gamefunc::renderTexture(exitBtn.getBtnTex(), NULL, exitBtn.getBtnRect());

    if(!isSetting()){
        selectButton(playBtn);
        selectButton(settingBtn[0]);
        selectButton(exitBtn);
    }
}

void Menu::renderPauseMenu()
{
    gamefunc::renderTexture(pauseBG.getBtnTex(), NULL, pauseBG.getBtnRect());
    gamefunc::renderTexture(menuBtn.getBtnTex(), NULL, menuBtn.getBtnRect());
    gamefunc::renderTexture(settingBtn[1].getBtnTex(), NULL, settingBtn[1].getBtnRect());
    gamefunc::renderTexture(backBtn.getBtnTex(), NULL, backBtn.getBtnRect());

    if(!isSetting()){
        selectButton(menuBtn);
        selectButton(settingBtn[1]);
        selectButton(backBtn);
    }
}

void Menu::renderEndMenu(int score)
{
    int *w = new int, *h = new int;
    SDL_Color color = {255, 255, 255, 255};
    SDL_Texture* text = gamefunc::createTextTexture(to_string(score), color);
    SDL_QueryTexture(text, NULL, NULL, w, h);

    gamefunc::renderTexture(endBG.getBtnTex(), NULL, endBG.getBtnRect());
    gamefunc::renderTexture(retryBtn.getBtnTex(), NULL, retryBtn.getBtnRect());
    gamefunc::renderTexture(text, NULL, 650-*w*3/4, 339, *w*1.25, *h*1.25);

    delete w, h;
    SDL_DestroyTexture( text );
    if(!isPause()) selectButton(retryBtn);
}

void Menu::renderSetting()
{
    gamefunc::renderTexture(settingBG.getBtnTex(), NULL, settingBG.getBtnRect() );
    gamefunc::renderTexture(settingBtn[0].getBtnTex(), NULL, 538, 167, 200, 48 );
    gamefunc::renderTexture(musicTex, NULL, 599, 317, 65, 24);
    gamefunc::renderTexture(soundTex, NULL, 598, 257, 68, 24);
    gamefunc::renderTexture(FSTex, NULL, 598, 377, 68, 24);
    gamefunc::renderTexture(okBtn.getBtnTex(), NULL, okBtn.getBtnRect());

    selectButton(okBtn);
    if(tickS)gamefunc::renderTexture(tick, NULL, 675, 260, 12, 14);
    if(tickM)gamefunc::renderTexture(tick, NULL, 675, 320, 12, 14);
    if(fs)gamefunc::renderTexture(tick, NULL, 675, 380, 12, 14);

}



