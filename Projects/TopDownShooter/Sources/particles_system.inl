#include <ecs/ecs.h>
#include <Engine/time.h>
#include <Engine/Render/sprite.h>
#include <Engine/transform2d.h>
#include "sprite_sheets_pool.h"
#include "random.h"
#include "particles_system.h"

static constexpr auto k_bloodParticleStopAtLifeCycleState = 0.05f;
static constexpr auto k_bloodParticleStartDisappearingAtLifeCycleState = 0.7f;

SYSTEM(ecs::SystemOrder::LOGIC, ecs::Tag particle) UpdateParticles(ecs::EntityId eid, float& lifeCycleState, const float lifeTime)
{
    lifeCycleState += Time::delta_time() / lifeTime;
    if (lifeCycleState >= 1)
    {
        ecs::destroy_entity(eid);
        return;
    }
}

SYSTEM(ecs::SystemOrder::LOGIC + 1, ecs::Tag particle, ecs::Tag blood) UpdateBloodParticles(
    const float lifeCycleState, vec4& color, vec2& velocity, vec2& acceleration, Sprite& sprite, const SpriteSheetsPool& ssp)
{
    if (lifeCycleState > k_bloodParticleStopAtLifeCycleState)
    {
        velocity = acceleration = vec2(0);
    }

    color.a = glm::clamp(
        1 - (lifeCycleState - k_bloodParticleStartDisappearingAtLifeCycleState) / (1 - k_bloodParticleStartDisappearingAtLifeCycleState),
        0.0f,
        1.0f);

    sprite = ssp.blood.get_sprite(glm::clamp(static_cast<size_t>(
        std::floor(lifeCycleState * ssp.blood.get_count() / k_bloodParticleStopAtLifeCycleState)),
        size_t(0),
        ssp.blood.get_count() - 1));
}

EVENT() EntityEmitBlood(const EntityEmitBloodEvent& event, const Transform2D& transform)
{
    constexpr auto particleLifeTime = 7.5f;
    auto particleTransform = transform;
    particleTransform.scale *= event.isLethal ? 1.0f : 0.3f;
    std::uniform_real_distribution<float> minusPlusOneUniform(-1, 1);
    const auto particleVelocity = event.momentumVelocity/*  +
        vec2(minusPlusOneUniform(Random::Get()), minusPlusOneUniform(Random::Get())) * 0.5f */;
    particleTransform.rotation = std::atan2(particleVelocity.y, particleVelocity.x) - PIHALF;
    const auto particleAcceleration = -particleVelocity / particleLifeTime / k_bloodParticleStopAtLifeCycleState;
    ecs::create_entity<Sprite, vec4, int, float, float, Transform2D, vec2, vec2, ecs::Tag, ecs::Tag>(
        {"sprite", {}},
        {"color", vec4(vec3(0.75f), 1)},
        {"renderOrder", -1},
        {"lifeCycleState", 0.0f},
        {"lifeTime", particleLifeTime},
        {"transform", particleTransform},
        {"velocity", particleVelocity},
        {"acceleration", particleAcceleration},
        {"particle", {}},
        {"blood", {}}
    );
}
