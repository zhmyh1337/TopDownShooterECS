#include <ecs/ecs.h>
#include <Engine/Render/world_renderer.h>
#include <Engine/Render/sprite.h>
#include "camera.h"

SYSTEM(ecs::SystemOrder::LOGIC + 2, ecs::Tag localPlayer) UpdateCameraPosition(
    const Transform2D& transform, Camera& camera)
{
    camera.transform.position = transform.position;
}

SYSTEM(ecs::SystemOrder::LOGIC + 3, ecs::Tag background) UpdateBackground(
    Sprite& sprite, Transform2D& transform, const Camera& camera, const WorldRenderer& wr)
{
    constexpr auto backgroundScalingConstant = 0.05f;
    transform.position = camera.transform.position;
    transform.scale = camera.transform.scale * vec2(wr.resolution.x, wr.resolution.y);
    sprite.scale = transform.scale * backgroundScalingConstant;
    sprite.offset = 0.5f * (backgroundScalingConstant * camera.transform.position - sprite.scale);
}
