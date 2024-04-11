#include "Monster.h"

Monster::Monster(const int& _x, const int& _y, SDL_Texture* image, Map& _map, int _type) : Texture( _x, _y)
{
    origin_x = _x ;
    x_vel = mon_speed/2;
    type = _type;

    texture = image;
    mat = _map;
    collision = {x, y+16, mon_width, mon_height};

    for(int i=0; i<WALK_FRAMES; i++){
        animationWalk[i] = {i*32, 0, 32, 32};
    }
    for(int i=0; i<FALL_FRAMES; i++){
        animationFall[i] = {i*32, 32, 32, 32};
    }
    for(int i=0; i<HURT_FRAMES; i++){
        animationHurt[i] = {i*32, 96, 32, 32};
    }
    for(int i=0; i<ATTACK_FRAMES; i++){
        animationAttack[i] = {i*32, 64, 32, 32};
    }
    for(int i=0 ; i<DIE_FRAMES; i++){
        if(i<2) animationDie[i] = {i*32 + 128, 96, 32, 32};
        else animationDie[i] = {i*32 - 64, 128, 32, 32};
    }

    if(type == 0)hp = 3;
    else if(type == 1)hp = 5;
    else hp = 2;

}

void Monster::render(SDL_Rect& camera)
{
    SDL_Rect des = {x - camera.x, y - camera.y, 64, 64};

    if(walking){
        if((countWalk+1)/6 >= WALK_FRAMES)countWalk = 0;
        countWalk++;
        gamefunc::renderTextureFlip(texture, &animationWalk[countWalk/6], &des, flip );
    }
    else countWalk=0;

    if(falling){
        if((countFall+1)/6 >= FALL_FRAMES)countFall = 0;
        countFall++;
        gamefunc::renderTextureFlip(texture, &animationFall[countFall/6], &des, flip);
    }
    else countFall = 0;

    if(attacking){
        if((countHit+1)/6 >= ATTACK_FRAMES)countHit = 0;
        countHit++;
        gamefunc::renderTextureFlip(texture, &animationAttack[countHit/6], &des, flip);
    }
    else countHit = 0;

    if(hurting){
        if((countHurt+1)/6 >= HURT_FRAMES){
            hurting = false;
            hp--;
        }
        countHurt++;
        gamefunc::renderTextureFlip(texture, &animationHurt[countHurt/6], &des, flip);
    }
    else countHurt = 0;

    if(die){
        if((countDie+1)/8 >= DIE_FRAMES) return;
        countDie++;
        gamefunc::renderTextureFlip(texture, &animationDie[countDie/8], &des, flip);
    }
    else countDie = 0;
}
