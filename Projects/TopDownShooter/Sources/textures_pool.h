#pragma once

#include <ecs/ecs.h>
#include <Engine/Render/Texture/texture2d.h>

struct TexturesPool : ecs::Singleton
{
    Texture2D* background;
    Texture2D* soldierFeetIdle;
    Texture2D* soldierFeetWalk;
    Texture2D* soldierFeetRun;
    Texture2D* soldierRifleIdle;
    Texture2D* soldierRifleMove;
    Texture2D* soldierRifleReload;
    Texture2D* soldierRifleMeleeAttack;
    Texture2D* soldierRifleShoot;
    Texture2D* zombieIdle;
    Texture2D* zombieMove;
    Texture2D* zombieAttack;
    Texture2D* bullet;
    Texture2D* blood;
    Texture2D* circle;
};
