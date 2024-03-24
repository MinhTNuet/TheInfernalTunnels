#include "Map.h"

tileMap::tileMap(int _x, int _y, int _type) : Texture(_x, _y)
{
    tileType = _type;
    collision = {_x, _y, TILE_SIZE, TILE_SIZE};
}void tileMap::setCollision(int _h)
{
    collision.h = _h;
}

int tileMap::getType() const
{
    return tileType;
}

Map::Map(int s_x, const char* path, SDL_Texture* _tileSet, const int& _STT)
{
    start_x = s_x;
    start_y = 0;
    STT = _STT;
    tileSet = _tileSet;

    loadMap(path, _STT);
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

void Map::loadMap(const char* path, int _STT)
{
    ifstream file(path);
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
        vector <tileMap> row;
        for(int j=0; j < MAP_WIDTH; j++){
            file >> data;
            file >> temp;
            tileMap column(x, y, data);
            if(data > 120 && data < 140) column.setCollision(24);
            row.push_back(column);
            x += TILE_SIZE;
        }
        tiles.push_back(row);
        x = 0;
        y += TILE_SIZE;
    }
    file.close();
}

void Map::drawTile(SDL_Renderer* renderer, int x, int y, int tileType) {
    SDL_Rect rect = {x, y, TILE_SIZE, TILE_SIZE};
    SDL_Color color;
    if (tileType == 1) {
        color = {0, 0, 0};
    } else {
        color = {255, 255, 255};
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Map::renderMap(SDL_Renderer* renderer)
{
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;
            int tileType = tileMp[i][j];
            drawTile(renderer, x, y, tileType);
        }
    }
}
