#ifndef Keybroad_H
#define Keybroad_H

#include <game.h>
#include <ECS/ECS.h>
#include <ECS/Components.h>

class Keyboard : public Component{
    public:
        TransformComponent * transform;

        void init() override{
            transform = &entity->getComponent<TransformComponent>();
        }

        const Uint8* keystates = SDL_GetKeyboardState(NULL); 

        void update() override {
            transform->velocity.x = 0;
            transform->velocity.y = 0;

            // if(transform->player1 == 2 && !gkp_2
            //     || transform->player1 == 4 && gkp_2){
                if(transform->player1 == 2){
                if (keystates[SDL_SCANCODE_UP]) {
                    transform->velocity.y = -1;
                }
                if (keystates[SDL_SCANCODE_LEFT]) {
                    transform->velocity.x = -1;
                }
                if (keystates[SDL_SCANCODE_DOWN]) {
                    transform->velocity.y = 1;
                }
                if (keystates[SDL_SCANCODE_RIGHT]) {
                    transform->velocity.x = 1;
                }
                // if (keystates[SDL_SCANCODE_RCTRL]) {
                //     *gkp_2 = !(*gkp_2);
                // }
            }
            // else if(transform->player1 == 1 && !gkp_1
            //     || transform->player1 == 3 && gkp_1){
            if(transform->player1 == 1){
                if (keystates[SDL_SCANCODE_W]) {
                    transform->velocity.y = -1;
                }
                if (keystates[SDL_SCANCODE_A]) {
                    transform->velocity.x = -1;
                }
                if (keystates[SDL_SCANCODE_S]) {
                    transform->velocity.y = 1;
                }
                if (keystates[SDL_SCANCODE_D]) {
                    transform->velocity.x = 1;
                }
                // if (keystates[SDL_SCANCODE_LCTRL]) {
                //     *gkp_1 = !(*gkp_1);
                // }
            }
            transform->velocity.normalize();
        }
};

#endif