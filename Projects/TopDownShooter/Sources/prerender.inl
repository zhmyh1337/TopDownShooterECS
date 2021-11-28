#include <ecs/ecs.h>
#include <Engine/transform2d.h>
#include <Engine/time.h>
#include "sprites_pool.h"
#include "sprite_sheets_pool.h"

template<typename Callable>
void getSoldierFeet(Callable);

SYSTEM(ecs::SystemOrder::RENDER - 1, ecs::Tag soldier) UpdateSoldierParts(
    const Transform2D& transform, bool isIdling, bool isRunning, float firstStepTime,
    const SpritesPool& sp, const SpriteSheetsPool& ssp)
{
    const Transform2D& soldierTransform = transform;
    QUERY(ecs::Tag soldierFeet) getSoldierFeet([&soldierTransform, isIdling, isRunning, firstStepTime, &sp, &ssp](
        Sprite& sprite,
        Transform2D& transform)
    {
        transform.position = soldierTransform.position;
        if (isIdling)
        {
            sprite = sp.soldierFeetIdle;
            transform.scale = vec2(sp.soldierFeetIdle.texture->get_aspect_ratio() * 1.2f, 1.15f);
            return;
        }
        
        const auto& spriteSheet = isRunning ? ssp.soldierFeetRun : ssp.soldierFeetWalk;
        constexpr auto indexMultiplier = 30.0f;
        auto spriteIndex = static_cast<size_t>(std::floor((Time::time() - firstStepTime) * indexMultiplier))
            % spriteSheet.get_count();
        sprite = spriteSheet.get_sprite(spriteIndex);
        transform.scale = vec2(spriteSheet.get_aspect_ratio(), 1.0f);
    });
}
