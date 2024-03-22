#include "gamefunc.h"

bool gamefunc::initWindow(){
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

SDL_Texture* gamefunc::loadTexture(string path)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, path.c_str());
    if(texture == NULL){
        cout << "Error load texture: " << SDL_GetError() << endl;
    }
    cout << "Success load texture: " << path << endl;
    return texture;
}

void gamefunc::renderTexture(SDL_Texture* img, SDL_Rect* rect1, SDL_Rect* rect2)
{
    SDL_RenderCopy(renderer, img, rect1, rect2);
}

void gamefunc::renderTexture(SDL_Texture* img, SDL_Rect* rect1, int x, int y, int w, int h)
{
    SDL_Rect rect2 = { x, y, w, h };
    SDL_RenderCopy(renderer, img, rect1, &rect2 );
}

void gamefunc::renderTextureFlip(SDL_Texture* img, SDL_Rect* rect1, SDL_Rect* rect2, SDL_RendererFlip flip )
{
    SDL_RenderCopyEx(renderer, img, rect1, rect2, 0, NULL, flip);
}

void gamefunc::renderPresent()
{
    SDL_RenderPresent(renderer);
}

void gamefunc::destroyTexture()
{
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
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

SDL_Texture* gamefunc::createText(string text, SDL_Color color)
{
    SDL_Texture* texture = NULL;
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

    if(textSurface == NULL) TTF_GetError();
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if(texture == NULL) SDL_GetError();
    SDL_FreeSurface( textSurface );
    return texture;
}
