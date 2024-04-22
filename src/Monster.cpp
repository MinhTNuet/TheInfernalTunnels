#include "Monster.h"

Monster::Monster(const int& _x, const int& _y, SDL_Texture* image, Map& _map, int _type) : Texture( _x, _y)
{
    origin_x = _x;
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

    if(type == 0)hp = 2;
    else if(type == 1)hp = 3;

}

void Monster::touchPlayer(player& _Player)
{
    attacking = false;
    if(getCollision().x < _Player.getCollision().x)x_vel = mon_speed;
    else if(getCollision().x > _Player.getCollision().x )x_vel = -mon_speed;
    else attacking = true;
}

void Monster::autoMove(player& _Player){
    dist = abs(getCollision().x - _Player.getCollision().x );

    if(_Player.getStartMap() != mat.getStart_x() || dist > 4*TILE_SIZE){
        if(attacking)attacking = false;
        if(x > origin_x && x-origin_x >= 3*TILE_SIZE)x_vel = -mon_speed/2;
        if(x < origin_x && origin_x-x >= 3*TILE_SIZE)x_vel = mon_speed/2;
    }
    else if(dist <= 4*TILE_SIZE){
        if(getCollision().x < _Player.getCollision().x)flip = SDL_FLIP_NONE;
        else flip = SDL_FLIP_HORIZONTAL;

        if(abs(y - _Player.getY()) > 20){
            if(x_vel == 0) touchPlayer(_Player);
            attacking = false;
            if(dist >= 96){
                if(getCollision().x > _Player.getCollision().x)x_vel = -mon_speed;
                else x_vel = mon_speed;
            }
        }
        else if(!hurting){
            if(dist <= 40){
                x_vel = 0;
                attacking = true;
            }
            else touchPlayer(_Player);
        }
    }
}

void Monster::updateMonster(player& _Player)
{
    if((hp <= 0 && !falling) || y > 64*MAP_HEIGHT){
        die = true;
        walking = false;
        attacking = false;
        return;
    }
    if(!die){
        if(x_vel != 0 && grounded)walking = true;
        else walking = false;
        if(y_vel >= 0 && !grounded)falling = true;
        else falling = false;

        if(gamefunc::checkCollision(getCollision(), _Player.getCollision()) && _Player.checkAttack() && flip != _Player.getFlip()){
            hurting = true;
            attacking = false;
        }
    }

    autoMove(_Player);

    if(hurting && countHurt == 0){
        y_vel -= 8;
        if(getCollision().x < _Player.getCollision().x)x_vel = -4;
        else x_vel = 4;
    }

    if(x_vel < 0 && !hurting) flip = SDL_FLIP_HORIZONTAL;
    else if(x_vel > 0 && !hurting) flip = SDL_FLIP_NONE;

    if(!falling)x += x_vel;
    collision.x = x - mat.getStart_x();
    if(gamefunc::checkWall(getCollision(), mat) || x>=mat.getStart_x()+64*MAP_WIDTH || x<=mat.getStart_x() ){
        x -= x_vel;
        origin_x = x - 3*x_vel/abs(x_vel)*TILE_SIZE;
        x_vel *= -1;
        collision.x = x - mat.getStart_x();
    }

    y_vel += force;
    y += y_vel;
    collision.y = y;
    if(gamefunc::checkWall(getCollision(), mat, &grounded)){
        if(y_vel > 0 && falling) grounded = true;
        y -= y_vel;
        y_vel = 0;
        collision.y = y;
    }
}

void Monster::render(SDL_Rect& camera)
{
    SDL_Rect des = {x - camera.x-10, y - camera.y-16, 64, 64};

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
