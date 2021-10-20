#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

int main(int argc, char* args[]) {
  if (SDL_Init(SDL_INIT_VIDEO) > 0)
    std::cout << "SDL_Init HAS FAILED. ERROR: " << SDL_GetError() << "\n";

  if (!(IMG_Init(IMG_INIT_PNG)))
    std::cout << "IMG_Init HAS FAILED. ERROR: " << SDL_GetError() << "\n";

  RenderWindow window("Game", 600, 400);

  SDL_Texture* grassTexture = window.loadTexture("./res/gfx/Grass_1.png");

  Entity entities[3] = {Entity(0,310, grassTexture), Entity(32,310, grassTexture), Entity(64,310, grassTexture)};
  int entitiesLen = sizeof(entities) / sizeof(entities[0]);

  bool gameRunning = true;

  SDL_Event event;

  while (gameRunning)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        gameRunning = false;
    }
    
    window.clear();
    
    for (int i = 0; i < entitiesLen; i++)
    {
      window.render(entities[i]);
    }
    

    window.display();
  }
  
  
  window.cleanUp();
  SDL_Quit();

  return 0;
}