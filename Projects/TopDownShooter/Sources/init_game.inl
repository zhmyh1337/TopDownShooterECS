#include <ecs/ecs.h>
#include <Application/application.h>
#include <Application/application_data.h>
#include <Engine/Render/world_renderer.h>
#include <Engine/Render/sprite.h>
#include <Engine/Render/Shader/shader.h>
#include <Engine/transform2d.h>
#include "sprites_pool.h"
#include "camera.h"
#include "init_game_event.h"
#include "game_data.h"

static void InitCamera(WorldRenderer &wr, Camera& camera)
{
    auto resolution = Application::get_context().get_screen_resolution();
    wr.resolution = vec2(resolution.x, resolution.y);
    auto orthoScale = 1.f / 100.f; // 100 pixels per unit
    auto projectionMatrix = glm::ortho(
        -static_cast<float>(resolution.x), static_cast<float>(resolution.x), 
        -static_cast<float>(resolution.y), static_cast<float>(resolution.y));
    camera.Init(projectionMatrix, vec3(orthoScale * 1.0f, orthoScale * 1.5f, 1 / 10.f));
}

static void InitEntities(const SpritesPool &sp)
{
    ecs::create_entity<Sprite, Transform2D, int, ecs::Tag>(
        {"sprite", sp.background},
        {"transform", {}},
        {"renderOrder", -9},
        {"background", {}}
    );

    ecs::create_entity<Sprite, Transform2D, int>(
        {"sprite", Sprite(nullptr, get_shader("quad_shader"))},
        {"transform", {}},
        {"renderOrder", 9}
    );

    /*
    for (int i = 0; i < 3; i++)
    {
        ecs::create_entity<Sprite, Transform2D, vec4, int, ecs::Tag, int>(
            {"sprite", sp.circle},
            {"transform", Transform2D(vec2(), vec2(0.1f))},
            {"color", vec4(1, 0, 0, 1)},
            {"renderOrder", 1},
            {"debugCircle", {}},
            {"id", i}
        );
    }
    */

    ecs::create_entity<Transform2D, vec2, vec2, float, float, bool, bool, float, float, int, bool, ecs::Tag, ecs::Tag>(
        {"transform", {}},
        {"velocity", {}},
        {"viewDirection", {}},
        {"health", 1.0f},
        {"lastDamageReceivedTime", -std::numeric_limits<float>::infinity()},
        {"isIdling", true},
        {"isRunning", false},
        {"firstStepTime", {}},
        {"lastShotTime", {}},
        {"shootingState", -1},
        {"canShoot", true},
        {"soldier", {}},
        {"localPlayer", {}}
    );

    ecs::create_entity<Sprite, vec4, Transform2D, size_t, ecs::Tag, ecs::Tag>(
        {"sprite", {}},
        {"color", {}},
        {"transform", {}},
        {"lastSpriteIndex", -1},
        {"soldierPart", {}},
        {"soldierFeet", {}}
    );

    ecs::create_entity<Sprite, vec4, Transform2D, ecs::Tag, ecs::Tag>(
        {"sprite", {}},
        {"color", {}},
        {"transform", {}},
        {"soldierPart", {}},
        {"soldierBody", {}}
    );
}

EVENT() InitGame(
    const InitGameEvent &event,
    GameData& gameData,
    WorldRenderer &wr,
    SpritesPool& sp,
    Camera& camera)
{
    InitCamera(wr, camera);
    InitEntities(sp);
    gameData = {};
}
