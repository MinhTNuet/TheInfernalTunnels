#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>
#include "Game.h"

using namespace std;


int main(int argc, char* argv[])
{
    bool quit = false;
    SDL_Event e;
    if(!gamefunc::initWindow()) return 0;
    else {
        while( !quit )
        {
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                gamefunc::setRender();
                SDL_RenderClear(renderer);
                Map mp;

                mp.renderMap(renderer);

                gamefunc::renderPresent();
                gamefunc::destroyTexture();
            }
        }
    }


    gamefunc::destroyTexture();
}
