#include "sound_effect.h"

SoundEffect::SoundEffect()
{
}

SoundEffect::SoundEffect(Mix_Chunk* mixChunk, int channelBegin, int channelEnd)
    : m_mixChunk(mixChunk), m_currentChannel(channelBegin), m_channelBegin(channelBegin), m_channelEnd(channelEnd)
{
}

void SoundEffect::Play()
{
    PlayImpl();
    NextChannel();
}

void SoundEffect::PlayAtVector(const glm::vec2& vec)
{
    PlayImpl();
    SetPosition(vec);
    NextChannel();
}

void SoundEffect::PlayImpl()
{
    Mix_PlayChannel(m_currentChannel, m_mixChunk, 0);   
}

void SoundEffect::SetPosition(const glm::vec2& vec)
{
    const auto radians = std::atan2(vec.y, vec.x);
    const auto degrees = glm::degrees(radians);
    const auto dist = glm::length(vec);
    Mix_SetPosition(m_currentChannel, static_cast<Sint16>(90 - degrees), dist * k_unitScale);
}

void SoundEffect::NextChannel()
{
    if (++m_currentChannel >= m_channelEnd)
    {
        m_currentChannel = m_channelBegin;
    }
}
