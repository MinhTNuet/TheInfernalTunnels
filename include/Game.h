#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>
#include "Map.h"
#include "Texture.h"
#include "gamefunc.h"

using namespace std;

class Game
{
public:
    bool init();
    bool loadMedia();
    bool loadMap();
};
#endif // GAME_H
