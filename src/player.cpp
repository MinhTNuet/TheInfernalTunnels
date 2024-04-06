#include "player.h"

player::player(int _x, int _y, SDL_Texture* image) : Texture(_x, _y)
{
    collision = {_x, _y, player_w, player_h};
    p_texture = image;
}

void player::updatePlayer(deque <Map>& list_map)
{
    mapPresent(list_map);
    handleCollision(list_map);
}

void player::handleEvent(SDL_Event &e)
{
    cout<<x_vel<<" "<<y_vel<<endl;
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
void player::handleCollision(deque <Map>& list_map)
{
    x += x_vel;
    collision.x = x - list_map[index_map_player].getStart_x();
    if(gamefunc::checkWall(getCollision(), list_map[index_map_player]) || x<list_map[0].getStart_x()) {
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
        if(y_vel > 0){
            grounded = true;
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


void player::Jump()
{
    if(grounded){
        y_vel = -25;
        jumping = true;
    }
}

void player::mapPresent(deque <Map>& list_map)
{
    if(getCollision().x >= MAP_WIDTH*64 && index_map_player<2 ){
        index_map_player++;
    }
    else if(getCollision().x < 0 && index_map_player>0 ){
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


    float smooth = 0.1;
    camera.x = lerp(camera.x, cam_target_x, smooth);
    camera.y = lerp(camera.y, cam_target_y, smooth);
}

void player::renderPlayer(SDL_Rect &camera)
{
    SDL_Rect str = {x - camera.x, y - camera.y, 64, 64};
    SDL_Rect des = {0, 0, 64, 64};
    gamefunc::renderTexture(p_texture, &des, &str);
}

void player::resetplayer()
{
    die = false;
    x = 64;
    y = 320;
    y_vel = 0;
    hp = 3;
}
