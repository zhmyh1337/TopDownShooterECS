#include "sound_effects_factory.h"
#include <SDL2/SDL_mixer.h>

SoundEffect SoundEffectsFactory::Create(std::string_view filePath, size_t channelsCount, float volume)
{
    auto mixChunk = Mix_LoadWAV(filePath.data());
    Mix_VolumeChunk(mixChunk, volume * MIX_MAX_VOLUME);
    auto soundEffect = SoundEffect(mixChunk, static_cast<int>(m_totalChannelsCount), channelsCount);
    m_totalChannelsCount += channelsCount;
    return soundEffect;
}

void SoundEffectsFactory::AllocateChannels()
{
    Mix_AllocateChannels(static_cast<int>(m_totalChannelsCount));
}
