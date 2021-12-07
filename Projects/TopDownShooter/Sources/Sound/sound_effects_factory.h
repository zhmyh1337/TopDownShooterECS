#pragma once

#include <ecs/ecs.h>
#include <string_view>
#include "sound_effect.h"

class SoundEffectsFactory : ecs::Singleton
{
public:
    SoundEffect Create(std::string_view filePath, size_t channelsCount, float volume = 1.0f);
    void AllocateChannels();

private:
    size_t m_totalChannelsCount = 0;
};
