#pragma once

#include <SDL2/SDL_mixer.h>
#include <glm/glm.hpp>

class SoundChannel
{
public:
    SoundChannel(int index);

    void Update();

    void Stop();

    void PlayChunkAtPosition(Mix_Chunk* chunk, int uniqueId, const glm::vec2& position, const glm::vec2& earPosition);

public:
    bool m_isPlaying = false;
    int m_uniqueId = 0;
    glm::vec2 m_position = glm::vec2();

private:
    int m_index;
};
