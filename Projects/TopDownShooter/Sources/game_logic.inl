#include <ecs/ecs.h>
#include <Engine/time.h>
#include <Engine/Render/sprite.h>
#include "random.h"
#include "camera.h"
#include "constants.h"
#include "game_data.h"

SYSTEM(ecs::SystemOrder::LOGIC - 2) SpawnEnemies(GameData& gameData, const Camera& camera)
{
    if (gameData.nextEnemySpawnTime > Time::time())
    {
        return;
    }

    debug_log("Spawning an enemy");
    auto transformationMatrix = camera.transform.get_matrix() * glm::inverse(camera.projection);
    vec2 topLeftCorner = transformationMatrix * vec4(-1, 1, 1, 1);
    vec2 bottomRightCorner = transformationMatrix * vec4(1, -1, 1, 1);
    constexpr glm::vec2 transformScale(1, 1);
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

    ecs::create_entity<Sprite, Transform2D, vec2, vec2, ecs::Tag>(
        {"sprite", {}},  
        {"transform", Transform2D(spawnPosition, transformScale)},
        {"velocity", {}},
        {"viewDirection", {}},
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

SYSTEM(ecs::SystemOrder::LOGIC - 1, ecs::Tag localPlayer) DirectEnemies(const Transform2D& transform)
{
    const Transform2D& localPlayerTransform = transform;
    QUERY(ecs::Tag enemy) gatherEnemies([&localPlayerTransform](
        Transform2D& transform, vec2& velocity, vec2& viewDirection)
    {
        viewDirection = glm::normalize(localPlayerTransform.position - transform.position);
        velocity = viewDirection * 2.0f;
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
