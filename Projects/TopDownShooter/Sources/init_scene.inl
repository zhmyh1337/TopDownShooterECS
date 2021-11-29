#include <ecs/ecs.h>
#include <Application/application.h>
#include <Application/application_data.h>
#include <Engine/Render/world_renderer.h>
#include <Engine/Render/sprite.h>
#include <Engine/Render/Shader/shader.h>
#include <Engine/transform2d.h>
#include "textures_pool.h"
#include "sprites_pool.h"
#include "sprite_sheets_pool.h"
#include "camera.h"

static void InitCamera(WorldRenderer &wr, Camera& camera)
{
    auto resolution = Application::get_context().get_screen_resolution();
    wr.resolution = vec2(resolution.x, resolution.y);
    auto orthoScale = 1.f / 100.f; // 100 pixels per unit
    auto projectionMatrix = glm::ortho(
        -static_cast<float>(resolution.x), static_cast<float>(resolution.x), 
        -static_cast<float>(resolution.y), static_cast<float>(resolution.y));
    camera.Init(projectionMatrix, vec3(orthoScale * 1.0f, orthoScale * 2.0f, 1 / 10.f));
}

static void InitTexturesPool(TexturesPool &tp)
{
    tp.background = new Texture2D(
        project_resources_path("background.jpg"),
        TextureColorFormat::RGB,
        TextureFormat::UnsignedByte,
        TexturePixelFormat::Linear,
        TextureWrappFormat::Repeat,
        true);
    tp.soldierFeetIdle = new Texture2D(project_resources_path("soldier_feet_idle.png"), TextureColorFormat::RGBA);
    tp.soldierFeetWalk = new Texture2D(project_resources_path("soldier_feet_walk.png"), TextureColorFormat::RGBA);
    tp.soldierFeetRun = new Texture2D(project_resources_path("soldier_feet_run.png"), TextureColorFormat::RGBA);
    tp.soldierRifleIdle = new Texture2D(project_resources_path("soldier_rifle_idle.png"), TextureColorFormat::RGBA);
    tp.soldierRifleMove = new Texture2D(project_resources_path("soldier_rifle_move.png"), TextureColorFormat::RGBA);
    tp.soldierRifleReload = new Texture2D(project_resources_path("soldier_rifle_reload.png"), TextureColorFormat::RGBA);
    tp.soldierRifleMeleeAttack = new Texture2D(project_resources_path("soldier_rifle_meleeattack.png"), TextureColorFormat::RGBA);
    tp.soldierRifleShoot = new Texture2D(project_resources_path("soldier_rifle_shoot.png"), TextureColorFormat::RGBA);
    tp.circle = new Texture2D(project_resources_path("circle.png"), TextureColorFormat::RGBA);
}

static void InitSpritesPool(const TexturesPool &tp, SpritesPool& sp)
{
    sp.soldierFeetIdle = Sprite(tp.soldierFeetIdle, get_shader("standard_shader"));
    sp.circle = Sprite(tp.circle, get_shader("standard_shader"));
}

static void InitSpriteSheetsPool(const TexturesPool &tp, SpriteSheetsPool& ssp)
{
    ssp.soldierFeetWalk = SpriteSheet(tp.soldierFeetWalk, get_shader("standard_shader"), 20);
    ssp.soldierFeetRun = SpriteSheet(tp.soldierFeetRun, get_shader("standard_shader"), 20);
    ssp.soldierRifleIdle = SpriteSheet(tp.soldierRifleIdle, get_shader("standard_shader"), 20);
    ssp.soldierRifleMove = SpriteSheet(tp.soldierRifleMove, get_shader("standard_shader"), 20);
    ssp.soldierRifleReload = SpriteSheet(tp.soldierRifleReload, get_shader("standard_shader"), 20);
    ssp.soldierRifleMeleeAttack = SpriteSheet(tp.soldierRifleMeleeAttack, get_shader("standard_shader"), 15);
    ssp.soldierRifleShoot = SpriteSheet(tp.soldierRifleShoot, get_shader("standard_shader"), 3);
}

static void InitEntities(const TexturesPool &tp)
{
    ecs::create_entity<Sprite, Transform2D, int, ecs::Tag>(
        {"sprite", Sprite(tp.background, get_shader("standard_shader"))},
        {"transform", {}},
        {"renderOrder", -1},
        {"background", {}}
    );

    ecs::create_entity<Sprite, Transform2D, vec4, int, ecs::Tag>(
        {"sprite", Sprite(tp.circle, get_shader("standard_shader"))},
        {"transform", Transform2D(vec2(), vec2(0.1f))},
        {"color", vec4(1, 0, 0, 1)},
        {"renderOrder", 999},
        {"debugCircle", {}}
    );

    ecs::create_entity<Transform2D, vec2, vec2, bool, bool, float, ecs::Tag, ecs::Tag>(
        {"transform", {}},
        {"velocity", {}},
        {"viewDirection", {}},
        {"isIdling", true},
        {"isRunning", false},
        {"firstStepTime", {}},
        {"soldier", {}},
        {"localPlayer", {}}
    );

    ecs::create_entity<Sprite, Transform2D, ecs::Tag, ecs::Tag>(
        {"sprite", {}},
        {"transform", {}},
        {"soldierPart", {}},
        {"soldierFeet", {}}
    );

    ecs::create_entity<Sprite, Transform2D, ecs::Tag, ecs::Tag>(
        {"sprite", {}},
        {"transform", {}},
        {"soldierPart", {}},
        {"soldierBody", {}}
    );
}

EVENT() InitScene(
    const ecs::OnSceneCreated &event,
    WorldRenderer &wr,
    TexturesPool &tp,
    SpritesPool& sp,
    SpriteSheetsPool &ssp,
    Camera& camera)
{
    InitCamera(wr, camera);
    InitTexturesPool(tp);
    InitSpritesPool(tp, sp);
    InitSpriteSheetsPool(tp, ssp);
    InitEntities(tp);

    debug_log("scene %s created", event.scene_name.c_str());
}
