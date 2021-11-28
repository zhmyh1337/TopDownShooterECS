#include <ecs/ecs.h>
#include <Application/application.h>
#include <Application/application_data.h>
#include <Engine/Render/world_renderer.h>
#include <Engine/Render/sprite.h>
#include <Engine/Render/Shader/shader.h>
#include <Engine/transform2d.h>
#include "textures_pool.h"
#include "camera.h"

static void InitCamera(WorldRenderer &wr, Camera& camera)
{
    auto resolution = Application::get_context().get_screen_resolution();
    wr.resolution = vec2(resolution.x, resolution.y);
    auto orthoScale = 1.f / 100.f; // 100 pixel per unit
    mat3 projectionMatrix(0.f);
    projectionMatrix[0][0] = 1.f / resolution.x;
    projectionMatrix[1][1] = 1.f / resolution.y;
    camera.Init(projectionMatrix, vec3(orthoScale * 1.0f, orthoScale * 2.5f, 1 / 10.f));
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
}

static void InitEntities(TexturesPool &tp)
{
    ecs::create_entity<Sprite, Transform2D, ecs::Tag>(
        {"sprite", Sprite(tp.background, get_shader("standard_shader"))},
        {"transform", {}},
        {"background", {}}
    );
}

EVENT() InitScene(
    const ecs::OnSceneCreated &event,
    WorldRenderer &wr,
    TexturesPool &tp,
    Camera& camera)
{
    InitCamera(wr, camera);
    InitTextures(tp);
    InitEntities(tp);

    debug_log("scene %s created", event.scene_name.c_str());
}
