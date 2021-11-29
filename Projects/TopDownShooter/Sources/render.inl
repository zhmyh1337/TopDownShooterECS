#include <ecs/ecs.h>
#include <Engine/Render/world_renderer.h>
#include <Engine/Render/Shader/shader.h>
#include <Engine/transform2d.h>
#include <Engine/Render/sprite.h>
#include "camera.h"

template<typename Callable>
void gatherSprites(Callable);

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

        if (sprite.texture)
        {
            renderables.push_back({
                .sprite = std::cref(sprite),
                .transform = std::cref(transform),
                .renderOrder = renderOrder ? *renderOrder : 0,
                .color = color
            });
        }
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
        static int mvpUniformLocation;
        static int uvOffsetScaleUniformLocation;
        static int colorUniformLocation;
        if (it == renderables.cbegin() ||
            shader.get_id() != std::prev(it)->sprite.get().shader.get_id())
        {
            shader.use();
            mvpUniformLocation = shader.get_uniform_location("mvp");
            uvOffsetScaleUniformLocation = shader.get_uniform_location("uvOffsetScale");
            colorUniformLocation = shader.get_uniform_location("color");
        }

        sprite.texture->bind(shader, "sprite", 0);
        shader.set_mat4x4(mvpUniformLocation, viewProjection * transform.get_matrix());
        shader.set_vec4(uvOffsetScaleUniformLocation, vec4(sprite.offset, sprite.scale));
        shader.set_vec4(colorUniformLocation, renderable.color ? *renderable.color : vec4(1.f));
        wr.quadVao.render();
    }

    glEnable(GL_DEPTH_TEST);
}
