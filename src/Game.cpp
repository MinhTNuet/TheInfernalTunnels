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

    tileSet = gamefunc::loadTextureFromFile("src/anhtest.jpg");
    p_texture[0] = gamefunc::loadTextureFromFile("src/Jump.png");
    p_texture[1] = gamefunc::loadTextureFromFile("src/Run.png");
    p_texture[2] = gamefunc::loadTextureFromFile("src/Fall.png");

    return true;

}

void Game::setTileClip()
{
    tileClip.push_back({0, 0, 0, 0});

    for(int i=0; i<13; i++){
        for(int j=0; j<20; j++){
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
    Player = new player( 64, 128, tileSet);
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
    mat = new Map(0, "map1.txt", tileSet);
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
