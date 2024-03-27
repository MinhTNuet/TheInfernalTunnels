#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>

using namespace std;

class Texture
{
    protected:
        int x, y;
        SDL_Texture* texture;
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        SDL_Rect collision;

    public:
        Texture(int _x = 0, int _y = 0, SDL_Texture* img = NULL);
        SDL_Texture* getTexture() const;
        int getX() const;
        int getY() const;
        SDL_RendererFlip getFlip() const {return flip;}
        SDL_Rect getCollision() const {return collision;}
};

#endif // TEXTURE_H
