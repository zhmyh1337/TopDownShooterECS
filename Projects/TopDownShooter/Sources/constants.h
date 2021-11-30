#pragma once

#include <glm/glm.hpp>

namespace consts
{
    namespace sprites
    {
        struct soldier_rifle
        {
            static constexpr auto muzzlePosition = glm::vec2(1.5f, -0.46f);
            static constexpr auto shoulderPosition = glm::vec2(0.f, -0.46f);
        };
    }
}
