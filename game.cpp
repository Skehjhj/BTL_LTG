#include<texture.h>
#include<game.h>
#include<ECS/menu.h>
#include<ECS/Components.h>
#include<Vecto2D.h>
#include<Collision.h>
#include <SDL2/SDL.h>

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

vector<ColliderComponent*> Game::colliders;

Manager manager;

auto& player1(manager.addEntity());
auto& player2(manager.addEntity());
auto& score1(manager.addEntity());
auto& score2(manager.addEntity());
auto& player1_gkp(manager.addEntity());
auto& player2_gkp(manager.addEntity());
auto& ball(manager.addEntity());

int playerScore1 = 0, playerScore2 = 0;
Game::Game(){
    isRunning = true;
}
Game::~Game(){
}



void Game::run(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){

    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(TTF_Init() != 0) {
        cout << "TTF_init error";

    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        cout << "Initialized" << endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window){
            renderer = SDL_CreateRenderer(window, -1, 0);
            
            fbdR.w = 1280;
            fbdR.h = 720;
            fbdR.x = 0;
            fbdR.y = 0;

            if(renderer){
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                isRunning = true;
            }
        }
        else cout << "window error";
    }

    footballbg = TextureManager::loadTexture("images/football.png");
    //ECS implement

    player1.addComponent<TransformComponent>(100, 100, 1);
    player1.addComponent<SpriteComponent>("images/meomeo.png");
    player1.addComponent<ColliderComponent>("player");
    player1.addComponent<Keyboard>();

    player2.addComponent<TransformComponent>(1100, 100, 2);
    player2.addComponent<SpriteComponent>("images/chai.png");
    player2.addComponent<ColliderComponent>("player");
    player2.addComponent<Keyboard>();

    score1.addComponent<TextComponent>(to_string(playerScore1), renderer, WIDTH/4, HEIGHT / 15, 40, white);
    score2.addComponent<TextComponent>(to_string(playerScore2), renderer, WIDTH* 3/4, HEIGHT / 15, 40, white);

    // player1_gkp.addComponent<TransformComponent>(50, 100, 3);
    // player1_gkp.addComponent<SpriteComponent>("images/meomeo.png");
    // player1_gkp.addComponent<ColliderComponent>("player");
    // player1_gkp.addComponent<Keyboard>();

    // player2_gkp.addComponent<TransformComponent>(1150, 100, 4);
    // player2_gkp.addComponent<SpriteComponent>("images/chai.png");
    // player2_gkp.addComponent<ColliderComponent>("player");
    // player2_gkp.addComponent<Keyboard>();

    ball.addComponent<TransformComponent>(Game::WIDTH/2, Game::HEIGHT/2, 0, 20, 20);
    ball.addComponent<ColliderComponent>("ball");
    ball.addComponent<SpriteComponent>("images/meomeo.png");
    checkhit = true;
    ResetBall();
    LaunchBall();
}


// int Game::showMenu(SDL_Surface* Screen, TTF_Font* font)
// {
//     Uint32 time;
//     int mouseX, mouseY;
//     const int NUMMENU = 2;
//     const char* labels[NUMMENU] = {"One Player", "Two Players"};
//     SDL_Surface* menus[NUMMENU];
//     bool selected[NUMMENU] = {0,0};
//     SDL_Color color[2] = {{255, 255, 255}, {255, 0, 0}};

//     menus[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
//     menus[1] = TTF_RenderText_Solid(font, labels[1], color[0]);
//     SDL_Rect pos[NUMMENU];
//     pos[0].x = Screen->clip_rect.w/2 - menus[0]->clip_rect.w/2;
//     pos[0].y = Screen->clip_rect.h/2 - menus[0]->clip_rect.h;
//     pos[1].x = Screen->clip_rect.w/2 - menus[0]->clip_rect.w/2;
//     pos[1].y = Screen->clip_rect.h/2 - menus[0]->clip_rect.h;


//     SDL_FillRect(Screen, &Screen->clip_rect, SDL_MapRGB(Screen->format, 0x00, 0x00, 0x00));
//     SDL_Event menu_event;
//     while(1)
//     {
//         time = SDL_GetTicks();
//         while(SDL_PollEvent(&menu_event))
//         {
//             switch(menu_event.type)
//             {
//                 case SDL_QUIT:
//                     for(int i = 0; i < NUMMENU; i++) SDL_FreeSurface(menus[i]);
//                     return 1;
//                 case SDL_MOUSEMOTION:
//                     mouseX = menu_event.motion.x;
//                     mouseY = menu_event.motion.y;
//                     for(int i = 0; i < NUMMENU; i++)
//                     {
//                         if(mouseX >= pos[i].x && mouseX <= pos[i].w && mouseY >= pos[i].y && mouseY <=pos[i].h)
//                         {
//                             if(!selected[i])
//                             {
//                                 selected[i] = 1;
//                                 SDL_FreeSurface(menus[i]);
//                                 menus[i] = TTF_RenderText_Solid(font, menus[i], color[1]);
//                             }
//                         }else{
//                             if(selected[i])
//                             {
//                                 selected[i] = 0;
//                                 SDL_FreeSurface(menus[i]);
//                                 menus[i] = TTF_RenderText_Solid(font, menus[i], color[0]);
//                             }
//                         }

//                     }
//                 case SDL_MOUSEBUTTONDOWN:
//                     mouseX = menu_event.button.x;
//                     mouseY = menu_event.button.y;
//                     for(int i = 0; i < NUMMENU; i++)
//                     {
//                         if(mouseX >= pos[i].x && mouseX <= pos[i].w && mouseY >= pos[i].y && mouseY <=pos[i].h)
//                         {
//                             for(int j = 0; j < NUMMENU; i++)
//                                 SDL_FreeSurface(menus[j]);
//                             return i;

//                         }
                        
//                     }
//                     break;
//                 case SDL_KEYDOWN:
//                     if(menu_event.key.keysym.sym == SDLK_ESCAPE)
//                     {
//                         for(int i = 0; i < NUMMENU; i++)
//                                 SDL_FreeSurface(menus[i]);
//                         return 0;
//                     }
                    
//             }
//         }
//         for(int i = 0; i < NUMMENU; i++)
//             SDL_BlitSurface(menus[i], NULL, Screen, &pos[i]);
//         SDL_Flip(Screen);
//         if(1000/30 > (SDL_GetTicks() - time))
//             SDL_Delay(1000/30 - (SDL_GetTicks() - time));
//         SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, Screen);
//         for(int i = 0; i < NUMMENU; i++) SDL_RenderCopy(renderer, Message, NULL, &pos[i]);


//     }

// }


void Game::handleMenu(){
    // while (SDL_PollEvent(&event)) {
    //     if (event.type == SDL_MOUSEBUTTONDOWN) {
    //         // Get the mouse position
    //         int mouseX, mouseY;
    //         SDL_GetMouseState(&mouseX, &mouseY);

    //         // Check if the user clicked on the "Player vs Player" option
    //         if (mouseX >= 100 && mouseX <= 300 && mouseY >= 100 && mouseY <= 150) {
    //             gamemode = 1; // Player vs Player
    //         }
    //         // Check if the user clicked on the "Player vs AI" option
    //         else if (mouseX >= 100 && mouseX <= 300 && mouseY >= 200 && mouseY <= 250) {
    //             gamemode = 2; // Player vs AI
    //         }
    //     }
    //     if(event.type == SDL_QUIT){
    //         isRunning = false;          
    //     }
    // }
    

    SDL_Event event;


    Menu Menu(renderer, window);

    
    Menu.initScreen( "images/background.jpg");
    //clear the render
            SDL_RenderClear(renderer);
            Menu.render();
            SDL_RenderPresent(renderer);
    while (!quitMenu){
            
            SDL_PollEvent(&event);
            if(event.type==SDL_WINDOWEVENT && event.window.event==SDL_WINDOWEVENT_CLOSE){
                quitMenu = true;
            }
            else if(event.type == SDL_QUIT) isRunning = false;
            else if(event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_1) {
                    printf("1 key pressed!\n");
                    quitMenu = true;
                    gamemode = 1;
                }
                else if(event.key.keysym.sym == SDLK_2){
                    printf("2 key pressed!\n");
                    quitMenu = true;
                    gamemode = 2;
                }

            }
    }
}

void Game::handleEvents(){
    while(SDL_PollEvent(&event) != 0){
        switch(event.type){
            case SDL_QUIT:
                isRunning = false;
                break;
        }
    }
}

bool Game::hit(){
    if(!checkhit) return false;
    if (Collision::AABB(player1.getComponent<ColliderComponent>().collider, ball.getComponent<ColliderComponent>().collider, player1.getComponent<TransformComponent>().velocity, ball.getComponent<TransformComponent>().velocity)
        || Collision::AABB(player2.getComponent<ColliderComponent>().collider, ball.getComponent<ColliderComponent>().collider, player2.getComponent<TransformComponent>().velocity, ball.getComponent<TransformComponent>().velocity)){
            start = SDL_GetTicks();
            checkhit = false;
            return true;
    }
    return false;
}

void Game::update(){
    //updating
    manager.refresh();
    manager.update();

    // cout << "ball: " << ball.getComponent<TransformComponent>().position.x << " || " << ball.getComponent<TransformComponent>().position.y + ball.getComponent<TransformComponent>().height <<  endl;

    if(ball.getComponent<TransformComponent>().position.y <= 0
    || ball.getComponent<TransformComponent>().position.y + ball.getComponent<TransformComponent>().height >= HEIGHT) {
        ball.getComponent<TransformComponent>().velocity.y = -ball.getComponent<TransformComponent>().velocity.y;     // Change y direction
        // beeper.Beep(SF_HZ_HIT, SF_DURATION_HIT);
    }

    if(ball.getComponent<TransformComponent>().position.x <= 0
    || ball.getComponent<TransformComponent>().position.x + ball.getComponent<TransformComponent>().width >= WIDTH) {
        // SDL_Delay(1000);
         if(ball.getComponent<TransformComponent>().position.x <= 0) {
            ++playerScore2;
            score2.getComponent<TextComponent>().setMes(to_string(playerScore2));
        }
        if(ball.getComponent<TransformComponent>().position.x + ball.getComponent<TransformComponent>().width >= WIDTH) {
            ++playerScore1;
            score1.getComponent<TextComponent>().setMes(to_string(playerScore1));
        }
        ResetBall();
        LaunchBall();
        // beeper.Beep(SF_HZ_HIT, SF_DURATION_HIT);
    }
    
    if(hit()){
        hitb++;
        curBallSpeed += VELincrease;
        Vector2D ballvel = ball.getComponent<TransformComponent>().velocity;
        ballvel.x = (float)-sgn(ballvel.x);
        ballvel.y += rnDis(rnGen) / 2.0f;
        ballvel.normalize();
        ballvel.x *= curBallSpeed;
        ballvel.y *= curBallSpeed;
        ball.getComponent<TransformComponent>().velocity = ballvel;
        // cout << "ballhit: " << hitb << " || " << ball.getComponent<TransformComponent>().velocity.x << " || " << ball.getComponent<TransformComponent>().velocity.y << " || " 
        // << "ballspeed:  " << curBallSpeed << " || " << ball.getComponent<TransformComponent>().velocity.length() <<  endl;
    }

    if(!checkhit){
        Uint32 end = SDL_GetTicks();
        if(end - start > 200) checkhit = true;
    }
}

void Game::render(){
    SDL_RenderClear(renderer);
    //rendering
    SDL_RenderCopy(renderer, footballbg, NULL , &fbdR);
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game Cleaned" << endl;
}

void Game::ResetBall(){
    ball.getComponent<TransformComponent>().position = Vector2D(Game::WIDTH/2, Game::HEIGHT/2);
    curBallSpeed = BallSpeed;
}

void Game::LaunchBall(){
    std::uniform_int_distribution<int> dir(0, 1);
    int direction = 1+(-2)*(dir(rnGen)%2);
    ball.getComponent<TransformComponent>().velocity.x = direction * curBallSpeed;
    ball.getComponent<TransformComponent>().velocity.y = rnDis(rnGen)/4.0f * curBallSpeed;
}