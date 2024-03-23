#include "Game.h"
#include "gamefunc.h"
bool Game::init()
{
    if(SDL_Init( SDL_INIT_EVERYTHING) < 0){
        SDL_GetError();
        return false;
    }
    if(!IMG_Init(IMG_INIT_JPG)){
        IMG_GetError();
        return false;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        Mix_GetError();
        return false;
    }
    if(TTF_Init() == -1){
        TTF_GetError();
        return false;
    }
    if(!gamefunc::initWindow()) return false;
    cout << "Success init dowload" << endl;
    return true;
}

bool Game::loadMedia(){

}

bool Game::loadMap(){

}


