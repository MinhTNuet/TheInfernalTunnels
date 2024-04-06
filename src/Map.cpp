#include "Map.h"

tileMat::tileMat(int _x, int _y, int _type) : Texture(_x, _y)
{
    tileType = _type;
    collision = {_x, _y, TILE_SIZE, TILE_SIZE};
}

void tileMat::setCollision(int _h)
{
    collision.h = _h;
}

int tileMat::getType() const
{
    return tileType;
}

Map::Map(int s_x, const char* fileName, SDL_Texture* _tileSet, const int& _STT)
{
    start_x = s_x;
    start_y = 0;
    STT = _STT;
    tileSet = _tileSet;
    loadMap(fileName, _STT);
}

void Map::clearMap()
{
    tiles.clear();
}

void Map::setStart_x(int _x)
{
    start_x = _x;
}

void Map::setMapTexture(SDL_Texture* texture)
{
    tileSet = texture;
}

void Map::loadMap(const char* fileName, int _STT)
{
    ifstream file(fileName);
    if(!file)
    {
        cout << "Could not load data map";
    }

    STT = _STT;
    int x = 0;
    int y = 0;
    int data;
    char temp;

    for(int i=0; i < MAP_HEIGHT; i++){
        vector <tileMat> row;
        for(int j=0; j < MAP_WIDTH; j++){
            file >> data;
            file >> temp;
            tileMat column(x, y, data);
            row.push_back(column);
            x += TILE_SIZE;
        }
        tiles.push_back(row);
        x = 0;
        y += TILE_SIZE;
    }
    file.close();
}

void Map::renderMap(vector <SDL_Rect> clipTile, SDL_Rect& camera)
{
    for(int i = camera.y/TILE_SIZE; i*TILE_SIZE - camera.y < SCREEN_HEIGHT; i++){
        for(int j = (camera.x - getStart_x())/TILE_SIZE; j< MAP_WIDTH; j++){
            if(j<0) continue;
            if(j*TILE_SIZE + getStart_x() - camera.x >= SCREEN_WIDTH) break;
            SDL_Rect dst = {getDataMap(j,i).getX() + getStart_x() - camera.x, getDataMap(j,i).getY() - camera.y, TILE_SIZE, TILE_SIZE};
            gamefunc::renderTexture(tileSet, &clipTile[getDataMap(j,i).getType()], &dst);
        }
    }
}

void Map::fillRight(vector <SDL_Rect> clipTile, SDL_Rect& camera)
{
    if(camera.x + 64*MAP_WIDTH <= getStart_x())return;

    for(int i=camera.y/TILE_SIZE; i*TILE_SIZE - camera.y < SCREEN_HEIGHT; i++){
        for(int j=0; j*64+getStart_x() - camera.x < SCREEN_WIDTH; j++){
            SDL_Rect dst = {getStart_x() - camera.x + j*64, getDataMap(j,i).getY() - camera.y, TILE_SIZE, TILE_SIZE};
            gamefunc::renderTexture(tileSet, &clipTile[getDataMap(j,i).getType()], &dst);
        }
    }
}

void Map::fillLeft(vector <SDL_Rect> clipTile, SDL_Rect& camera)
{
    if(camera.x >= getStart_x() + 64*MAP_WIDTH)return;
    renderMap(clipTile, camera);
}
