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

    soundTex = gamefunc::createTextTexture("Sound", {255, 255, 255, 255} );
    musicTex = gamefunc::createTextTexture("Music", {255, 255, 255, 255} );
    FSTex = gamefunc::createTextTexture("FullScr", {255, 255, 255, 255} );
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
                Mix_PlayChannel( -1, sound_menu_2, 0 );
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


