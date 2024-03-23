#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>
#include "gamefunc.h"
#include "Texture.h"

using namespace std;

class tileMap : public Texture
{
public:
    tileMap(int _x, int _y, int _type);
    void setCollision(int _h);
    int getType() const;
private:
    int tileType;

};

class GameMap
{
public:
    GameMap(){;}
    GameMap(int s_x, const char* path, SDL_Texture* _tileSet, const int& _STT);

    void clearMap();
    void setStart_x(int _x);
    void setMapTexture(SDL_Texture* _Map);
    void loadMap(const char* path, int _STT);
private:
    int start_x, start_y, STT;
    vector <vector<tileMap>> tiles;

    SDL_Texture* tileSet;

};

#endif // MAP_H
