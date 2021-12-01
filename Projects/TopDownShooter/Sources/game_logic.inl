#include <ecs/ecs.h>
#include <Engine/time.h>
#include <Engine/Render/sprite.h>
#include "random.h"
#include "camera.h"
#include "sprite_sheets_pool.h"
#include "constants.h"
#include "game_data.h"

SYSTEM(ecs::SystemOrder::LOGIC - 2) SpawnEnemies(GameData& gameData, const Camera& camera)
{
    if (gameData.isGameOver)
    {
        return;
    }

    if (gameData.nextEnemySpawnTime > Time::time())
    {
        return;
    }

    debug_log("Spawning an enemy");
    auto transformationMatrix = camera.transform.get_matrix() * glm::inverse(camera.projection);
    vec2 topLeftCorner = transformationMatrix * vec4(-1, 1, 1, 1);
    vec2 bottomRightCorner = transformationMatrix * vec4(1, -1, 1, 1);
    constexpr glm::vec2 transformScale(1.5f);
    const auto radius = glm::length(transformScale) / 2;
    topLeftCorner += vec2(-1, 1) * radius;
    bottomRightCorner += vec2(1, -1) * radius;
    vec2 spawnPosition;
    switch (Random::Get()() % 4)
    {
    case 0: // top
        spawnPosition = vec2(std::uniform_real_distribution<float>(topLeftCorner.x, bottomRightCorner.x)(Random::Get()), topLeftCorner.y);
        break;

    case 1: // bottom
        spawnPosition = vec2(std::uniform_real_distribution<float>(topLeftCorner.x, bottomRightCorner.x)(Random::Get()), bottomRightCorner.y);
        break;

    case 2: // left
        spawnPosition = vec2(topLeftCorner.x, std::uniform_real_distribution<float>(bottomRightCorner.y, topLeftCorner.y)(Random::Get()));
        break;

    case 3: // right
        spawnPosition = vec2(bottomRightCorner.x, std::uniform_real_distribution<float>(bottomRightCorner.y, topLeftCorner.y)(Random::Get()));
        break;
    }

    ecs::create_entity<Sprite, Transform2D, vec2, vec2, vec2, float, int, bool, ecs::Tag>(
        {"sprite", {}},  
        {"transform", Transform2D(spawnPosition, transformScale)},
        {"roamingDestination", {}},
        {"velocity", {}},
        {"viewDirection", {}},
        {"lastAttackTime", {}},
        {"attackState", -1},
        {"canDamage", true},
        {"enemy", {}}
    );

    auto lambda = 1.5f + gameData.killsCount * 0.05f;
    std::exponential_distribution distribution(lambda);
    auto distributedValue = distribution(Random::Get());
    auto cooldownInSeconds = glm::clamp(distributedValue * 2.0f, 0.0f, 2.0f);
    gameData.nextEnemySpawnTime = Time::time() + cooldownInSeconds;
    debug_log("Waiting %f seconds to spawn an enemy (lambda = %f, distributedValue = %f)",
        cooldownInSeconds, lambda, distributedValue);
}

template<typename Callable>
void gatherEnemies(Callable);

SYSTEM(ecs::SystemOrder::LOGIC - 1, ecs::Tag localPlayer) DirectEnemies(
    const Transform2D& transform, const GameData& gameData)
{
    const auto& localPlayerTransform = transform;
    QUERY(ecs::Tag enemy) gatherEnemies([&localPlayerTransform, &gameData](
        Transform2D& transform, vec2& velocity, vec2& viewDirection, vec2& roamingDestination)
    {
        constexpr auto scalarVelocity = 4.0f;
        if (gameData.isGameOver)
        {
            viewDirection = glm::normalize(roamingDestination - transform.position);
            velocity = viewDirection * scalarVelocity;
        }
        else
        {
            viewDirection = glm::normalize(localPlayerTransform.position - transform.position);
            velocity = glm::length(localPlayerTransform.position - transform.position) > 1.3f
                ? viewDirection * scalarVelocity
                : vec2(0);
        }
        transform.rotation = std::atan2(viewDirection.y, viewDirection.x);
    });
}

SYSTEM(ecs::SystemOrder::LOGIC - 1, ecs::Tag bullet) DestroyOldBullets(ecs::EntityId eid, float creationTime)
{
    if (creationTime + consts::physics::bullet::lifeTime < Time::time())
    {
        ecs::destroy_entity(eid);
    }
}

template<typename Callable>
void gatherLeavingEnemies(Callable);

struct GameOverEvent {};

EVENT(ecs::Tag localPlayer) GameOver(const GameOverEvent& event, const Transform2D& transform, GameData& gameData)
{
    gameData.isGameOver = true;

    const auto& localPlayerTransform = transform;
    QUERY(ecs::Tag enemy) gatherLeavingEnemies([&localPlayerTransform](vec2& roamingDestination, int& attackState)
    {
        attackState = -1;
        constexpr auto leavingRadius = 1e10f;
        const auto angle = std::uniform_real_distribution<float>(0, PITWO)(Random::Get());
        roamingDestination = localPlayerTransform.position + vec2(std::cos(angle), std::sin(angle)) * leavingRadius;
    });
}

struct LocalPlayerReceiveDamageEvent
{
    float damage;
};

EVENT(ecs::Tag localPlayer) LocalPlayerReceiveDamage(const LocalPlayerReceiveDamageEvent& event,
    float& health, float& lastDamageReceivedTime, GameData& gameData)
{
    health -= event.damage;
    lastDamageReceivedTime = Time::time();
    if (health <= 0 && !gameData.isGameOver)
    {
        ecs::send_event_immediate(GameOverEvent());
    }
}

template<typename Callable>
void gatherAttackingEnemies(Callable);

SYSTEM(ecs::SystemOrder::LOGIC + 2, ecs::Tag localPlayer) EnemiesAttack(
    const Transform2D& transform, const SpriteSheetsPool& ssp, const GameData& gameData)
{
    if (gameData.isGameOver)
    {
        return;
    }

    const auto& localPlayerTransform = transform;
    QUERY(ecs::Tag enemy) gatherAttackingEnemies([&localPlayerTransform, &ssp](
        const Transform2D& transform, float& lastAttackTime, int& attackState, bool& canDamage)
    {
        if (attackState != -1)
        {
            const auto deltaTime = Time::time() - lastAttackTime;
            attackState = static_cast<int>(std::floor(
                deltaTime / consts::sprites::zombie::timePerMeleeAttackFrame));
            if (attackState >= static_cast<int>(ssp.zombieAttack.get_count()))
            {
                attackState = -1;
                canDamage = true;
            }
        }

        const auto distToPlayer = glm::length(localPlayerTransform.position - transform.position);
        if (attackState == 5 && canDamage)
        {
            if (distToPlayer < consts::enemy::meleeAttackDamageRange)
            {
                ecs::send_event_immediate(LocalPlayerReceiveDamageEvent{ .damage = consts::enemy::damage });
            }
            canDamage = false;
        }

        if (distToPlayer < consts::enemy::meleeAttackBeginRange && attackState == -1)
        {
            lastAttackTime = Time::time();
            attackState = 0;
        }
    });
}
