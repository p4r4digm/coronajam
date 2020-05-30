
#include "game.h"
#include <stdio.h>
#include <SDL_image.h>

SDL_Texture* playerTex;


Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
   int flags = 0;
   if (fullscreen) {
      flags = SDL_WINDOW_FULLSCREEN;
   }

   if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
      printf("SDL subsystems initialized...\n");
      
      window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
      if (window) {
         printf("Window created.\n");

         renderer = SDL_CreateRenderer(window, -1, 0);
         if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            printf("Renderer made.\n");

            //Loading our player
            SDL_Surface* tmpSurface = IMG_Load("assets/player.jpg");
            printf("IMG_Load: %s\n", IMG_GetError());
            playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
            SDL_FreeSurface(tmpSurface);

            isRunning = true;
            return;
         }
      }
   }
   isRunning = false;
}

void Game::handleEvents(){
   SDL_Event event;
   SDL_PollEvent(&event);
   switch (event.type) {
   case SDL_QUIT:
      isRunning = false;

   }
}

void Game::update(){
   //This is just some debug stuff
   //Game::count += 1;
   //printf("%d I guess it's working...\n", Game::count);
}
void Game::render(){
   SDL_RenderClear(renderer);
   //Add player here to render
   int check = SDL_RenderCopy(renderer, playerTex, NULL, NULL);
   SDL_RenderPresent(renderer);

}

void Game::clean(){
   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderer);
   SDL_Quit();

   printf("Cleanup successful.\n");
}

bool Game::running() {
   return isRunning;
}