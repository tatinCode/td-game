#include <SDL2/SDL_error.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <SDL2/SDL.h>

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char** argv){

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cerr << "SDL Init failed!: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
            "Top-down shooter",         //name of the window
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED,
            WIDTH, HEIGHT,
            SDL_WINDOW_SHOWN
            );

    if(!window){
        std::cerr << "Window creation failed!: " << SDL_GetError() << "\n";
        SDL_Quit();

        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        std::cerr << "Renderer Creation failed!: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 1;
    }

    bool running = true;
    SDL_Event event;

    //player stuff
    SDL_Rect player;
    player.w = 40;
    player.h = 40;
    player.x = WIDTH / 2 - player.w /2;
    player.y = HEIGHT / 2 - player.h /2;
    int speed = 5;
    
    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }

            const Uint8* keystate = SDL_GetKeyboardState(NULL);

            //movement keys for the player
            if(keystate[SDL_SCANCODE_W]){
                player.y -= speed;
            }
            else if(keystate[SDL_SCANCODE_S]){
                player.y += speed;
            }
            else if(keystate[SDL_SCANCODE_A]){
                player.x -= speed;
            }
            else if(keystate[SDL_SCANCODE_D]){
                player.x += speed;
            }


            //keep player in bounds
            if(player.x < 0){
                player.x = 0;
            }
            if(player.y < 0){
                player.y = 0;
            }

            if(player.x + player.w > WIDTH){
                player.x = WIDTH - player.w;
            }
            if(player.y + player.h > HEIGHT){
                player.y= HEIGHT - player.h;
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //game renderer calls here

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &player);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
