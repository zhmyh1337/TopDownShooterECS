#pragma once

#include <ecs/ecs.h>
#include <Engine/Render/sprite_sheet.h>

struct SpriteSheetsPool : ecs::Singleton
{
    SpriteSheet soldierFeetRun;
};
