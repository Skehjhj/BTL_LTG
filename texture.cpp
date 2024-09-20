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
void TextureManager::draw(SDL_Texture* texture, SDL_Rect dest){
    SDL_RenderCopy(Game::renderer, texture, NULL, &dest);
}
SDL_Texture* TextureManager::renderText(const string &message, const string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer)
{        //Open Font File
        TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
        if(!font){
            cout << "TTF_OpenFont error";
            return nullptr;
        }

        //We need to render text to a surface using TTF_RenderText_Blended
        SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
        if(!surface){
            cout << "TTF_RenderText error";
            return nullptr;
        }

        // Then from returned surface, we create a texture using that surface
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if(!texture){
            cout << "CreateTextureFromSurface error";
        }

        //Clean up and return;
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return texture;
}