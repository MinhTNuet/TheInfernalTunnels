#include "menu.h"

Menu::Menu(SDL_Texture* MenuTex[], Mix_Chunk* menuSound[])
{
    sound_menu_1 = menuSound[0];
    sound_menu_2 = menuSound[1];
    menuBG = MenuTex[0];

    playBtn.setButton(MenuTex[1], 540, 330, 200, 48);


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

}

void Menu::handleInputMenu(SDL_Event& e, player& _Player, bool& isRunning)
{
    if(isMenu()){
        renderMainMenuScreen();
        switch(e.type){
        case SDL_MOUSEBUTTONDOWN:
            if(checkMouse(*playBtn.getBtnRect())){
                Mix_PlayChannel(-1, sound_menu_2, 0);
                menu = false;
                isRunning = true;
            }
            break;
        }
    }
}


