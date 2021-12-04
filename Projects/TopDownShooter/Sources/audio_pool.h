#pragma once

#include <ecs/ecs.h>
#include <SDL2/SDL_mixer.h>

struct AudioPool : ecs::Singleton
{
    Mix_Chunk* rifleShot;
};
