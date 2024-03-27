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
            run,
            jump
        };
        player(int _x, int _y);

        void handleEvent(SDL_Event &e);
        void handleStatus();

        void handleCollision(Map mat);

        void Jump();
        void buffhp() {if(hp<3) hp++;}

        void changeCam(SDL_Rect &camera, Map mat);
        void resetplayer();



    private:
        int player_w = 48;
        int player_h = 56;
        int player_speed = 4;
        int hp = 3;
        int index_map_player = 0;
        int startX_map_player;
        int x_vel = 0, y_vel = 0;

        bool idling = false;
        bool grounded = false;
        bool walking = false;
        bool jumping= false;
        bool falling = false;
        bool attacking = false;
        bool hurting = false;
        bool die = false ;
};

#endif // PLAYER_H
