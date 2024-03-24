#ifndef GAMEFUNC_H
#define GAMEFUNC_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

#define MAP_WIDTH 10
#define MAP_HEIGHT 8
#define TILE_SIZE 32
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static TTF_Font* font = NULL;
static SDL_Event* event;

const int tileMp[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1}
};

namespace gamefunc {
    bool initWindow();
    void clearRender();
    void setRender();
    SDL_Texture* loadTextureFromFile(string path);
    void renderTexture(SDL_Texture* img, SDL_Rect* rect1, SDL_Rect* rect2);
    void renderTexture(SDL_Texture* img, SDL_Rect* rect1, int x, int y, int w, int h);
    void renderTextureFlip( SDL_Texture* img, SDL_Rect* rect1, SDL_Rect* rect2, SDL_RendererFlip flip );
    void renderPresent();
    void destroyTexture();

    bool initFont(const char* path);
    SDL_Texture* createTextTexture(string text, SDL_Color color);
    void renderQuit();
}



#endif // GAMEFUNC_H