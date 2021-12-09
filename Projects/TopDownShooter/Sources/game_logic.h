#pragma once

#include <glm/glm.hpp>

struct EnemyGotShotEvent
{
    glm::vec2 hitPosition;
    glm::vec2 hitMomentumVelocity = glm::vec2(0);
};
