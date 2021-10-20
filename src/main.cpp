#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

int main(int argc, char* args[]) {
  if (SDL_Init(SDL_INIT_VIDEO) > 0)
    std::cout << "SDL_Init HAS FAILED. ERROR: " << SDL_GetError() << "\n";

  if (!(IMG_Init(IMG_INIT_PNG)))
    std::cout << "IMG_Init HAS FAILED. ERROR: " << SDL_GetError() << "\n";

  RenderWindow window("Gamer", 960, 640);

  SDL_Texture* grassTexture = window.loadTexture("./res/gfx/Grass_1.png");
  SDL_Texture* platformTexture = window.loadTexture("./res/gfx/Platform_1.png");
  SDL_Texture* bgTexture = window.loadTexture("./res/gfx/BG.png");
  SDL_Texture* grassLongTexture = window.loadTexture("./res/gfx/Grass_Long.png");

  // Entity entitiesS[3] = {Entity(0,310, grassTexture), Entity(32,310, grassTexture), Entity(64,310, grassTexture)};
  // int entitiesLen = sizeof(entitiesS) / sizeof(entitiesS[0]);

  std::vector<Entity> entities = {Entity(Vector2f(0,0), Vector2i(480,320), bgTexture, Vector2i(408, 320)),
                                  Entity(Vector2f(0,288), Vector2i(480,32), grassLongTexture, Vector2i(480, 32))
                                  };

   {
     Entity platform(Vector2f(192, 232), Vector2i(32,32), platformTexture, Vector2i(32, 32));
     Entity platform2(Vector2f(224, 232), Vector2i(32,32), platformTexture, Vector2i(32, 32));
     Entity platform3(Vector2f(256, 232), Vector2i(32,32), platformTexture, Vector2i(32, 32));

     entities.push_back(platform);
     entities.push_back(platform2);
     entities.push_back(platform3);
   }

  const float timeStep = 0.01f;
  float accumulator = 0.01f;
  float currentTime = utils::hireTimeInSeconds();

  bool gameRunning = true;

  SDL_Event event;

  while (gameRunning)
  {
    float newTime = utils::hireTimeInSeconds();
    float frameTime = newTime - currentTime;

    currentTime = newTime;

    accumulator += frameTime;

    while (accumulator >= timeStep)
    {
      while (SDL_PollEvent(&event))
      {
        if (event.type == SDL_QUIT)
          gameRunning = false;
      }

      {
        Entity platform(Vector2f(64, 128), Vector2i(32,32), platformTexture, Vector2i(32, 32));

        entities.push_back(platform);
      }

      accumulator -= timeStep;
    }
    
    //const float alpha = accumulator / timeStep;

    
    window.clear();

    for (Entity& e : entities)
    {
      window.render(e);
    }   

    window.display();
  }
  
  
  window.cleanUp();
  SDL_Quit();

  return 0;
}