#include <ecs/ecs.h>
#include <Engine/Render/world_renderer.h>
#include <Engine/Render/Shader/shader.h>
#include <Engine/transform2d.h>
#include <Engine/Render/sprite.h>
#include <Engine/time.h>
#include "camera.h"

template<typename Callable>
void gatherSprites(Callable);

template<typename Callable>
void getLocalPlayerTransform(Callable);

template<typename Callable>
void getLocalPlayerHealth(Callable);

SYSTEM(ecs::SystemOrder::RENDER) RenderScene(WorldRenderer &wr, const Camera &camera)
{
    auto viewProjection = camera.projection * glm::inverse(camera.transform.get_matrix());
    wr.screenToWorld = camera.transform.get_matrix();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    struct Renderable
    {
        std::reference_wrapper<const Sprite> sprite;
        std::reference_wrapper<const Transform2D> transform;
        int renderOrder;
        const vec4* color;
    };

    static std::vector<Renderable> renderables;
    renderables.clear();

    QUERY() gatherSprites([&viewProjection](
        const Sprite& sprite,
        const Transform2D& transform,
        const int* renderOrder,
        const vec4* color)
    {
        // culling
        vec2 minPos = viewProjection * vec4(transform.position - transform.scale * 0.5f, 1, 1);
        vec2 maxPos = viewProjection * vec4(transform.position + transform.scale * 0.5f, 1, 1);
        if (1.f < minPos.x || 1.f < minPos.y || maxPos.x < -1.f || maxPos.y < -1.f)
        {
            return;
        }

        if (!sprite.texture)
        {
            return;
        }

        renderables.push_back({
            .sprite = std::cref(sprite),
            .transform = std::cref(transform),
            .renderOrder = renderOrder ? *renderOrder : 0,
            .color = color
        });
    });

    std::stable_sort(renderables.begin(), renderables.end(), [](const Renderable& lhs, const Renderable& rhs) {
        return lhs.renderOrder < rhs.renderOrder || (lhs.renderOrder == rhs.renderOrder &&
            lhs.sprite.get().shader.get_id() < rhs.sprite.get().shader.get_id());
    });

    for (auto it = renderables.cbegin(); it != renderables.cend(); it++)
    {
        const auto& renderable = *it;
        const auto& sprite = renderable.sprite.get();
        const auto& transform = renderable.transform.get();
        const auto& shader = sprite.shader;
        /* const bool isSpriteShader = sprite.texture != nullptr; */
        static int mvpUniformLocation;
        static int uvOffsetScaleUniformLocation;
        static int colorUniformLocation;
        if (it == renderables.cbegin() ||
            shader.get_id() != std::prev(it)->sprite.get().shader.get_id())
        {
            shader.use();
            mvpUniformLocation = shader.get_uniform_location("mvp");
            colorUniformLocation = shader.get_uniform_location("color");
            /* if (isSpriteShader) */
            {
                uvOffsetScaleUniformLocation = shader.get_uniform_location("uvOffsetScale");
            }
        }

        shader.set_mat4x4(mvpUniformLocation, viewProjection * transform.get_matrix());
        shader.set_vec4(colorUniformLocation, renderable.color ? *renderable.color : vec4(1.f));
        /* if (isSpriteShader) */
        {
            shader.set_vec4(uvOffsetScaleUniformLocation, vec4(sprite.offset, sprite.scale));
            sprite.texture->bind(shader, "sprite", 0);
        }
        wr.quadVao.render();
    }

    {
        // fog
        const auto shader = get_shader("fog_shader");
        shader.use();
        shader.set_mat4x4(shader.get_uniform_location("viewProjectionInversed"), glm::inverse(viewProjection));
        QUERY(ecs::Tag localPlayer) getLocalPlayerTransform([&shader](const Transform2D& transform)
        {
            shader.set_vec2(shader.get_uniform_location("localPlayerPosition"), transform.position);
        });
        shader.set_float(shader.get_uniform_location("time"), Time::time());
        shader.set_float(shader.get_uniform_location("visibleDistance"), 12.5f);
        wr.quadVao.render();
    }

    {
        // healthbar
        const auto shader = get_shader("healthbar_shader");
        static Transform2D transform(vec2(1.0f - 0.2f - 0.01f, -0.95f), vec2(0.2f, 0.0275f));
        static auto transformMatrix = transform.get_matrix();
        constexpr auto borderThicknessYRatio = 0.1f;
        shader.use();
        QUERY(ecs::Tag localPlayer) getLocalPlayerHealth([&shader](const float health)
        {
            shader.set_float(shader.get_uniform_location("health"), glm::clamp(health, 0.0f, 1.0f));
        });
        shader.set_mat4x4(shader.get_uniform_location("transform"), transformMatrix);
        shader.set_vec4(shader.get_uniform_location("backgroundColor"), vec4(vec3(0), 1));
        shader.set_vec2(shader.get_uniform_location("borderThickness"),
            borderThicknessYRatio * vec2(transform.scale.y / transform.scale.x * wr.resolution.y / wr.resolution.x, 1));
        wr.quadVao.render();
    }

    glEnable(GL_DEPTH_TEST);
}
