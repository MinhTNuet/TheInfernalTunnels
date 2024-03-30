#include "Game.h"

bool Game::init()
{
    if(SDL_Init( SDL_INIT_EVERYTHING) < 0)
    {
        SDL_GetError();
        return false;
    }
    if(!IMG_Init(IMG_INIT_JPG))
    {
        IMG_GetError();
        return false;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        Mix_GetError();
        return false;
    }
    if(TTF_Init() == -1)
    {
        TTF_GetError();
        return false;
    }
    if(!gamefunc::initWindow()) return false;
    cout << "Success init dowload" << endl;

    tileSet = gamefunc::loadTextureFromFile("image/tileSet.png");
    p_texture[0] = gamefunc::loadTextureFromFile("image/player/Sprites/Jump.png");
    p_texture[1] = gamefunc::loadTextureFromFile("image/player/Sprites/Run.png");
    p_texture[2] = gamefunc::loadTextureFromFile("image/player/Sprites/Fall.png");

    return true;

}

bool Game::loadMedia()
{
    bool check = true;

}

//bool Game::loadMap()
//{
//    map_enemy map1("image/Map/map1.txt",1);
//    total_map.push_back(map1);
//    map_enemy map2("image/Map/map2.txt",2);
//    total_map.push_back(map2);
//    map_enemy map3("image/Map/map3.txt",3);
//    total_map.push_back(map1);
//    return true;
//}


void Game::setTileClip()
{
    tileClip.push_back({0, 0, 0, 0});

    for(int i=0; i<11; i++){
        for(int j=0; j<34; j++){
            tileClip.push_back({TILE_SIZE*j, TILE_SIZE*i, TILE_SIZE, TILE_SIZE} );
        }
    }
}

//bool Game::createMap()
//{
//    for( int i=0 ; i<3 ; i++){
//        int random = rand() % totalMap.size();
//        random = i;
//        Map gameMap( i*MAP_WIDTH*TILE_SIZE, totalMap[random].path, tileSet, totalMap[random].STT );
//        listM.push_back( Map );
//    }
//    return true;
//}

bool Game::createPlayer()
{
    Player = new player(64, 320, tileSet);
    if(Player == NULL) return false;
    return true;
}

void Game::updateGame()
{
    Player->updatePlayer(*mat);
    Player->changeCam(camera, *mat);
}

void Game::render_Game()
{
    render_Map();
    Player->renderPlayer(camera);
}

void Game::load_map()
{
    mat = new Map(0, "image/Map/map3.txt", tileSet);
}

void Game::render_Map()
{
    mat->renderMap(tileClip, camera);
}

void Game::resetGame()
{
    Player->resetplayer();

}

void Game::handleInputGame(SDL_Event &e)
{
    if(e.type == SDL_QUIT) gamefunc::renderQuit();
    Player->handleEvent(e);
}

void Game::runGame(SDL_Event &e)
{
    handleInputGame(e);
    updateGame();
    render_Game();

    gamefunc::renderPresent();
}

void Game::clearMedia()
{
    SDL_DestroyTexture(tileSet);
    TTF_CloseFont(font);
}
