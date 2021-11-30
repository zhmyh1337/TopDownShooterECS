#include <ecs/ecs.h>
#include <Engine/transform2d.h>
#include <Engine/time.h>
#include "constants.h"
#include "sprites_pool.h"
#include "sprite_sheets_pool.h"

template<typename Callable>
void getSoldierFeet(Callable);

template<typename Callable>
void getSoldierBody(Callable);

template<typename Callable>
void getDebugCircle(Callable);

SYSTEM(ecs::SystemOrder::RENDER - 1, ecs::Tag soldier) UpdateSoldierParts(
    const Transform2D& transform, bool isIdling, bool isRunning, float firstStepTime,
    const SpritesPool& sp, const SpriteSheetsPool& ssp)
{
    const Transform2D& soldierTransform = transform;

    vec2 pos0, pos1, pos2;
    QUERY(ecs::Tag debugCircle) getDebugCircle([&](Transform2D& transform, const int& id) {
        switch (id)
        {
        case 0:
            transform.position = soldierTransform.get_matrix() * vec4(
                consts::sprites::soldier_rifle::muzzlePosition, vec2(1));
            pos0 = transform.position;
            break;

        case 1:
            transform.position = soldierTransform.get_matrix() * vec4(
                consts::sprites::soldier_rifle::shoulderPosition, vec2(1));
            pos1 = transform.position;
            break;

        case 2:
            transform.position = soldierTransform.position;
            pos2 = transform.position;
            break;

        default:
            break;
        }
    });

    QUERY(ecs::Tag soldierFeet) getSoldierFeet([&soldierTransform, isIdling, isRunning, firstStepTime, &sp, &ssp](
        Sprite& sprite,
        Transform2D& transform)
    {
        transform.rotation = soldierTransform.rotation;
        constexpr auto scaleFactor = 0.7f;
        if (isIdling)
        {
            sprite = sp.soldierFeetIdle;
            transform.scale = vec2(sp.soldierFeetIdle.texture->get_aspect_ratio() * 1.2f, 1.2f) * scaleFactor;
        }
        else
        {
            const auto& spriteSheet = isRunning ? ssp.soldierFeetRun : ssp.soldierFeetWalk;
            constexpr auto indexMultiplier = 25.0f;
            auto spriteIndex = static_cast<size_t>(std::floor((Time::time() - firstStepTime) * indexMultiplier))
                % spriteSheet.get_count();
            sprite = spriteSheet.get_sprite(spriteIndex);
            transform.scale = vec2(spriteSheet.get_aspect_ratio(), 1.0f) * scaleFactor;
        }
        transform.position = soldierTransform.get_matrix() * vec4(-0.2f, -0.25f, 1.0f, 1.0f);
    });

    QUERY(ecs::Tag soldierBody) getSoldierBody([&soldierTransform, isIdling, firstStepTime, &ssp](
        Sprite& sprite,
        Transform2D& transform)
    {
        transform.position = soldierTransform.position;
        transform.rotation = soldierTransform.rotation;
        const SpriteSheet* spriteSheet = nullptr;
        float indexMultiplier = 10.0f;
        if (isIdling)
        {
            spriteSheet = &ssp.soldierRifleIdle;
            indexMultiplier = 10.0f;
        }
        else
        {
            spriteSheet = &ssp.soldierRifleMove;
            indexMultiplier = 20.0f;
        }

        const auto spriteIndexDeltaTime = isIdling ? Time::time() : Time::time() - firstStepTime;
        auto spriteIndex = static_cast<size_t>(std::floor(spriteIndexDeltaTime * indexMultiplier))
            % spriteSheet->get_count();
        sprite = spriteSheet->get_sprite(spriteIndex);
        transform.scale = vec2(spriteSheet->get_aspect_ratio(), 1.0f);
    });
}
