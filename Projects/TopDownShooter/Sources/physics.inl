#include <ecs/ecs.h>
#include <Engine/transform2d.h>
#include <Engine/time.h>
#include "game_data.h"
#include "particles_system.h"
#include "audio_pool.h"

template<typename Callable>
void gatherTargets(Callable);

SYSTEM(ecs::SystemOrder::LOGIC + 1) MoveEntities(
    Transform2D &transform, vec2 &velocity, const vec2* acceleration)
{
    if (acceleration)
    {
        velocity += *acceleration * Time::delta_time();
    }
    transform.position += velocity * Time::delta_time();
}

SYSTEM(ecs::SystemOrder::LOGIC + 2, ecs::Tag bullet) BulletCollisionDetection(
    ecs::EntityId eid, const Transform2D& transform, GameData& gameData, const vec2& velocity, AudioPool& ap)
{
    const auto bulletRadius = transform.get_radius();
    const auto bulletEid = eid;
    const auto& bulletTransform = transform;
    QUERY(ecs::Tag enemy) gatherTargets([bulletEid, bulletRadius, &bulletTransform, &gameData, &velocity, &ap](
        ecs::EntityId eid, const Transform2D& transform)
    {
        auto targetRadius = transform.get_radius();
        auto dist = glm::length(transform.position - bulletTransform.position);
        if (dist < bulletRadius + targetRadius)
        {
            ecs::send_event_immediate(eid, EntityEmitBloodEvent { .momentumVelocity = velocity * 0.1f });
            ap.bulletDamage.AddToPlaybackQueue(
                static_cast<int>(SoundEffect::UniqueIds::EnemyTakesBulletDamageBegin) +
                    gameData.killsCount % 1'000'000,
                bulletTransform.position);
            ecs::destroy_entity(bulletEid);
            ecs::destroy_entity(eid);
            gameData.killsCount++;
        }
    });
}
