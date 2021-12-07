#include "sound_effect.h"
#include <common.h>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <glm/gtx/norm.hpp>

SoundEffect::SoundEffect()
{
}

SoundEffect::SoundEffect(Mix_Chunk* mixChunk, int firstChannelIndex, size_t channelsCount)
    : m_mixChunk(mixChunk)
{
    m_reservedChannels.reserve(channelsCount);
    for (int i = firstChannelIndex; i < firstChannelIndex + static_cast<int>(channelsCount); i++)
    {
        m_reservedChannels.emplace_back(i);
    }
}

void SoundEffect::AddToPlaybackQueue(int uniqueId, glm::vec2 position)
{
    m_playbackQueue.push_back({ .uniqueId = uniqueId, .position = position });
}

void SoundEffect::PlayAll(const glm::vec2& earPosition)
{
    for (auto& channel : m_reservedChannels)
    {
        channel.Update();
    }

    struct PlayableData
    {
        bool isContinuing;
        glm::vec2 position;
        int uniqueId;
    };

    // Avoiding allocations every frame
    static std::unordered_map<int, PlayableData> uniqueIdToPosition;
    uniqueIdToPosition.clear();
    for (const auto& channel : m_reservedChannels)
    {
        if (channel.m_isPlaying)
        {
            uniqueIdToPosition[channel.m_uniqueId] = PlayableData
            {
                .isContinuing = true,
                .position = channel.m_position,
                .uniqueId = channel.m_uniqueId
            };
        }
    }
    for (const auto& playbackQueueData : m_playbackQueue)
    {
        uniqueIdToPosition[playbackQueueData.uniqueId] = PlayableData
        {
            .isContinuing = false,
            .position = playbackQueueData.position,
            .uniqueId = playbackQueueData.uniqueId
        };
    }

    // Avoiding allocations every frame
    static std::vector<PlayableData> playableCandidates;
    playableCandidates.clear();
    std::ranges::transform(uniqueIdToPosition, std::back_inserter(playableCandidates),
        [](const std::pair<int, PlayableData>& data)
        {
            return data.second;
        });
    std::ranges::sort(playableCandidates, {}, [&earPosition](const PlayableData& playableCandidate) {
        return glm::length2(playableCandidate.position - earPosition);
    });
    playableCandidates.resize(std::min(playableCandidates.size(), m_reservedChannels.size()));

    // Avoiding allocations every frame
    static std::unordered_set<int> continuingUniqueIds;
    continuingUniqueIds.clear();
    for (const auto& playable : playableCandidates)
    {
        if (playable.isContinuing)
        {
            continuingUniqueIds.insert(playable.uniqueId);
        }
    }

    auto reservedChannelsIterator = m_reservedChannels.begin();
    auto playableCandidatesIterator = playableCandidates.begin();
    while (playableCandidatesIterator != playableCandidates.end())
    {
        if (playableCandidatesIterator->isContinuing)
        {
            playableCandidatesIterator++;
            continue;
        }

        if (reservedChannelsIterator->m_isPlaying &&
            continuingUniqueIds.contains(reservedChannelsIterator->m_uniqueId))
        {
            reservedChannelsIterator++;
            continue;
        }

        reservedChannelsIterator->PlayChunkAtPosition(
            m_mixChunk, playableCandidatesIterator->uniqueId, playableCandidatesIterator->position, earPosition);
        reservedChannelsIterator++;
        playableCandidatesIterator++;
    }

    for (; reservedChannelsIterator != m_reservedChannels.end(); reservedChannelsIterator++)
    {
        if (reservedChannelsIterator->m_isPlaying &&
            !continuingUniqueIds.contains(reservedChannelsIterator->m_uniqueId))
        {
            reservedChannelsIterator->Stop();
        }
    }

    /*
    debug_log("%zu/%zu sound channels are being played",
        std::ranges::count(m_reservedChannels, true, [](const auto& channel) { return channel.m_isPlaying; }),
        m_reservedChannels.size());
    */

    m_playbackQueue.clear();
}
