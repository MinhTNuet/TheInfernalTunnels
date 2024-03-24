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


class tileMat : public Texture
{
public:
    tileMat(int _x, int _y, int _type);
    void setCollision(int _h);
    int getType() const;
private:
    int tileType;

};

class Map
{
public:
    Map(){;}
    Map(int s_x, string fileName);

    void clearMap();
    void setStart_x(int _x);
    void setMapTexture(SDL_Texture* _Map);
    void loadMap(string fileName);
    void renderMap(vector<SDL_Rect> clipTile, SDL_Rect& camera);

    int getStart_x() const {return start_x;}
    int getStart_y() const {return start_y;}
    int getSTT() const {return STT;}

    tileMat getDataMap(int _x, int _y) const {return tiles[_y][_x];}
private:
    int start_x, start_y, STT;
    vector <vector<tileMat>> tiles;

    SDL_Texture* tileSet;

};

#endif // MAP_H
