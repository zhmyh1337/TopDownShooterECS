#include <ecs/ecs.h>
#include <Engine/input.h>
#include <Engine/time.h>
#include <Engine/Render/world_renderer.h>
#include "camera.h"
#include "constants.h"
#include "sprites_pool.h"
#include "sprite_sheets_pool.h"
#include "game_data.h"

EVENT() ChangeZoom(const MouseWheelEvent &event, Camera& camera)
{
    camera.zoom.z = glm::clamp(camera.zoom.z - event.wheel * 0.05f, 0.f, 1.f);
    camera.UpdateTransformScale();
}

SYSTEM(ecs::SystemOrder::LOGIC, ecs::Tag localPlayer) ProcessLocalPlayerMovement(
    vec2& velocity, bool& isIdling, bool& isRunning, float& firstStepTime, const GameData& gameData)
{
    if (gameData.isGameOver)
    {
        return;
    }

    constexpr auto scalarVelocity = 3.0f;
    constexpr auto runningVelocityBoost = 2.0f;
    
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
    vec2& viewDirection, Transform2D& transform, const WorldRenderer& wr, const GameData& gameData)
{
    if (gameData.isGameOver)
    {
        return;
    }

    // spent about four hours doing this maths :)
    auto mouse = Input::get_mouse_position();
    auto mouseWorld = wr.screen_to_world(mouse.x, mouse.y);
    viewDirection = glm::normalize(mouseWorld - transform.position);
    auto shoulderWorldDistance = glm::length(consts::sprites::soldier_rifle::shoulderPosition * transform.scale);
    auto mouseWorldDistance = glm::length(mouseWorld - transform.position);
    auto gammaAngle = std::atan2(viewDirection.y, viewDirection.x);
    auto betaAngle = glm::acos(glm::clamp(shoulderWorldDistance / mouseWorldDistance, -1.0f, 1.0f));
    transform.rotation = gammaAngle - betaAngle + PIHALF;
}

SYSTEM(ecs::SystemOrder::LOGIC + 2, ecs::Tag localPlayer) LocalPlayerShoot(
    const Transform2D& transform, int& shootingState, float& lastShotTime, bool& canShoot,
    const SpritesPool& sp, const SpriteSheetsPool& ssp, const GameData& gameData)
{
    if (gameData.isGameOver)
    {
        return;
    }

    if (shootingState != -1)
    {
        const auto deltaTime = Time::time() - lastShotTime;
        shootingState = static_cast<int>(std::floor(
            deltaTime / consts::sprites::soldier_rifle::timePerShootFrame));
        if (shootingState >= static_cast<int>(ssp.soldierRifleShoot.get_count()))
        {
            shootingState = -1;
            canShoot = true;
        }
    }

    if (shootingState == 1 && canShoot)
    {
        auto muzzlePosition = vec2(
            transform.get_matrix() * vec4(consts::sprites::soldier_rifle::muzzlePosition, vec2(1)));
        auto shoulderPosition = vec2(
            transform.get_matrix() * vec4(consts::sprites::soldier_rifle::shoulderPosition, vec2(1)));
        auto directionVector = glm::normalize(muzzlePosition - shoulderPosition);
        ecs::create_entity<Sprite, Transform2D, vec2, int, float, ecs::Tag>(
            {"sprite", sp.bullet},
            {"transform", Transform2D(muzzlePosition, vec2(1.f, 0.35f) * 0.5f, std::atan2(directionVector.y, directionVector.x))},
            {"velocity", directionVector * consts::physics::bullet::initialVelocity},
            {"renderOrder", 1},
            {"creationTime", Time::time()},
            {"bullet", {}}
        );
        canShoot = false;
    }

    if (Input::get_mouse_button_state(MouseButton::LeftButton) && shootingState == -1 &&
        lastShotTime + consts::soldier::fireCooldown < Time::time())
    {
        lastShotTime = Time::time();
        shootingState = 0;
    }
}
