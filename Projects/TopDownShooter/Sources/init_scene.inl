#include <ecs/ecs.h>
#include <Application/application.h>
#include <Application/application_data.h>
#include <Engine/Render/world_renderer.h>
#include <Engine/Render/Shader/shader.h>
#include <Engine/transform2d.h>
#include "game_structs.h"
#include "camera.h"

EVENT() InitScene(
    const ecs::OnSceneCreated &event,
    WorldRenderer &wr,
    SpriteFactory &sf,
    Camera& camera)
{
    auto resolution = Application::get_context().get_screen_resolution();
    wr.resolution = vec2(resolution.x, resolution.y);
    float orthoScale = 1.f / 100.f; // 100 pixel per unit
    mat3 projection(0.f);
    projection[0][0] = 1.f / resolution.x;
    projection[1][1] = 1.f / resolution.y;

    camera.Init(projection, vec3(orthoScale * 1.0f, orthoScale * 2.5f, 1 / 10.f));

    auto backgroundTexture = wr.add_texture(new Texture2D(project_resources_path("background.jpg"), TextureColorFormat::RGB, TextureFormat::UnsignedByte, TexturePixelFormat::Linear, TextureWrappFormat::Repeat, true));
    auto standardShader = get_shader("standard_shader");
    sf.background = Sprite(backgroundTexture, standardShader/*, vec2{}, vec2(resolution.x, resolution.y) * orthoScale * 0.9f*/);

    ecs::create_entity<Sprite, Transform2D, ecs::Tag>(
        {"sprite", sf.background},
        {"transform", {}},
        {"background", {}}
    );

    debug_log("scene %s created", event.scene_name.c_str());
}
