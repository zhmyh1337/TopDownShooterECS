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

SYSTEM(ecs::SystemOrder::LOGIC + 4, ecs::Tag soldier) UpdateSoldierParts(
    const Transform2D& transform, float lastDamageReceivedTime,
    bool isIdling, bool isRunning, float firstStepTime, int shootingState,
    const SpritesPool& sp, const SpriteSheetsPool& ssp)
{
    const Transform2D& soldierTransform = transform;

    const auto colorBlueGreenChannel = glm::clamp(Time::time() - lastDamageReceivedTime, 0.0f, 1.0f);
    const auto colorFilter = vec4(1, colorBlueGreenChannel, colorBlueGreenChannel, 1);

    QUERY(ecs::Tag soldierFeet) getSoldierFeet(
        [&soldierTransform, isIdling, isRunning, firstStepTime, &sp, &ssp, &colorFilter](
        Sprite& sprite,
        vec4& color,
        Transform2D& transform)
    {
        color = colorFilter;

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
            constexpr auto indexMultiplier = 15.0f;
            const auto spriteIndex = static_cast<size_t>(std::floor((Time::time() - firstStepTime) * indexMultiplier))
                % spriteSheet.get_count();
            sprite = spriteSheet.get_sprite(spriteIndex);
            transform.scale = vec2(spriteSheet.get_aspect_ratio(), 1.0f) * scaleFactor;
        }
        transform.position = soldierTransform.get_matrix() * vec4(-0.2f, -0.25f, 1.0f, 1.0f);
    });

    QUERY(ecs::Tag soldierBody) getSoldierBody(
        [&soldierTransform, isIdling, firstStepTime, shootingState, &ssp, &colorFilter](
        Sprite& sprite,
        vec4& color,
        Transform2D& transform)
    {
        color = colorFilter;

        transform.position = soldierTransform.position;
        transform.rotation = soldierTransform.rotation;

        if (shootingState != -1)
        {
            const SpriteSheet& spriteSheet = ssp.soldierRifleShoot;
            sprite = spriteSheet.get_sprite(static_cast<size_t>(shootingState));
            transform.scale = vec2(spriteSheet.get_aspect_ratio(), 1.0f);
            return;
        }

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
        const auto spriteIndex = static_cast<size_t>(std::floor(spriteIndexDeltaTime * indexMultiplier))
            % spriteSheet->get_count();
        sprite = spriteSheet->get_sprite(spriteIndex);
        transform.scale = vec2(spriteSheet->get_aspect_ratio(), 1.0f);
    });
}

SYSTEM(ecs::SystemOrder::LOGIC + 4, ecs::Tag enemy) UpdateEnemySprite(
    Sprite& sprite, const Transform2D& transform, const vec2& velocity, const SpriteSheetsPool& ssp,
    ecs::EntityId eid, const float firstStepTime, int attackState)
{
    if (attackState != -1)
    {
        sprite = ssp.zombieAttack.get_sprite(static_cast<size_t>(attackState));
        return;
    }

    constexpr auto indexMultiplier = 15.0f;
    const auto isIdling = velocity == glm::vec2(0);
    const auto& spriteSheet = isIdling ? ssp.zombieIdle : ssp.zombieMove;
    const auto spriteIndex = static_cast<size_t>(std::floor((Time::time() - firstStepTime) * indexMultiplier)) % spriteSheet.get_count();
    sprite = spriteSheet.get_sprite(spriteIndex);
}
