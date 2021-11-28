#include <ecs/ecs.h>
#include <Engine/transform2d.h>
#include <Engine/time.h>

SYSTEM(ecs::SystemOrder::LOGIC + 1) MoveEntitiesWithVelocity(Transform2D &transform, const vec2 &velocity)
{
    transform.position += velocity * Time::delta_time();
}
