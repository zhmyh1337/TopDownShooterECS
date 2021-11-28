#include <ecs/ecs.h>
#include <Engine/input.h>
#include <Engine/time.h>
#include <Engine/Render/world_renderer.h>
#include <Engine/Render/sprite.h>
#include "sprite_sheets_pool.h"
#include "camera.h"

SYSTEM(ecs::SystemOrder::RENDER - 1) next_sprite(Sprite& sprite, size_t& spriteIndex, float& lastStepTime, const SpriteSheetsPool& ssp)
{
    size_t delta = std::floor((Time::time() - lastStepTime) * 50);
    if (delta)
    {
        spriteIndex = (spriteIndex + delta) % ssp.soldierFeetRun.get_count();
        sprite = ssp.soldierFeetRun.get_sprite(spriteIndex);
        lastStepTime = Time::time();
    }
}

SYSTEM(ecs::SystemOrder::RENDER - 2) move_camera(Camera& camera)
{
    auto velocity = vec2(Input::get_key_state(SDLK_d) - Input::get_key_state(SDLK_a), Input::get_key_state(SDLK_w) - Input::get_key_state(SDLK_s));
    camera.transform.position += 5.f * Time::delta_time() * velocity;
}

SYSTEM(ecs::SystemOrder::RENDER - 1, ecs::Tag background) setup_background(
    Sprite& sprite, Transform2D& transform, const Camera& camera, const WorldRenderer& wr)
{
    constexpr auto backgroundScalingConstant = 0.05f;
    transform.position = camera.transform.position;
    transform.scale = camera.transform.scale * vec2(wr.resolution.x, wr.resolution.y);
    sprite.scale = transform.scale * backgroundScalingConstant;
    sprite.offset = 0.5f * (backgroundScalingConstant * camera.transform.position - sprite.scale);
}

EVENT() change_zoom(const MouseWheelEvent &event, Camera& camera)
{
    camera.zoom.z = glm::clamp(camera.zoom.z - event.wheel * 0.05f, 0.f, 1.f);
    camera.UpdateTransformScale();
}
