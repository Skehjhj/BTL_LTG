#ifndef game_H
#define game_H
#include <iostream>
#include <vector>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_version.h>
#include <SDL2/begin_code.h>
#include <SDL2/close_code.h>
#include <cmath>
#include <random>

using namespace std;

class ColliderComponent;

class Game{
    public:
        static const int WIDTH = 1280, HEIGHT = 720;
        static const int FPS = 60;
        static const int Fdelay = 1000/FPS;

        static constexpr float BallSpeed = 1.0f;
        static constexpr float VELincrease = 0.05f;

        int gamemode = 0;
        int hitb = 0;
        bool quitMenu = false;
        bool checkhit = true;
        Uint32 start;

        std::mt19937 rnGen;
        std::uniform_real_distribution<float> rnDis;

        Mix_Music *bgmusic = NULL;
        Mix_Chunk *beep = NULL;

        Game();
        ~Game();
        void run(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

        // int showMenu();

        void handleMenu();
        void handleEvents();
        void update();
        void render();
        void clean();
        void cleanupGameMode();
        bool hit();
        bool running() { return isRunning; };


        static SDL_Renderer *renderer;
        static SDL_Event event;
        static vector<ColliderComponent*> colliders;
        SDL_Color white = {255, 255, 255, 255};
    private:
        int count = 0;
        float curBallSpeed = BallSpeed;
        bool isRunning;
        
        // TTF_Font *font = TTF_OpenFont("AtariClassic-Regular.ttf", 20);
        // SDL_Surface *Screen;
        SDL_Window * window = NULL;  
        SDL_Texture* footballbg = NULL;
        SDL_Rect fbsrcR, fbdR;
        
        // void ResetBall(const Vector2D& pos);
        // void LaunchBall(const Vector2D& dir);

        void ResetBall();
        void LaunchBall();
};

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

#endif