#pragma once

#include "Sound/sound_effect.h"
#include <ecs/ecs.h>

struct AudioPool : ecs::Singleton
{
    SoundEffect rifleShot;
    SoundEffect localPlayerTakesDamage;
    SoundEffect bulletDamage;
    SoundEffect gameOver;
};
