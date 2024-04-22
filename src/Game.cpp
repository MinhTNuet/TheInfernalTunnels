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

    monsterTex[0] = gamefunc::loadTextureFromFile("image/mon1/Mon1.png");
    monsterTex[1] = gamefunc::loadTextureFromFile("image/mon2/Mon2.png");

    liveBar = gamefunc::loadTextureFromFile("image/LiveBar.png");
    heart = gamefunc::loadTextureFromFile("image/heart.png");
    hp_pos = {{20, 20, 36, 28}, {44, 20, 36, 28}, {68, 20, 36, 28}};

    p_sound[0] = Mix_LoadWAV("music/sound_Jump.wav");
    p_sound[1] = Mix_LoadWAV("music/sound_Fall.wav");
    p_sound[2] = Mix_LoadWAV("music/sound_Attack.wav");
    p_sound[3] = Mix_LoadWAV("music/sound_Hurt.wav");
    p_sound[4] = Mix_LoadWAV("music/sound_Death.wav");
    for(int i=0; i<5; i++){
        if(p_sound[i] != NULL){
            cout<<"Load success file p_sound: "<< i << endl;
            check = false;
        }else cout<<"Error load file p_sound: "<< i << endl;
    }

    menuTex[0] = gamefunc::loadTextureFromFile("image/button_and_background/background_menu.png");
    menuTex[1] = gamefunc::loadTextureFromFile("image/button_and_background/play01.png");
    menuTex[2] = gamefunc::loadTextureFromFile("image/button_and_background/back01.png");
    menuTex[3] = gamefunc::loadTextureFromFile("image/button_and_background/background_end.png");
    menuTex[4] = gamefunc::loadTextureFromFile("image/button_and_background/restart01.png");

    menuSound[0] = Mix_LoadWAV("music/sound_menu_select.wav" );
    menuSound[1] = Mix_LoadWAV("music/sound_menu_click.wav" );
    for(int i=0; i<2; i++){
        if(menuSound[i] != NULL){
            cout<<"Load success file menu sound: "<< i << endl;
            check = true;
        }else {cout<<"Error load file menu sound: "<< i << endl;check = false;}
    }

    menu = new Menu(menuTex, menuSound);
    if( menu == NULL ){
        cout << "Error init Menu" << endl;
        check = false;
    }

    gamefunc::initFont("image/font.ttf");
    getHighScore();
    return check;
}

bool Game::loadMap()
{
    map_enemy map1("image/Map/map1.txt", {322, 328}, 1);
    total_map.push_back(map1);
    map_enemy map2("image/Map/map2.txt", {387, 283, 254}, 2);
    total_map.push_back(map2);
    map_enemy map3("image/Map/map3.txt", {159, 162, 244, 481, 533}, 3);
    total_map.push_back(map3);
//    map_enemy map4("image/Map/map4.txt", {424, 513, 537}, 4);
//    total_map.push_back(map4);
//    map_enemy map5("image/Map/map5.txt", {69}, 5);
//    total_map.push_back(map5);
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
    Player = new player(40, 500, p_texture, p_sound);
    if(Player == NULL) return false;
    return true;
}

bool Game::createMonster()
{
    for(int i=0; i<list_map.size(); i++){
        for(int j=0; j<list_map[i].getMonsterList().size(); j++){
            int random = rand() % 2;
            Monster* mon = new Monster((list_map[i].getMonsterList()[j]%MAP_WIDTH)*TILE_SIZE + list_map[i].getStart_x(), (list_map[i].getMonsterList()[j]/MAP_WIDTH)*TILE_SIZE, monsterTex[random], list_map[i], random);
            monsterList.push_back(mon);
        }
    }
    return true;
}

void Game::updateGame()
{
    if(updateMap()){
        for(int j=0; j<list_map[2].getMonsterList().size(); j++){
            int random = rand() % 2;
            Monster* mon = new Monster((list_map[2].getMonsterList()[j]%MAP_WIDTH)*TILE_SIZE + list_map[2].getStart_x(), (list_map[2].getMonsterList()[j]/MAP_WIDTH)*TILE_SIZE, monsterTex[random], list_map[2], random);
            monsterList.push_back(mon);
        }
    }
    Player->updatePlayer(list_map, monsterList);
    Player->changeCam(camera, list_map);
    updateMonster();
    if(Player->isDead())setHighScore();
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
        mat.setMonsterList(total_map[randomMap].monster_pos);
        list_map.push_back(mat);
        return true;
    }
    return false;
}

void Game::updateMonster()
{
    for(int i=0 ; i<monsterList.size() ; i++){
        if(monsterList[i] != NULL){
            monsterList[i]->updateMonster(*Player);
            if(monsterList[i]->isDead()){
                if(monsterList[i]->getType() == 0){
                    Player->buffhp();
                    scoreMonster += 5;
                }
                else if(monsterList[i]->getType() == 1) scoreMonster += 30;
                delete monsterList[i];
                monsterList[i] = NULL;
                monsterList.erase(monsterList.begin() + i);
                i--;
            }
        }
    }
}

void Game::getHighScore()
{
    string temp;
    fstream high("image/HighScore.txt", fstream::in);
    high >> temp;
    highScore = stoi(temp);
}

void Game::setHighScore()
{
    totalScore = scoreMonster + scoreRun;
    if(totalScore >= highScore){
        fstream high("image/HighScore.txt", fstream::out | fstream::trunc);
        high << highScore;
    }
}

void Game::render_Game()
{
    render_Map();
    render_Monster();
    Player->renderPlayer(camera);
    render_hp_Score();
    render_time();
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

void Game::render_hp_Score()
{
    scoreRun = max(scoreRun, Player->getX()/TILE_SIZE);
    totalScore = scoreRun + scoreMonster;
    highScore = max(highScore, totalScore);

    SDL_Texture* scoreTex = gamefunc::createTextTexture("Score: " + to_string(totalScore), {0, 0, 0, 255} );
    SDL_Texture* highScoreTex = gamefunc::createTextTexture("High Score: " + to_string(highScore), {255, 0, 0, 255});

    int *w = new int, *h = new int;
    SDL_QueryTexture(scoreTex, NULL, NULL, w, h);
    gamefunc::renderTexture(scoreTex, NULL, SCREEN_WIDTH - *w - 10, 10, *w, *h);

    SDL_QueryTexture(highScoreTex, NULL, NULL, w, h);
    gamefunc::renderTexture(highScoreTex, NULL, SCREEN_WIDTH - *w - 10, 35, *w, *h);

    delete w, h;
    SDL_DestroyTexture(scoreTex);
    SDL_DestroyTexture(highScoreTex);

    gamefunc::renderTexture(liveBar, NULL, 0, 0, 132, 68);
    for(int i=0; i<Player->gethp(); i++){
        gamefunc::renderTexture(heart, NULL, &hp_pos[i]);
    }
}

void Game::resetGame()
{
    while(!monsterList.empty()){
        delete monsterList[0];
        monsterList[0] = NULL;
        monsterList.erase(monsterList.begin());
    }
    for(int i=0; i<list_map.size(); i++){
        list_map[i].clearMap();
    }
    if(!list_map.empty())list_map.clear();
    if(!createMap())cout << "Error reset list Map";
    if(!createMonster())cout << "Error reset Monster";
    time->resetToMax();
    Player->resetplayer();
    camera.x = 0;
    camera.y = 0;
    setHighScore();
    scoreMonster = 0;
    scoreRun = 0;
    totalScore = 0;
    getHighScore();
}

void Game::handleInputGame(SDL_Event &e)
{
    if(e.type == SDL_QUIT)gamefunc::renderQuit();
    menu->handleInputMenu(e, *Player, runningGame);
    if(!menu->isRunning()){
        Player->handleEvent(e);
    }
}

bool Game::createTimer()
{
    time = new Timer(62.0f, 62.0f);
    if(time == NULL) return false;
    return true;
}

void Game::render_time()
 {
    float timeRemaining = time->getTimeRemaining();
    string timeString = to_string((int)timeRemaining) + "s";
    SDL_Texture* timeStringTex = gamefunc::createTextTexture("Time remaining: " + timeString, {255, 255, 255, 255});

    int *w = new int, *h = new int;
    SDL_QueryTexture(timeStringTex, NULL, NULL, w, h);
    gamefunc::renderTexture(timeStringTex, NULL, SCREEN_WIDTH - *w - 10, 60, *w, *h);
    delete w, h;
    SDL_DestroyTexture(timeStringTex);
}

void Game::countDownTime()
{
    static Uint32 lastFrameTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastFrameTime) / 1000.0f;
    lastFrameTime = currentTime;
    time->countDown(deltaTime);
    if(time->timeSIsZero()){
        Player->overTime();
    }

}

void Game::runGame(SDL_Event &e)
{
    if(!menu->isMenu()){
        if(!menu->isEnd()){
            countDownTime();
            updateGame();
        }
        render_Game();
        if(menu->isEnd())menu->renderEndMenuScreen(totalScore);
    } else if(runningGame){
        runningGame = false;
        resetGame();
    }
    handleInputGame(e);
    if(menu->isRestart())resetGame();
    gamefunc::renderPresent();
}

void Game::clearMedia()
{
    SDL_DestroyTexture(tileSet);
    SDL_DestroyTexture(liveBar);
    SDL_DestroyTexture(heart);
    for(int i=0; i<7; i++)SDL_DestroyTexture(p_texture[i]);
    for(int i=0; i<2; i++)SDL_DestroyTexture(monsterTex[i]);
    for(int i=0; i<5; i++)SDL_DestroyTexture(menuTex[i]);
    TTF_CloseFont(font);
    delete time;
}
