#ifndef SpriteComp_H
#define SpriteComp_H

#include <ECS/Components.h>
#include <SDL2/SDL.h>
#include <texture.h>

class SpriteComponent : public Component{
    private:
        TransformComponent *transform;
        SDL_Texture* texture;
        SDL_Rect srcR, dR;

    public:
        SpriteComponent() = default;

        SpriteComponent(const char* path){
            setTex(path);
        }
        ~SpriteComponent(){
            SDL_DestroyTexture(texture);
        }
        void setTex(const char* path){
            texture = TextureManager::loadTexture(path);
        }
        void init() override{
            transform = &entity->getComponent<TransformComponent>();
    
            srcR.x = srcR.y = 0;
            srcR.w = transform->width;
            srcR.h = transform->height;
            
        }

        void update() override{
            dR.x = static_cast<int>(transform->position.x);
            dR.y = static_cast<int>(transform->position.y);
            dR.w = transform->width * transform->scale;
            dR.h = transform->height * transform->scale;
        }

        void draw() override{
            TextureManager::draw(texture, srcR, dR);
        }

    
};

#endif