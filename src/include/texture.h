#ifndef texture_H
#define texture_H
#include <game.h>

class TextureManager{
    public:
    static SDL_Texture* loadTexture(const char* fileName);
    static void draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
};

#endif