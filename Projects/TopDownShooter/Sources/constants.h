#pragma once

#include <glm/glm.hpp>

namespace consts
{
    namespace sprites
    {
        struct soldier_rifle
        {
            static constexpr auto muzzlePosition = glm::vec2(1.375f, -0.46f);
            static constexpr auto shoulderPosition = glm::vec2(0.f, -0.46f);
            static constexpr auto timePerShootFrame = 1.0f / 10;
        };
    }

    namespace physics
    {
        struct bullet
        {
            static constexpr auto initialVelocity = 15.0f;
            static constexpr auto lifeTime = 5.0f;
        };
    }

    struct soldier
    {
        static constexpr auto fireCooldown = 1.0f / 10;
    };
}
