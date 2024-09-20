#ifndef texture_H
#define texture_H
#include <game.h>

class TextureManager{
    public:
    static SDL_Texture* loadTexture(const char* fileName);
    static void draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
    static void draw(SDL_Texture* texture, SDL_Rect dest);
    static SDL_Texture* renderText(const string &message, const string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer);
};

#endif