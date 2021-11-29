#include <ecs/ecs.h>
#include <Engine/input.h>
#include <Engine/time.h>
#include <Engine/Render/world_renderer.h>
#include "camera.h"

EVENT() ChangeZoom(const MouseWheelEvent &event, Camera& camera)
{
    camera.zoom.z = glm::clamp(camera.zoom.z - event.wheel * 0.05f, 0.f, 1.f);
    camera.UpdateTransformScale();
}

SYSTEM(ecs::SystemOrder::LOGIC, ecs::Tag localPlayer) ProcessLocalPlayerMovement(
    vec2& velocity, bool& isIdling, bool& isRunning, float& firstStepTime)
{
    constexpr auto scalarVelocity = 2.5f;
    constexpr auto runningVelocityBoost = 1.75f;
    
    auto directionVector = vec2(
        Input::get_key_state(SDLK_d) - Input::get_key_state(SDLK_a),
        Input::get_key_state(SDLK_w) - Input::get_key_state(SDLK_s));
    auto normalizedVector = directionVector == vec2(0.0f) ? vec2(0.0f) : glm::normalize(directionVector);
    velocity = scalarVelocity * normalizedVector;
    auto wasIdling = isIdling;
    if ((isIdling = velocity == vec2(0.0f)))
    {
        isRunning = false;
    }
    else
    {
        if (wasIdling)
        {
            firstStepTime = Time::time();
        }
        if ((isRunning = Input::get_key_state(SDLK_LSHIFT)))
        {
            velocity *= runningVelocityBoost;
        }
    }
}

SYSTEM(ecs::SystemOrder::LOGIC, ecs::Tag localPlayer) LocalPlayerViewToMouse(
    vec2& viewDirection, Transform2D& transform, const WorldRenderer& wr)
{
    auto mousePosition = Input::get_mouse_position();
    auto worldPosition = wr.screen_to_world(mousePosition.x, mousePosition.y);
    viewDirection = glm::normalize(worldPosition - transform.position);
    transform.rotation = atan2f(viewDirection.y, viewDirection.x);
}
