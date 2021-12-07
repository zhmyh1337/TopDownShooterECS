#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "sound_channel.h"

class SoundEffect
{
public:
    enum class UniqueIds
    {
        GameOver = -3,
        LocalPlayerTakesDamage = -2,
        LocalPlayerShoots = -1,
        EnemyTakesBulletDamageBegin = 0
    };

public:
    SoundEffect();

    SoundEffect(Mix_Chunk* mixChunk, int firstChannelIndex, size_t channelsCount);

    void AddToPlaybackQueue(int uniqueId, glm::vec2 position = glm::vec2());

    void PlayAll(const glm::vec2& earPosition);

private:
    struct PlaybackQueueData
    {
        int uniqueId;
        glm::vec2 position;
    };

private:
    Mix_Chunk* m_mixChunk;

    std::vector<SoundChannel> m_reservedChannels;
    std::vector<PlaybackQueueData> m_playbackQueue;
};
