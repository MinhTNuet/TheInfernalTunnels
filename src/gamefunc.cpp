#include "gamefunc.h"

bool gamefunc::initWindow()
{
    window = SDL_CreateWindow( "The Infernal Tunnels", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL){
        cout << "Error init Window: " << SDL_GetError() << endl;
        return false;
    }
    else {
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        if(renderer == NULL){
            cout << "Error init Renderer: " << SDL_GetError() << endl;
            return false;
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
        }
    }
    return true;
}

void gamefunc::clearRender()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void gamefunc::setRender()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

}

SDL_Texture* gamefunc::loadTextureFromFile(string path)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
    if (texture == NULL) {
        cout << "Error loading texture from file: " << SDL_GetError() << endl;
    } else {
        cout << "Successfully loaded texture from file: " << path << endl;
    }
    return texture;
}

void gamefunc::renderTexture(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* des)
{
    SDL_RenderCopy(renderer, texture, src, des);
}

void gamefunc::renderTexture(SDL_Texture* texture, SDL_Rect* src, int _x, int _y, int _w, int _h)
{
    SDL_Rect des = {_x, _y, _w, _h};
    SDL_RenderCopy(renderer, texture, src, &des);
}

void gamefunc::renderTextureFlip(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* des, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(renderer, texture, src, des, 0, NULL, flip);
}

void gamefunc::renderPresent()
{
    SDL_RenderPresent(renderer);
}

void gamefunc::destroyTexture()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
}

bool gamefunc::initFont( const char* path )
{
	TTF_CloseFont(font);
	font = TTF_OpenFont(path, 24);
	if (font == NULL) {
		cout << "Error init font: " << TTF_GetError();
		return false;
	}
	return true;
}

SDL_Texture* gamefunc::createTextTexture(string text, SDL_Color color)
{
    SDL_Texture* texture = NULL;
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

    if(textSurface == NULL) TTF_GetError();
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if(texture == NULL) SDL_GetError();
    SDL_FreeSurface(textSurface);
    return texture;
}

void gamefunc::renderQuit()
{
    clearRender();
    destroyTexture();
}
