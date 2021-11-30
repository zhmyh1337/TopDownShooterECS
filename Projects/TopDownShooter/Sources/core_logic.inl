#include <ecs/ecs.h>
#include <Engine/time.h>
#include "constants.h"

SYSTEM(ecs::SystemOrder::LOGIC - 1, ecs::Tag bullet) DestroyOldBullets(ecs::EntityId eid, float creationTime)
{
    if (creationTime + consts::physics::bullet::lifeTime < Time::time())
    {
        ecs::destroy_entity(eid);
    }
}
