#ifndef Keybroad_H
#define Keybroad_H

#include <game.h>
#include <ECS/ECS.h>
#include <ECS/Components.h>

class Keyboard : public Component{
    public:
        TransformComponent * transform;
        bool isPlayer1 = true;
        bool isPlayer2 = true;
        bool break1 = false;
        bool break2 = false;

        void init() override{
            transform = &entity->getComponent<TransformComponent>();
        }

        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        const Uint8* keystate_current;

        void update() override {
            transform->velocity.x = 0;
            transform->velocity.y = 0;
            
            if (keystates[SDL_SCANCODE_LCTRL] && !break1) {
                break1 = true;
                isPlayer1 = !isPlayer1;
            }
            if (keystates[SDL_SCANCODE_RCTRL] && !break2) {
                break2 = true;
                isPlayer2 = !isPlayer2;
            }
            if(keystates[SDL_SCANCODE_LCTRL] == 0) break1 = false;
            if(keystates[SDL_SCANCODE_RCTRL] == 0) break2 = false;

            if (isPlayer1) {
                if(transform->player1 == 1) player1();
            } 
            else {
                if(transform->player1 == 3) player1();
            }
            if(isPlayer2){
                if(transform->player1 == 2) player2();
            }
            else{
                if(transform->player1 == 4) player2();
            }

            transform->velocity.normalize();
        }
        void player2(){
            if (keystates[SDL_SCANCODE_UP]) transform->velocity.y = -1;
            if (keystates[SDL_SCANCODE_LEFT]) transform->velocity.x = -1;
            if (keystates[SDL_SCANCODE_DOWN]) transform->velocity.y = 1;
            if (keystates[SDL_SCANCODE_RIGHT]) transform->velocity.x = 1;
        }
        void player1(){
            if (keystates[SDL_SCANCODE_W]) transform->velocity.y = -1;
            if (keystates[SDL_SCANCODE_A]) transform->velocity.x = -1;
            if (keystates[SDL_SCANCODE_S]) transform->velocity.y = 1;
            if (keystates[SDL_SCANCODE_D]) transform->velocity.x = 1;
        }
        private:
        void updatePlayerControls() {
            // Existing player control logic
        }

        void updateGoalkeeperControls() {
            // New goalkeeper control logic
        }
};

#endif