#ifndef GAMEFUNC_H
#define GAMEFUNC_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>
#include "Texture.h"
#include "Map.h"

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;

#define MAP_WIDTH 34
#define MAP_HEIGHT 17
#define TILE_SIZE 64

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static TTF_Font* font = NULL;
static SDL_Event* event;

class Map;

namespace gamefunc {
    bool initWindow();
    void clearRender();
    SDL_Texture* loadTextureFromFile(string path);

    void renderTexture(SDL_Texture* img, SDL_Rect* rect1, SDL_Rect* rect2);
    void renderTexture(SDL_Texture* img, SDL_Rect* rect1, int x, int y, int w, int h);
    void renderTextureFlip( SDL_Texture* img, SDL_Rect* rect1, SDL_Rect* rect2, SDL_RendererFlip flip );
    void renderPresent();
    void destroyTexture();

    bool initFont(const char* path);
    SDL_Texture* createTextTexture(string text, SDL_Color color);

    bool checkCollision(SDL_Rect obj1, SDL_Rect obj2);
    bool checkWall(SDL_Rect obj, Map mat, bool* grounded = NULL);

    void setWindowFS();
    void quitWindowFS();
    void renderQuit();
}



#endif // GAMEFUNC_H
