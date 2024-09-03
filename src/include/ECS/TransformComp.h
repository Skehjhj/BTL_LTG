#ifndef TransformComp_H
#define TransformComp_H
#include <ECS/Components.h>
#include <Vecto2D.h>

class TransformComponent : public Component{
    private:
        

    public:
        Vector2D position;
        Vector2D velocity;
        int player1;

        int height = 200;
        int width = 15;
        int scale = 1;

        int VEL = 10;
        

        TransformComponent(){
            position.Zero();
        }
        TransformComponent(float x, float y, int p){
            position.x = x;
            position.y = y;
            player1 = p;
        }

        TransformComponent(float x, float y, int p, int h, int w){
            position.x = x;
            position.y = y;
            player1 = p;
            height = h;
            width = w;
        }

        void init() override{
            velocity.Zero();
        }
        
        void update() override{
            position.x += velocity.x * VEL;
            position.y += velocity.y * VEL;

            if(player1 != 0){
                if(position.y < 25) position.y = 25;
                else if(position.y + height > Game::HEIGHT - 25) position.y = Game::HEIGHT - 25 - height;

                if(position.x < 25) position.x = 25;
                else if (position.x + width > Game::WIDTH - 25) position.x = Game::WIDTH - 25 - width;

                else if(player1 == 1 && position.x + width > 400){
                    position.x = 400 - width;
                }
                else if(player1 == 2 && position.x + width < Game::WIDTH - 400){
                    position.x = Game::WIDTH - 400 - width;
                }
            } 
        }
};

#endif