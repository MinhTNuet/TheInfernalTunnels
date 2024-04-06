#include "gamefunc.h"

bool gamefunc::initWindow()
{
    window = SDL_CreateWindow("The Infernal Tunnels", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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



SDL_Texture* gamefunc::loadTextureFromFile(string path)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, path.c_str());
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

bool gamefunc::checkCollision(SDL_Rect obj1, SDL_Rect obj2)
{
    if(obj1.x + obj1.w < obj2.x) return false;
    if(obj2.x + obj2.w < obj1.x) return false;
    if(obj1.y + obj1.h < obj2.y) return false;
    if(obj2.y + obj2.h < obj1.y) return false;
    return true;
}

bool gamefunc::checkWall(SDL_Rect obj, Map mat, bool* grounded)
{
    int a = obj.x / TILE_SIZE;
    int b = a + 1;
    int c = obj.y / TILE_SIZE;
    int d = c + 1;

    if(d >= MAP_HEIGHT)return false;

    if(grounded != NULL){
        if(mat.getDataMap(a,d).getType() > 132 && mat.getDataMap(b,d).getType() > 132) *grounded = false;
        else if(mat.getDataMap(a,d).getType() > 132 && obj.x + obj.w < mat.getDataMap(b,d).getX()) * grounded = false;

    }

    if(mat.getDataMap(a,c).getType() < 132){
        if(gamefunc::checkCollision(obj, mat.getDataMap(a,c).getCollision()))return true;
    }
    if(mat.getDataMap(b,c).getType() < 132){
        if(gamefunc::checkCollision(obj, mat.getDataMap(b,c).getCollision()))return true;
    }
    if(mat.getDataMap(a,d).getType() < 132){
        if(gamefunc::checkCollision(obj, mat.getDataMap(a,d).getCollision()))return true;
    }
    if(mat.getDataMap(b,d).getType() < 132){
        if(gamefunc::checkCollision(obj, mat.getDataMap(b,d).getCollision()))return true;
    }
    return false;
}

bool gamefunc::checkWall(SDL_Rect obj, Map map1, Map map2, bool* grounded)
{
    bool check = false;
    int a = MAP_WIDTH-1;
    int b = 0;
    int c = obj.y/TILE_SIZE;
    int d = c + 1;

    if(d >= MAP_HEIGHT) return false;

    if(grounded != NULL){
        if(map1.getDataMap(a, d).getType() > 132 && map2.getDataMap(b, d).getType() > 132 && grounded != NULL) *grounded = false;
        else if(map1.getDataMap(a, d).getType() > 132 && obj.x+obj.w <= map2.getDataMap(b, d).getX()) *grounded = false;
    }

    if(map1.getDataMap(a, c).getType() < 132){
        if(gamefunc::checkCollision( obj, map1.getDataMap(a, c).getCollision())) return true;
    }
    if(map1.getDataMap(a, d).getType() < 132){
        if(gamefunc::checkCollision( obj, map1.getDataMap(a, d).getCollision())) return true;
    }

    obj.x -= 64*MAP_WIDTH;
    if(map2.getDataMap(b, c).getType() < 132){
        if(gamefunc::checkCollision(obj, map2.getDataMap(b, c).getCollision())) check = true;
    }
    if(map2.getDataMap(b, d).getType() < 132){
        if(gamefunc::checkCollision(obj, map2.getDataMap(b, d).getCollision())) check = true;
    }

    return check;
}

void gamefunc::setWindowFS()
{
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}

void gamefunc::quitWindowFS()
{
    SDL_SetWindowFullscreen(window, 0);
}

void gamefunc::renderQuit()
{
    clearRender();
    destroyTexture();
}
