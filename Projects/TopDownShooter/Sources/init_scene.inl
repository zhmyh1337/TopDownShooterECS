#include <ecs/ecs.h>
#include <Application/application.h>
#include <Application/application_data.h>
#include <Engine/Render/world_renderer.h>
#include <Engine/Render/sprite.h>
#include <Engine/Render/Shader/shader.h>
#include <Engine/transform2d.h>
#include "textures_pool.h"
#include "sprite_sheets_pool.h"
#include "camera.h"

static void InitCamera(WorldRenderer &wr, Camera& camera)
{
    auto resolution = Application::get_context().get_screen_resolution();
    wr.resolution = vec2(resolution.x, resolution.y);
    auto orthoScale = 1.f / 100.f; // 100 pixel per unit
    mat3 projectionMatrix(0.f);
    projectionMatrix[0][0] = 1.f / resolution.x;
    projectionMatrix[1][1] = 1.f / resolution.y;
    camera.Init(projectionMatrix, vec3(orthoScale * 1.0f, orthoScale * 2.0f, 1 / 10.f));
}

static void InitTextures(TexturesPool &tp)
{
    tp.background = new Texture2D(
        project_resources_path("background.jpg"),
        TextureColorFormat::RGB,
        TextureFormat::UnsignedByte,
        TexturePixelFormat::Linear,
        TextureWrappFormat::Repeat,
        true);
    tp.soldierFeetRun = new Texture2D(project_resources_path("soldier_feet_run.png"), TextureColorFormat::RGBA);
}

static void InitSpriteSheets(const TexturesPool &tp, SpriteSheetsPool& ssp)
{
    ssp.soldierFeetRun = SpriteSheet(tp.soldierFeetRun, get_shader("standard_shader"), 20, 204, 124);
}

static void InitEntities(const TexturesPool &tp, const SpriteSheetsPool& ssp)
{
    ecs::create_entity<Sprite, Transform2D, int, ecs::Tag>(
        {"sprite", Sprite(tp.background, get_shader("standard_shader"))},
        {"transform", {}},
        {"renderOrder", -1},
        {"background", {}}
    );

    ecs::create_entity<Sprite, size_t, float, Transform2D, ecs::Tag>(
        {"sprite", ssp.soldierFeetRun.get_sprite(0)},
        {"spriteIndex", 0},
        {"lastStepTime", Time::time()},
        {"transform", Transform2D(vec2{}, vec2(ssp.soldierFeetRun.get_aspect_ratio(), 1.f))},
        {"soldierFeet", {}}
    );
}

EVENT() InitScene(
    const ecs::OnSceneCreated &event,
    WorldRenderer &wr,
    TexturesPool &tp,
    SpriteSheetsPool &ssp,
    Camera& camera)
{
    InitCamera(wr, camera);
    InitTextures(tp);
    InitSpriteSheets(tp, ssp);
    InitEntities(tp, ssp);

    debug_log("scene %s created", event.scene_name.c_str());
}
