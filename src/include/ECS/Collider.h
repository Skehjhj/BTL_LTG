
#ifndef Collider_H
#define Collider_H
#include <string>
#include <ECS/ECS.h>
#include <SDL2/SDL.h>
#include <ECS/Components.h>

class ColliderComponent : public Component{
    public:
        SDL_Rect collider;
        std::string tag;

        TransformComponent *transform;
        ColliderComponent(std::string t){
            tag = t;
        }

        void init() override{
            if(!entity->hasComponent<TransformComponent>()){
                entity->addComponent<TransformComponent>();
            }

            transform = &entity->getComponent<TransformComponent>();

            Game::colliders.push_back(this);
        }

        void update() override{
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width;
            collider.h = transform->height;
        }

    private:
        

};
#endif