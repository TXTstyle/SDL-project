#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Math.hpp"

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
  SDL_Texture* playerTexture = window.loadTexture("./res/gfx/Player.png");

  playerVector PlayerPos(64,200);
  playerVector PlayerPow(0,0);
  playerVector PlayerPosL(PlayerPos.x,PlayerPos.y);

  // Entity entitiesS[3] = {Entity(0,310, grassTexture), Entity(32,310, grassTexture), Entity(64,310, grassTexture)};
  // int entitiesLen = sizeof(entitiesS) / sizeof(entitiesS[0]);

  std::vector<Entity> entities = {Entity(Vector2f(0,0), Vector2i(480,320), bgTexture, Vector2i(480, 320)),
                                  Entity(Vector2f(0,288), Vector2i(480,32), grassLongTexture, Vector2i(480, 32))
                                  };

   {
     Entity platform(Vector2f(192, 232), Vector2i(32,32), platformTexture, Vector2i(32, 32));
     Entity platform2(Vector2f(224, 232), Vector2i(32,32), platformTexture, Vector2i(32, 32));
     Entity platform3(Vector2f(256, 232), Vector2i(32,32), platformTexture, Vector2i(32, 32));
     Entity player(Vector2f(PlayerPos.x, PlayerPos.y), Vector2i(16, 16), playerTexture, Vector2i(32, 32));

     entities.push_back(platform);
     entities.push_back(platform2);
     entities.push_back(platform3);
     entities.push_back(player);
   }

  const float timeStep = 0.01f;
  float accumulator = 0.01f;
  float currentTime = utils::hireTimeInSeconds();

  bool gameRunning = true;

  SDL_Event event;

  int off = 66;
  bool goLeft = false;

  while (gameRunning)
  {
    float newTime = utils::hireTimeInSeconds();
    float frameTime = newTime - currentTime;

    currentTime = newTime;

    accumulator += frameTime;

    const Uint8 *keyStates = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        gameRunning = false;
      if(event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym)
        {
          case SDLK_d:
            PlayerPow.x += 8;
          break;
          case SDLK_a:
            PlayerPow.x -= 8;
          break;
          case SDLK_w:
            PlayerPow.y -= 8;
          break;
          case SDLK_s:
            PlayerPow.y += 8;
          break;
        }
      }
    }

    while (accumulator >= timeStep)
    {
      
      /*
      if(off >= 416 && !goLeft) {
        goLeft = true; 
        std::cout << goLeft << "\n";
      } else if(off <= 64 && goLeft) {
        goLeft = false; 
        std::cout << goLeft << "\n";
      }
      
      if(goLeft) {
        entities.pop_back();
        Entity platform(Vector2f(off, 128), Vector2i(32,32), platformTexture, Vector2i(32, 32));

        entities.push_back(platform);
        off -= 2;
          
      }else if (!goLeft)
      {
        entities.pop_back();
        Entity platform(Vector2f(off, 128), Vector2i(32,32), platformTexture, Vector2i(32, 32));

        entities.push_back(platform);
        off += 2;
      }*/
      
      //std::cout << (PlayerPosL.x) << ", " << PlayerPos.x << "\n";
      PlayerPosL.x = PlayerPos.x;

      while (PlayerPow.x > 0 && PlayerPos.x <= 464)
      {
        //PlayerPosL.x = PlayerPos.x;
        PlayerPos.x += 1;
        PlayerPow.x -= 2;
        PlayerPow.print();
      }
      while (PlayerPow.x < 0 && PlayerPos.x >= 0)
      {
        //PlayerPosL.x = PlayerPos.x;
        PlayerPos.x -= 1;
        PlayerPow.x += 2;
        PlayerPow.print();
      }
      
      if(PlayerPos.x > 464) PlayerPos.x = 464; PlayerPow.x = 0;
      if(PlayerPos.x < 0) PlayerPos.x = 0; PlayerPow.x = 0;

      PlayerPosL.y = PlayerPos.y;

      while (PlayerPow.y > 0 && PlayerPos.y <= 272)
      {
        //PlayerPosL.x = PlayerPos.x;
        PlayerPos.y += 1;
        PlayerPow.y -= 2;
        PlayerPow.print();
      }
      while (PlayerPow.y < 0 && PlayerPos.y >= 0)
      {
        //PlayerPosL.x = PlayerPos.x;
        PlayerPos.y -= 1;
        PlayerPow.y += 2;
        PlayerPow.print();
      }
      
      if(PlayerPos.y > 272) PlayerPos.y = 272; PlayerPow.y = 0;
      if(PlayerPos.y < 0) PlayerPos.y = 0; PlayerPow.y = 0;
      
      accumulator -= timeStep;
    }
    
    const float alpha = accumulator / timeStep;

    
    {
      float px = PlayerPosL.x + alpha*(PlayerPos.x-PlayerPosL.x);
      if(PlayerPow.x == 0) px = PlayerPos.x;
      entities.pop_back();
      Entity player(Vector2f(px, PlayerPos.y), Vector2i(16,16), playerTexture, Vector2i(32, 32));
      std::cout << (1-alpha)*(PlayerPos.x-PlayerPosL.x) << ", " << PlayerPos.x << "\n";
      entities.push_back(player);
    }
    
    
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