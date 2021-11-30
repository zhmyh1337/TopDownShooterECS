#include <ecs/ecs.h>
#include <Engine/transform2d.h>
#include <Engine/time.h>
#include "game_data.h"

template<typename Callable>
void gatherTargets(Callable);

SYSTEM(ecs::SystemOrder::LOGIC + 1) MoveEntitiesWithVelocity(Transform2D &transform, const vec2 &velocity)
{
    transform.position += velocity * Time::delta_time();
}

SYSTEM(ecs::SystemOrder::LOGIC + 2, ecs::Tag bullet) BulletCollisionDetection(
    ecs::EntityId eid, const Transform2D& transform, GameData& gameData)
{
    const auto bulletRadius = transform.get_radius();
    const auto bulletEid = eid;
    const auto& bulletTransform = transform;
    QUERY(ecs::Tag enemy) gatherTargets([bulletEid, bulletRadius, &bulletTransform, &gameData](
        ecs::EntityId eid, const Transform2D& transform)
    {
        auto targetRadius = transform.get_radius();
        auto dist = glm::length(transform.position - bulletTransform.position);
        if (dist < bulletRadius + targetRadius)
        {
            ecs::destroy_entity(bulletEid);
            ecs::destroy_entity(eid);
            gameData.killsCount++;
        }
    });
}
