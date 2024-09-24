#ifndef Text_H
#define Text_H
#include "Components.h"
#include <texture.h>

class TextComponent : public Component {
    private:
        string message;
        TransformComponent *transform;
        SDL_Texture* text;
        SDL_Rect dest;
        SDL_Renderer* renderer;
        SDL_Color textColor;
        
        int size;   
        int x;
        int y;
    public:
        TextComponent() = default;

        TextComponent(string message, SDL_Renderer* renderer, int x, int y) {
            setMes(message);
            this->renderer = renderer;
            this->x = x;
            this->y = y;
        }
        TextComponent(string message, SDL_Renderer* renderer, int x, int y, int size, SDL_Color textColor) {
            setMes(message);
            this->renderer = renderer;
            this->x = x;
            this->y = y;
            this->textColor = textColor;
            this->size = size;
        }

        ~TextComponent() {
            SDL_DestroyTexture(text);
        }
        void init() override {
        }
        
        void update() override{
        }

        void draw() override {
            setTexture();
            setDes();
            TextureManager::draw(text ,dest);
        }
        void setTexture() {
            text = TextureManager::renderText(message, "font/AtariClassic-Regular.ttf", textColor, size, renderer);
        }
        void setMes(string message) {
            this->message = message;
        }
        void setDes() {
            dest.x = this->x;
            dest.y = this->y;
            SDL_QueryTexture(text, NULL, NULL, &dest.w, &dest.h);
        }
        void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
        {
            textColor.r = red;
            textColor.g = green;
            textColor.b = blue;
            textColor.a = alpha;
        }
        SDL_Rect getRect(){return dest;}
};


#endif