#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>
#include "gamefunc.h"
#include "Texture.h"
#include "Game.h"

using namespace std;

int tileMaps[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1}
};

class tileMap : public Texture
{
public:
    tileMap(int _x, int _y, int _type);
    void setCollision(int _h);
    int getType() const;
private:
    int tileType;

};

class Map
{
public:
    Map(){;}
    Map(int s_x, const char* path, SDL_Texture* _tileSet, const int& _STT);

    void clearMap();
    void setStart_x(int _x);
    void setMapTexture(SDL_Texture* _Map);
    void loadMap(const char* path, int _STT);

    void drawTile(SDL_Renderer* renderer, int x, int y, int tileType);
    void renderMap(SDL_Renderer* renderer);
private:
    int start_x, start_y, STT;
    vector <vector<tileMap>> tiles;

    SDL_Texture* tileSet;

};

#endif // MAP_H
