#include "player.h"

player::player(int _x, int _y, SDL_Texture* image[], Mix_Chunk* sound[]) : Texture(_x, _y)
{
    collision = {_x, _y, player_w, player_h};
    p_texture[jump] = image[jump];
    p_texture[fall] = image[fall];
    p_texture[attack] = image[attack];
    p_texture[hurt] = image[hurt];
    p_texture[dead] = image[dead];
    p_texture[idle] = image[idle];
    p_texture[walk] = image[walk];

    p_sound[attack] = sound[attack];
    p_sound[jump] = sound[jump];
    p_sound[fall] = sound[fall];
    p_sound[hurt] = sound[hurt];
    p_sound[dead] = sound[dead];

    for(int i=0 ; i<8; i++){
        animationPlayer[i] = {i*250, 0, 250, 250};
    }
}

void player::updatePlayer(deque <Map>& list_map, vector<Monster*>& monsterList)
{
    mapPresent(list_map);

    if(!die){
        handleStatus();
        takeDamage(monsterList);
        handleCollision(list_map);
    }

    if(y > MAP_HEIGHT*64 +128 && !die){
        die = true;
        countDead = 6*24;
//        Mix_PlayChannel(-1, p_sound[dead], 0);
    }

}

void player::handleEvent(SDL_Event &e)
{

    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch(e.key.keysym.sym){
        case SDLK_d:
            x_vel += player_speed;
            break;
        case SDLK_a:
            x_vel -= player_speed;
            break;
        case SDLK_w:
            Jump();
            grounded = false;
            break;
        case SDLK_SPACE:
            if(!hurting && !die) {
                attacking = true;
//                Mix_PlayChannel(-1, p_sound[attack], 0);

            }
            break;
        }
    }
    if(e.type == SDL_KEYUP && e.key.repeat == 0 && x_vel != 0){
        switch(e.key.keysym.sym){
        case SDLK_d:
            x_vel -= player_speed;
            break;
        case SDLK_a:
            x_vel += player_speed;
            break;
        }
    }
}

void player::handleStatus()
{
    if(hp <= 0 && !hurting){
        die = true;
    }

    if(!die && !attacking && !hurting && grounded && x_vel != 0) walking = true;
    else walking = false;
    if(!die && !hurting && grounded && x_vel == 0) idling = true;
    else idling = false;
    if(!die && !hurting && !grounded && y_vel >= 0) falling = true;
    else falling = false;
    if(!die && !hurting && !grounded && y_vel < 0) jumping = true;
    else jumping = false;

    if(hurting)attacking = false;

    if(x_vel < 0)flip = SDL_FLIP_HORIZONTAL;
    else if(x_vel > 0)flip = SDL_FLIP_NONE;
}

void player::handleCollision(deque <Map>& list_map)
{
    x += x_vel;
    collision.x = x - list_map[index_map_player].getStart_x();
    if(gamefunc::checkWall(getCollision(), list_map[index_map_player]) || (attacking && grounded) || x<list_map[0].getStart_x()) {
        x -= x_vel;
        collision.x = getX() - list_map[index_map_player].getStart_x();
    } else if(getCollision().x + getCollision().w >= 64*MAP_WIDTH){
        if(gamefunc::checkWall(getCollision(), list_map[index_map_player], list_map[index_map_player + 1])){
            x -= x_vel;
            collision.x = x - list_map[index_map_player].getStart_x();
        }
    }

    y_vel += force;
    y += y_vel;
    collision.y = y;
    if(gamefunc::checkWall(getCollision(), list_map[index_map_player], &grounded)){
        if(y_vel > 0 && falling){
            grounded = true;
//            Mix_PlayChannel(-1, p_sound[fall], 0);
        }
        y -= y_vel;
        y_vel = 0;
        collision.y = y;
    }
    if(getCollision().x + getCollision().w >= 64*MAP_WIDTH){
        if(gamefunc::checkWall(getCollision(), list_map[index_map_player], list_map[index_map_player+1], &grounded)){
            y -= y_vel;
            y_vel = 0;
            collision.y = y;
        }
    }
}

void player::takeDamage(vector<Monster*>& monsterList)
{
    for(int i=0; i<monsterList.size(); i++){
        if(monsterList[i]->getStartMap() == getStartMap() && monsterList[i] != NULL){
            if(monsterList[i]->getDistance() <= TILE_SIZE && monsterList[i]->isAttack() && !hurting){
                hurting = true;
                y_vel = -6;
                hp--;
//                Mix_PlayChannel(-1, p_sound[hurt], 0);
            }
        }
    }
}

void player::Jump()
{
    if(grounded){
        y_vel = -20;
        jumping = true;
//        Mix_PlayChannel(-1, p_sound[jump], 0);
    }
}

void player::mapPresent(deque <Map>& list_map)
{
    if(getCollision().x >= MAP_WIDTH*64 && index_map_player<2){
        index_map_player++;
    }
    else if(getCollision().x < 0 && index_map_player>0){
        index_map_player--;
    }
    startX_map_player = list_map[index_map_player].getStart_x();
}

int lerp(int a, int b, float t)
{
    return (1-t)*a + t*b;
}

void player::changeCam(SDL_Rect &camera, deque <Map>& list_map)
{
    int cam_target_x = x - (float)1/2 * SCREEN_WIDTH;
    int cam_target_y = y - (float)1/3 * SCREEN_HEIGHT;

    if(cam_target_x < list_map[index_map_player].getStart_x() && index_map_player == 0){
        cam_target_x = list_map[index_map_player].getStart_x();
    }

    if(cam_target_y < 0.5*TILE_SIZE){
        cam_target_y = 0.5*TILE_SIZE;
    } else if(cam_target_y > 64*MAP_HEIGHT - SCREEN_HEIGHT - 0.5*TILE_SIZE){
        cam_target_y = 64*MAP_HEIGHT - SCREEN_HEIGHT - 0.5*TILE_SIZE;
    }

    if(hurting && countHurt < 18){
        cam_target_x += rand() % 51 - 25;
        cam_target_y += rand() % 51 - 25;
    }

    float smooth = 0.1;
    camera.x = lerp(camera.x, cam_target_x, smooth);
    camera.y = lerp(camera.y, cam_target_y, smooth);
}

void player::renderPlayer(SDL_Rect &camera)
{
    SDL_Rect str = {x - camera.x-110, y - camera.y -110, 250, 250};
    if(attacking){
        if((countHit+2)/6>= ATTACKING_FRAMES)attacking = false;
        countHit++;
        gamefunc::renderTextureFlip(p_texture[attack], &animationPlayer[countHit/6], &str, flip);
    }
    else{
        countHit = 0;
        if(hurting){
            if((countHurt+2)/4 >= HURTING_FRAMES)hurting = false;
            countHurt++;
            gamefunc::renderTextureFlip(p_texture[hurt], &animationPlayer[countHurt/4], &str, flip);
        }
        else countHurt = 0;

        if(jumping){
            if((countJump+1)/6 >= JUMPING_FRAMES)countJump = 0;
            countJump++;
            gamefunc::renderTextureFlip(p_texture[jump], &animationPlayer[countJump/6], &str, flip);
        }
        else countJump = 0;

        if(falling){
            if((countFall+1)/6 >= FALLING_FRAMES)countFall = 0;
            countFall++;
            gamefunc::renderTextureFlip(p_texture[fall], &animationPlayer[countFall/6], &str, flip);
        }
        else countFall = 0;

        if(walking){
            if((countWalk+1)/6 >= WALKING_FRAMES)countWalk = 0;
            countWalk++;
            gamefunc::renderTextureFlip(p_texture[walk], &animationPlayer[countWalk/6], &str, flip);
        }
        else countWalk = 0;

        if(idling){
            if((countIdle+1)/8 >= IDLING_FRAMES)countIdle = 0;
            countIdle++;
            gamefunc::renderTextureFlip(p_texture[idle], &animationPlayer[countIdle/8], &str, flip);
        }
        else countIdle = 0;

        if(die){
            if((countDead+1)/6 >= DIE_FRAMES )Mix_HaltChannel( -1 );
            countDead++;
            gamefunc::renderTextureFlip(p_texture[dead], &animationPlayer[countDead/6], &str, flip);
        }
        else countDead = 0;

    }

}

bool player::overTime()
{
    die = true;
    idling = false;
    walking = false;
    jumping= false;
    falling = false;
    attacking = false;
    hurting = false;
}

void player::resetplayer()
{
    die = false;
    x = 40;
    y = 500;
    y_vel = 0;
    hp = 3;
}
