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
    p_texture[1] = gamefunc::loadTextureFromFile("image/player/Sprites/Fall.png");
    p_texture[2] = gamefunc::loadTextureFromFile("image/player/Sprites/Attack.png");
    p_texture[3] = gamefunc::loadTextureFromFile("image/player/Sprites/Hurt.png");
    p_texture[4] = gamefunc::loadTextureFromFile("image/player/Sprites/Death.png");
    p_texture[5] = gamefunc::loadTextureFromFile("image/player/Sprites/Idle.png");
    p_texture[6] = gamefunc::loadTextureFromFile("image/player/Sprites/Walking.png");

    monsterTex[0] = gamefunc::loadTextureFromFile( "image/mon1/Mon1.png");
    monsterTex[1] = gamefunc::loadTextureFromFile( "image/mon2/Mon2.png");
    return check;
}

bool Game::loadMap()
{
    map_enemy map1("image/Map/map1.txt", {300}, 1);
    total_map.push_back(map1);
    map_enemy map2("image/Map/map2.txt", {300}, 2);
    total_map.push_back(map2);
    map_enemy map3("image/Map/map3.txt", {300}, 3);
    total_map.push_back(map3);
    map_enemy map4("image/Map/map4.txt", {300}, 4);
    total_map.push_back(map4);
    map_enemy map5("image/Map/map5.txt", {300}, 5);
    total_map.push_back(map5);
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
    for(int i=0; i<3; i++){
        int random = rand() % total_map.size();
        random = i;
        Map mat(i*MAP_WIDTH*TILE_SIZE, total_map[random].path, tileSet, total_map[random].STT);
        mat.setMonsterList(total_map[random].monster_pos);
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
    Player = new player(64, 500, p_texture);
    if(Player == NULL) return false;
    return true;
}

bool Game::createMonster()
{
    for(int i=0; i<list_map.size(); i++){
        for(int j=0; j<list_map[i].getMonsterList().size(); j++){
            int random = rand() % 3;
            Monster* mon = new Monster((list_map[i].getMonsterList()[j]%MAP_WIDTH)*TILE_SIZE + list_map[i].getStart_x(), (list_map[i].getMonsterList()[j]/MAP_WIDTH)*TILE_SIZE, monsterTex[random], list_map[i], random );
            monsterList.push_back(mon);
        }
    }
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

        int randomMap;
        randomMap = rand()%total_map.size();
        while((total_map[randomMap].STT == list_map[0].getSTT()) || (total_map[randomMap].STT == list_map[1].getSTT())){
           randomMap = rand()%total_map.size();
        }

        Map mat(list_map[1].getStart_x() + TILE_SIZE*MAP_WIDTH, total_map[randomMap].path, tileSet, total_map[randomMap].STT );
        list_map.push_back(mat);
        return true;
    }
    return false;
}


void Game::render_Game()
{
    render_Map();
    render_Monster();
    Player->renderPlayer(camera);
}

void Game::render_Map()
{
    list_map[0].fillLeft(tileClip, camera);
    list_map[1].renderMap(tileClip, camera);
    list_map[2].fillRight(tileClip, camera);

}

void Game::render_Monster()
{
    for(int i=0; i<monsterList.size(); i++){
        if(monsterList[i] != NULL){
            monsterList[i]->render(camera);
        }
    }
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
