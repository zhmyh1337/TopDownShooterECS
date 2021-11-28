#pragma once

#include <ecs/ecs.h>
#include <Engine/Render/sprite_sheet.h>

struct SpriteSheetsPool : ecs::Singleton
{
    SpriteSheet soldierFeetWalk;
    SpriteSheet soldierFeetRun;
    SpriteSheet soldierRifleIdle;
    SpriteSheet soldierRifleMove;
    SpriteSheet soldierRifleReload;
    SpriteSheet soldierRifleMeleeAttack;
    SpriteSheet soldierRifleShoot;
};
