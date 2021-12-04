#pragma once

#include <ecs/ecs.h>
#include "Sound/sound_effect.h"

struct AudioPool : ecs::Singleton
{
    SoundEffect rifleShot;
};
