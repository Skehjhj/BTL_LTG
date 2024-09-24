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
auto& ai_player(manager.addEntity());

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

    footballbg = TextureManager::loadTexture("images/background.png");
    //ECS implement

    score1.addComponent<TextComponent>(to_string(playerScore1), renderer, WIDTH/4, HEIGHT / 15, 40, white);
    score2.addComponent<TextComponent>(to_string(playerScore2), renderer, WIDTH* 3/4, HEIGHT / 15, 40, white);

    ball.addComponent<TransformComponent>(Game::WIDTH/2, Game::HEIGHT/2, 0, 20, 20);
    ball.addComponent<ColliderComponent>("ball");
    ball.addComponent<SpriteComponent>("images/white.jpg");

    player1.addComponent<TransformComponent>(350, Game::HEIGHT/2 - 50 , 1, 100, 20);
    player1.addComponent<SpriteComponent>("images/blue.jpg");
    player1.addComponent<ColliderComponent>("player");
    player1.addComponent<Keyboard>();

    player1_gkp.addComponent<TransformComponent>(10, Game::HEIGHT/2 - 75, 3, 150, 20);
    player1_gkp.addComponent<SpriteComponent>("images/blue.jpg");
    player1_gkp.addComponent<ColliderComponent>("player");
    player1_gkp.addComponent<Keyboard>();

    // player2.addComponent<TransformComponent>(1100, 100, 2);
    // player2.addComponent<SpriteComponent>("images/chai.png");
    // player2.addComponent<ColliderComponent>("player");
    // player2.addComponent<Keyboard>();
    // player2_gkp.addComponent<TransformComponent>(1150, 100, 4);
    // player2_gkp.addComponent<SpriteComponent>("images/chai.png");
    // player2_gkp.addComponent<ColliderComponent>("player");
    // player2_gkp.addComponent<Keyboard>();

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    bgmusic = Mix_LoadMUS("sound/BreakingPoint.mp3");
    beep = Mix_LoadWAV("sound/hit.mp3");
    if (beep == nullptr) {
        cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME * 3/4);
    Mix_PlayMusic(bgmusic, -1);

    checkhit = true;
    ResetBall();
    LaunchBall();
}


void Game::handleMenu(){

    SDL_Event event;
    Menu Menu(renderer, window);
    Menu.initScreen( "images/menu.png");
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
                    
                    ai_player.addComponent<TransformComponent>(Game::WIDTH - 250, Game::HEIGHT/2 - 75, 2, 150, 20);
                    ai_player.addComponent<SpriteComponent>("images/red.jpg");
                    ai_player.addComponent<ColliderComponent>("AI");
                    ai_player.addComponent<AIComponent>(&ball.getComponent<TransformComponent>());

                    player2.destroy();
                    player2_gkp.destroy();

                    quitMenu = true;
                    gamemode = 1;
                }
                else if(event.key.keysym.sym == SDLK_2){
                    printf("2 key pressed!\n");
                    
                    player2.addComponent<TransformComponent>(Game::WIDTH - 350, Game::HEIGHT/2 - 50, 2, 100, 20);
                    player2.addComponent<SpriteComponent>("images/red.jpg");
                    player2.addComponent<ColliderComponent>("player");
                    player2.addComponent<Keyboard>();
                    player2_gkp.addComponent<TransformComponent>(Game::WIDTH - 10, Game::HEIGHT/2 - 75, 4, 150, 20);
                    player2_gkp.addComponent<SpriteComponent>("images/red.jpg");
                    player2_gkp.addComponent<ColliderComponent>("player");
                    player2_gkp.addComponent<Keyboard>();

                    ai_player.destroy();

                    bool player2Initialized = 
                        player2.hasComponent<TransformComponent>() &&
                        player2.hasComponent<SpriteComponent>() &&
                        player2.hasComponent<ColliderComponent>() &&
                        player2.hasComponent<Keyboard>();

                    if (player2Initialized) {
                        std::cout << "Player 2 successfully initialized!" << std::endl;
                    } else {
                        std::cout << "Player 2 initialization failed!" << std::endl;
                    }
                    cout << "2 player mode" << endl;
                    quitMenu = true;
                    gamemode = 2;
                }
            }
    }
    manager.refresh();
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
    bool collision = false;
    collision |= Collision::AABB(player1.getComponent<ColliderComponent>().collider, ball.getComponent<ColliderComponent>().collider, player1.getComponent<TransformComponent>().velocity, ball.getComponent<TransformComponent>().velocity);
    collision |= Collision::AABB(player1_gkp.getComponent<ColliderComponent>().collider, ball.getComponent<ColliderComponent>().collider, player1_gkp.getComponent<TransformComponent>().velocity, ball.getComponent<TransformComponent>().velocity);

    if (gamemode == 2) {
        collision |= Collision::AABB(player2.getComponent<ColliderComponent>().collider, ball.getComponent<ColliderComponent>().collider, player2.getComponent<TransformComponent>().velocity, ball.getComponent<TransformComponent>().velocity);
        collision |= Collision::AABB(player2_gkp.getComponent<ColliderComponent>().collider, ball.getComponent<ColliderComponent>().collider, player2_gkp.getComponent<TransformComponent>().velocity, ball.getComponent<TransformComponent>().velocity);
    } else if (gamemode == 1) {
        collision |= Collision::AABB(ai_player.getComponent<ColliderComponent>().collider, ball.getComponent<ColliderComponent>().collider, ai_player.getComponent<TransformComponent>().velocity, ball.getComponent<TransformComponent>().velocity);
    }
    if (collision) {
        start = SDL_GetTicks();
        checkhit = false;
        return true;
    }
    return false;
}

void Game::update(){

    manager.refresh();
    manager.update();

    if(ball.getComponent<TransformComponent>().position.y <= 0
    || ball.getComponent<TransformComponent>().position.y + ball.getComponent<TransformComponent>().height >= HEIGHT) {
        ball.getComponent<TransformComponent>().velocity.y = -ball.getComponent<TransformComponent>().velocity.y;     // Change y direction
        Mix_PlayChannel(-1, beep, 0);
    }

    if(ball.getComponent<TransformComponent>().position.x <= 0
    || ball.getComponent<TransformComponent>().position.x + ball.getComponent<TransformComponent>().width >= WIDTH) {
        if(ball.getComponent<TransformComponent>().position.x <= 0) {
            ++playerScore2;
            score2.getComponent<TextComponent>().setMes(to_string(playerScore2));
        }
        if(ball.getComponent<TransformComponent>().position.x + ball.getComponent<TransformComponent>().width >= WIDTH) {
            ++playerScore1;
            score1.getComponent<TextComponent>().setMes(to_string(playerScore1));
        }
        Mix_PlayChannel(-1, beep, 0);
        ResetBall();
        LaunchBall();
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
        Mix_PlayChannel(-1, beep, 0);
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
    Mix_FreeMusic(bgmusic);
    Mix_FreeChunk(beep);
    Mix_CloseAudio();
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