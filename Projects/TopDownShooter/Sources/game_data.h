#pragma once

#include <ecs/ecs.h>

struct GameData : ecs::Singleton
{
    size_t killsCount = 0;
    float nextEnemySpawnTime = 0.0f;
    bool isGameOver = false;
};
