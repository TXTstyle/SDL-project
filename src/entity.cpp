#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


Entity::Entity(Vector2f p_pos, Vector2i p_scl, SDL_Texture* p_tex, Vector2i p_sclS)
:pos(p_pos), tex(p_tex), scl(p_scl)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = p_sclS.x;
    currentFrame.h = p_sclS.y;
}

SDL_Rect Entity::getCurrentFrame() {
    return currentFrame;
}