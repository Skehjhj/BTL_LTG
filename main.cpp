#include <game.h>

Game *game = nullptr;
int main(int argc, char *argv[]) {
    Uint32 Fstart;
    int Fend;
    game = new Game();
    game->run("Tiny Football", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::WIDTH, Game::HEIGHT, 0);
    while(game->running()){

        Fstart = SDL_GetTicks();
        if(!game->quitMenu) game->handleMenu();
        else if(game->quitMenu == true)
         {
                game->handleEvents();
                game->update();
                game->render();
         }

        Fend = SDL_GetTicks() - Fstart;
        if(Game::Fdelay > Fend){
            SDL_Delay(Game::Fdelay - Fend);
        }
    }
    game->clean();
    return 0;
}

