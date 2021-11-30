#pragma once

#include <ecs/ecs.h>
#include <Engine/Render/sprite.h>

struct SpritesPool : ecs::Singleton
{
    Sprite background;
    Sprite soldierFeetIdle;
    Sprite bullet;
    Sprite circle;
};
