#include "Texture.h"

Texture::Texture(int _x, int _y, SDL_Texture* img)
{
    x = _x;
    y = _y;
    texture = img;
}

SDL_Texture* Texture::getTexture() const
{
    return texture;
}

int Texture::getX() const
{
    return x;
}

int Texture::getY() const
{
    return y;
}
