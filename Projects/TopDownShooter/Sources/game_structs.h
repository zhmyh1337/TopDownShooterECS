#pragma once

#include <Engine/Render/sprite.h>

struct SpriteFactory : ecs::Singleton
{
    Sprite background;
};
