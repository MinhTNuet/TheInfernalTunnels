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
        fall,
        attack,
        hurt,
        dead,
        idle,
        walk
    };
    player(int _x, int _y, SDL_Texture* image[]);
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
    bool checkAttack() const { return countHit == 26; }
    bool isDead() const { return countDead >= 7*6-1; }

private:
    int player_w = 48;
    int player_h = 55;
    int player_speed = 4;
    int hp = 3;
    int index_map_player = 0;
    int startX_map_player;
    int x_vel = 0, y_vel = 0;

    static const int WALKING_FRAMES = 8;
    static const int IDLING_FRAMES = 8;
    static const int JUMPING_FRAMES = 2;
    static const int FALLING_FRAMES = 2;
    static const int ATTACKING_FRAMES = 8;
    static const int HURTING_FRAMES = 3;
    static const int DIE_FRAMES = 7;

    SDL_Rect animationPlayer[8];
    SDL_Texture* p_texture[7];

    int countWalk = 0, countIdle = 0, countJump = 0, countFall = 0, countHit = 0, countHurt = 0, countDead = 0;
    bool idling = false, grounded = false, walking = false, jumping= false, falling = false, attacking = false, hurting = false, die = false ;
};

#endif // PLAYER_H
