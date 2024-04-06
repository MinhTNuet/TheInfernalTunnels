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

    return true;

}

bool Game::loadMedia()
{
    bool check = true;
    tileSet = gamefunc::loadTextureFromFile("image/tileSet.png");
    p_texture[0] = gamefunc::loadTextureFromFile("image/player/Sprites/Jump.png");
    p_texture[1] = gamefunc::loadTextureFromFile("image/player/Sprites/Run.png");
    p_texture[2] = gamefunc::loadTextureFromFile("image/player/Sprites/Fall.png");
    return check;
}

bool Game::loadMap()
{
    map_enemy map1("image/Map/map1.txt",1);
    total_map.push_back(map1);
    map_enemy map2("image/Map/map2.txt",2);
    total_map.push_back(map2);
    map_enemy map3("image/Map/map3.txt",3);
    total_map.push_back(map3);
    return true;
}


void Game::setTileClip()
{
    tileClip.push_back({0, 0, 0, 0});

    for(int i=0; i<11; i++){
        for(int j=0; j<34; j++){
            tileClip.push_back({TILE_SIZE*j, TILE_SIZE*i, TILE_SIZE, TILE_SIZE} );
        }
    }
}

bool Game::createMap()
{
    for(int i=0 ; i<3 ; i++){
        int random = rand() % total_map.size();
        random = i;
        Map mat(i*MAP_WIDTH*TILE_SIZE, total_map[random].path, tileSet, total_map[random].STT);
        list_map.push_back(mat);
    }
    if(list_map.size() < 3){
        cout << "Error load list map";
        return false;
    }
    return true;
}

bool Game::createPlayer()
{
    Player = new player(64, 320, tileSet);
    if(Player == NULL) return false;
    return true;
}

void Game::updateGame()
{
    updateMap();
    Player->updatePlayer(list_map);
    Player->changeCam(camera, list_map);
}

bool Game::updateMap()
{
    if(list_map.size() != 3){
        cout << "Error update map";
        return false;
    }

    if(camera.x >= list_map[2].getStart_x() - 1){
        list_map[0].clearMap();
        list_map.pop_front();

        int randomMap ;
        randomMap = rand()%total_map.size();
        while((total_map[randomMap].STT == list_map[0].getSTT()) || (total_map[randomMap].STT == list_map[1].getSTT())){
           randomMap = rand()%total_map.size();
        }
        cout << "Update Map number: " << randomMap << endl;

        Map mat(list_map[1].getStart_x() + TILE_SIZE*MAP_WIDTH, total_map[randomMap].path, tileSet, total_map[randomMap].STT );
        list_map.push_back(mat);
        return true;
    }
    return false;
}

void Game::render_Game()
{
    render_Map();
    Player->renderPlayer(camera);
}

void Game::render_Map()
{
    list_map[0].fillLeft(tileClip, camera);
    list_map[1].renderMap(tileClip, camera);
    list_map[2].fillRight(tileClip, camera);

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
