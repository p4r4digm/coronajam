// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>

int main(int argc, char* args[])
{
   SDL_Init(SDL_INIT_EVERYTHING);
   SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);

   SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
   SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

   SDL_RenderClear(renderer);
   SDL_RenderPresent(renderer);

   SDL_Delay(3000);

   return 0;
}
