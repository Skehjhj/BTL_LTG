#include <texture.h>

SDL_Texture* TextureManager::loadTexture(const char* fileName){
    // SDL_Surface* surface = IMG_Load(fileName);
    // SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    // SDL_FreeSurface(surface);
    SDL_Texture* texture = IMG_LoadTexture(Game::renderer, fileName);
    return texture;
};

void TextureManager::draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest){
    SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}