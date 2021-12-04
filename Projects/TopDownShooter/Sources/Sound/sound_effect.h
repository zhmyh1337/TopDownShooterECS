#pragma once

#include <SDL2/SDL_mixer.h>
#include <glm/glm.hpp>
#include <string_view>

class SoundEffect
{
public:
    SoundEffect();

    SoundEffect(Mix_Chunk* mixChunk, int channelBegin, int channelEnd);

    void Play();

    void PlayAtVector(const glm::vec2& vec);

private:
    void PlayImpl();

    void SetPosition(const glm::vec2& vec);

    void NextChannel();

private:
    static constexpr auto k_unitScale = 10.0f;

    Mix_Chunk* m_mixChunk;
    int m_currentChannel;
    int m_channelBegin;
    int m_channelEnd;
};
