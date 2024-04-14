#ifndef MONSTER_H
#define MONSTER_H

#include <bits/stdc++.h>
#include "gamefunc.h"
#include "Map.h"
#include "player.h"

class Map;
class player;

using namespace std;

class Monster : public Texture
{
public:
    Monster(const int& _x, const int& _y, SDL_Texture* image, Map& _map, int type);

    bool canMove(player& _Player);
    bool canMove();
    void touchPlayer(player& _Player);
    void autoMove(player& _Player);

    void updateMonster(player& _Player);
    void render(SDL_Rect& camera);

    int getStartMap() const {return mat.getStart_x();}
    int getDistance() const {return dist;}
    int getType() const {return type;}
    bool isAttack() const{return countHit >= 30;}
    bool isDead() const {return countDie >= 63;}

private:
    int mon_width = 58;
    int mon_height = 58;
    int mon_speed = 4;
    int hp, type, origin_x, dist;
    int x_vel = 0, y_vel = 0;
    Map mat;

    static const int WALK_FRAMES = 6;
    static const int FALL_FRAMES = 6;
    static const int ATTACK_FRAMES = 6;
    static const int HURT_FRAMES = 4;
    static const int DIE_FRAMES = 8;

    SDL_Rect animationWalk[WALK_FRAMES];
    SDL_Rect animationFall[FALL_FRAMES];
    SDL_Rect animationAttack[ATTACK_FRAMES];
    SDL_Rect animationHurt[HURT_FRAMES];
    SDL_Rect animationDie[DIE_FRAMES];

    int countWalk = 0, countFall = 0, countHit = 0, countHurt = 0, countDie = 0;
    bool walking = false, falling = false, grounded = true, attacking = false, hurting = false, die = false;
};

#endif // MONSTER_H
