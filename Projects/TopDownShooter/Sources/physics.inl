#include <ecs/ecs.h>
#include <Engine/transform2d.h>
#include <Engine/time.h>
#include "game_logic.h"

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
    ecs::EntityId eid, const Transform2D& transform, const vec2& velocity)
{
    const auto bulletRadius = transform.get_radius();
    const auto bulletEid = eid;
    const auto& bulletTransform = transform;
    QUERY(ecs::Tag enemy) gatherTargets([bulletEid, bulletRadius, &bulletTransform, &velocity](
        ecs::EntityId eid, const Transform2D& transform)
    {
        auto targetRadius = transform.get_radius();
        auto dist = glm::length(transform.position - bulletTransform.position);
        if (dist < bulletRadius + targetRadius)
        {
            ecs::send_event_immediate(eid, EnemyGotShotEvent
            {
                .hitPosition = bulletTransform.position,
                .hitMomentumVelocity = velocity
            });
            ecs::destroy_entity(bulletEid);
        }
    });
}
