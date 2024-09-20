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
        // void handleEvents()
        // {
        //     SDL_Event event;
        //     SDL_PollEvent(&event);

        //     switch (event.type) {

        //     case SDL_QUIT:
        //         on = false;
        //         break;

        //     case SDL_KEYDOWN:
        //         switch (event.key.keysym.sym) {
        //         case SDLK_UP:
        //             
        //             break;
        //         case SDLK_DOWN:
        //             
        //             break;

        //         case SDLK_RETURN:
        //             
        //             // break;

        //         default:
        //             break;
        //         }
        //         
        //         
            
        //         break;


        //     default:
        //         break;
        //     }
        // }

        void render(){
            int window_width, window_height;
            SDL_GetWindowSize(windowScreen, &window_width, &window_height);
            //renderBackground();
            SDL_RenderCopy(FontRenderer, ImageTexture, NULL, NULL);
            SDL_RenderPresent(FontRenderer);
            // renderScreenText();
            // option1.setMes("1 Player");
            // option1.setRenderer(FontRenderer);
            // option1.setColor(255, 255, 255, 255);
            // option1.setTexture();
            // option1.setDes(500, 260);
            // option1.draw();

            // option2.setMes("2 Players");
            // option2.setRenderer(FontRenderer);
            // option2.setColor(255, 255, 255, 255);
            // option2.setTexture();
            // option2.setDes(500, 360);
            // option2.draw();

            // option2.setMes("TINY FOOTBALL");
            // option2.setRenderer(FontRenderer);
            // option2.setColor(255, 255, 255, 255);
            // option2.setTexture();
            // option2.setDes(500, 160);
            // option2.draw();
            TextComponent line1("TINY FOOTBALL", FontRenderer, 390, 60, 40, black);
            line1.setTexture();
            line1.draw();
            TextComponent line2("Press 1 or 2 to choose GAME MODE", FontRenderer, 320, 160, 20, black);
            line2.setTexture();
            line2.draw();

            TextComponent line3("1: PvE", FontRenderer, 20, 670, 20, white);
            line3.setTexture();
            line3.draw();
            TextComponent line4("2: PvP", FontRenderer, 20, 690, 20, white);
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