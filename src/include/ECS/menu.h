#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <ECS/Text.h>
#include <game.h>

using namespace std;

class Menu{
    public:
        bool on = false;
        Menu(SDL_Renderer *windowFontRenderer, SDL_Window *window){
            TTF_Init();
            FontRenderer = windowFontRenderer;
            windowScreen = window;
            SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        }

        void initScreen(const char *backgroundImg){
            if(backgroundImg != NULL){
                
                ImageRenderer = SDL_CreateRenderer(windowScreen, -1, 0);
                SDL_Surface *BackgroundSurface = IMG_Load(backgroundImg);
                ImageTexture = SDL_CreateTextureFromSurface(FontRenderer, BackgroundSurface);
            }
        }
        void update(){
            
        }


        void render(){
            int window_width, window_height;
            SDL_GetWindowSize(windowScreen, &window_width, &window_height);
            SDL_RenderCopy(FontRenderer, ImageTexture, NULL, NULL);
            SDL_RenderPresent(FontRenderer);
           
            TextComponent line1("TINY FOOTBALL", FontRenderer, 390, 60, 40, white);
            line1.setTexture();
            line1.draw();
            TextComponent line2("Press 1 or 2 to choose GAME MODE", FontRenderer, 320, 160, 20, white);
            line2.setTexture();
            line2.draw();

            TextComponent line3("1: PvE", FontRenderer, Game::WIDTH * 1/4 - 100, Game::HEIGHT / 2 , 25, white);
            line3.setTexture();
            line3.draw();
            TextComponent line4("2: PvP", FontRenderer, Game::WIDTH * 3/4 - 100, Game::HEIGHT / 2, 30, white);
            line4.setTexture();
            line4.draw();

        }

        void quitScreen(){
            SDL_DestroyTexture(FontTexture);
            SDL_FreeSurface(FontSurface);
        }

    private:
        SDL_Window *windowScreen;
        SDL_Renderer *FontRenderer, *ImageRenderer;
        SDL_Texture *FontTexture, *ImageTexture;
        SDL_Surface *FontSurface;
        SDL_Color white = {255, 255, 255, 255};
        SDL_Color black = {0, 0, 0, 0};
        
        TTF_Font *Font;

        int windowHeight, windowWidth;

};

#endif