#include "sound_channel.h"

#include <common.h>

SoundChannel::SoundChannel(int index)
    : m_index(index)
{
}

void SoundChannel::Update()
{
    m_isPlaying = m_isPlaying && Mix_Playing(m_index) == 1;
}

void SoundChannel::Stop()
{
    Mix_HaltChannel(m_index);
    m_isPlaying = false;
}

void SoundChannel::PlayChunkAtPosition(
    Mix_Chunk* chunk, int uniqueId, const glm::vec2& position, const glm::vec2& earPosition)
{
    constexpr auto maxHearingDistance = 20.0f;
    const auto vector = position - earPosition;

    if (vector == glm::vec2())
    {
        /* debug_log("Playing non-spatial %d sound", uniqueId); */
        Mix_PlayChannel(m_index, chunk, 0);
        m_isPlaying = true;
        m_uniqueId = uniqueId;
        m_position = position;
        return;
    }

    const auto dist = glm::length(vector);
    const auto distConvertedAsFloat = std::floor(dist / maxHearingDistance * 0xFF);

    if (distConvertedAsFloat >= 0xFF)
    {
        /* debug_log("Not playing %d sound as it's too far (%f/%f) away", uniqueId, dist, maxHearingDistance); */
        if (m_isPlaying)
        {
            Stop();
        }
        return;
    }

    const auto radians = std::atan2(vector.y, vector.x);
    const auto degrees = glm::degrees(radians);
    const auto angleConverted = static_cast<Sint16>(static_cast<int>(90 - degrees + 360) % 360);
    const auto distConvertedAsUint8 = static_cast<Uint8>(distConvertedAsFloat);
    /* debug_log("Playing %d sound at angle = %d, dist = %u",
        uniqueId, angleConverted, distConvertedAsUint8); */
    Mix_PlayChannel(m_index, chunk, 0);
    Mix_SetPosition(m_index, angleConverted, distConvertedAsUint8);
    
    m_isPlaying = true;
    m_uniqueId = uniqueId;
    m_position = position;
}
