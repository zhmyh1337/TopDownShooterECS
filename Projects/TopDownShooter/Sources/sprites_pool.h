#pragma once

#include <ecs/ecs.h>
#include <Engine/Render/sprite.h>

struct SpritesPool : ecs::Singleton
{
    Sprite soldierFeetIdle;
    Sprite circle;
};
