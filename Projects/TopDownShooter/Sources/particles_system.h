#pragma once

#include <glm/glm.hpp>

struct EntityEmitBloodEvent
{
    glm::vec2 momentumVelocity = glm::vec2(0);
    bool isLethal = true;
};
