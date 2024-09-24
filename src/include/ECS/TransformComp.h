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
        int width = 20;
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
            // if(player1 != 0){

            //     if(position.y < 25) position.y = 25;
            //     else if(position.y + height > Game::HEIGHT - 25) position.y = Game::HEIGHT - 25 - height;
            //     if(position.x < 25) position.x = 25;
            //     else if (position.x + width > Game::WIDTH - 25) position.x = Game::WIDTH - 25 - width;

            //     else if(player1 == 1 && position.x + width > 400){
            //         position.x = 400 - width;
            //     }
            //     else if(player1 == 2 && position.x + width < Game::WIDTH - 400){
            //         position.x = Game::WIDTH - 400 - width;
            //     }
            // } 

            switch(player1){
                case 1:
                    if(position.y < 125) position.y = 125;
                    if(position.y + height > Game::HEIGHT - 125) position.y = Game::HEIGHT - 125 - height;
                    if(position.x < 275) position.x = 275;
                    if(position.x + width > 475) position.x = 475 - width;
                    break;
                case 2:
                    if(position.y < 125) position.y = 125;
                    if(position.y + height > Game::HEIGHT - 125) position.y = Game::HEIGHT - 125 - height;
                    if(position.x + width < Game::WIDTH - 475) position.x = Game::WIDTH - 475 - width;
                    if(position.x + width > Game::WIDTH - 275) position.x = Game::WIDTH - 275 - width;
                    break;
                case 3:
                    if(position.y < 50) position.y = 50;
                    if(position.y + height > Game::HEIGHT - 50) position.y = Game::HEIGHT - 50 - height;
                    if(position.x < 5) position.x = 5;
                    if(position.x + width > 75) position.x = 75 - width;
                    break;
                case 4:
                    if(position.y < 50) position.y = 50;
                    if(position.y + height > Game::HEIGHT - 50) position.y = Game::HEIGHT - 50 - height;
                    if(position.x + width < Game::WIDTH - 75) position.x = Game::WIDTH - 75 - width;
                    if(position.x + width > Game::WIDTH - 5) position.x = Game::WIDTH - 5 - width;
                    break;
                case 5:
                    if(position.y < 50) position.y = 50;
                    if(position.y + height > Game::HEIGHT - 50) position.y = Game::HEIGHT - 50 - height;
                    // if(position.x + width < Game::WIDTH - 475) position.x = Game::WIDTH - 475 - width;
                    // if(position.x + width > Game::WIDTH - 275) position.x = Game::WIDTH - 275 - width;
                    break;
            }
        }
};

#endif