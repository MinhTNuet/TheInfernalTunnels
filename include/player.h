#ifndef PLAYER_H
#define PLAYER_H

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>
#include "gamefunc.h"

class Map;

using namespace std;

class player : public Texture
{
public:
    enum status{
        jump,
        run,
        fall,
        attack,
        death,
        idle,
        hurt
    };
    player(int _x, int _y, SDL_Texture* image);
    void updatePlayer(deque <Map>& list_map);

    void handleEvent(SDL_Event &e);
    void handleStatus();

    void handleCollision(deque <Map>& list_map);

    void Jump();
    void buffhp() {if(hp<3) hp++;}

    void mapPresent(deque <Map>& list_map);
    void changeCam(SDL_Rect &camera, deque <Map>& list_map);
    void renderPlayer(SDL_Rect &camera);
    void resetplayer();

    int getStartMap() const {return startX_map_player;}
    int gethp() const {return hp;}

private:
    int player_w = 48;
    int player_h = 56;
    int player_speed = 3;
    int hp = 3;
    int index_map_player = 0;
    int startX_map_player;
    int x_vel = 0, y_vel = 0;

    SDL_Texture* p_texture;

    bool idling = false, grounded = false, walking = false, jumping= false, falling = false, attacking = false, hurting = false, die = false ;
};

#endif // PLAYER_H
