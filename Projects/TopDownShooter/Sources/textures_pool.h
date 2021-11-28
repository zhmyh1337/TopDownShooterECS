#pragma once

#include <ecs/ecs.h>
#include <Engine/Render/Texture/texture2d.h>

struct TexturesPool : ecs::Singleton
{
    Texture2D* background;
    Texture2D* soldierFeetRun;
};
