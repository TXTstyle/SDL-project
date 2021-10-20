#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class Entity {
public:
    Entity(Vector2f p_pos, Vector2i p_scl, SDL_Texture* p_tex, Vector2i p_sclS);
    Vector2f& getPos() {
        return pos;
    }
    Vector2i& getScl() {
        return scl;
    }
    SDL_Texture* getTex() {
        return tex;
    }
    SDL_Rect getCurrentFrame();
private:
    Vector2f pos;
    Vector2i scl;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
};