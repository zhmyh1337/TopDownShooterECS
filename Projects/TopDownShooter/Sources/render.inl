#include <ecs/ecs.h>
#include <Engine/Render/world_renderer.h>
#include <Engine/Render/Shader/shader.h>
#include <Engine/transform2d.h>
#include <Engine/Render/sprite.h>
#include <Engine/time.h>
#include <ranges>
#include "constants.h"
#include "camera.h"

struct LocalPlayerRenderableInfo
{
    glm::vec2 viewDirection;
    Transform2D transform;
    glm::vec2 flashlightPosition;
    float health;
};

template<typename Callable>
void getLocalPlayerRenderableInfo(Callable);

LocalPlayerRenderableInfo GetLocalPlayerRenderableInfo()
{
    LocalPlayerRenderableInfo result;
    QUERY(ecs::Tag localPlayer) getLocalPlayerRenderableInfo([&](
        const glm::vec2& viewDirection, const Transform2D& transform, const float health)
    {
        result =
        {
            .viewDirection = viewDirection,
            .transform = transform,
            .flashlightPosition = transform.get_matrix() *
                vec4(consts::sprites::soldier_rifle::flashlightPosition, vec2(1)),
            .health = health
        };
    });
    return result;
}

void SetShaderPrimitiveShadowsUniforms(
    const Shader& shader, const LocalPlayerRenderableInfo& localPlayerInfo, float fullDarknessLevel)
{
    shader.set_vec2("viewDirection", localPlayerInfo.viewDirection);
    shader.set_vec2("localPlayerPosition", localPlayerInfo.transform.position);
    shader.set_vec2("flashlightPosition", localPlayerInfo.flashlightPosition);
    shader.set_float("fullDarknessLevel", fullDarknessLevel);
    shader.set_float("fov", PI / 6);
}

template<typename Callable>
void gatherSprites(Callable);

void RenderSprites(const WorldRenderer& wr, const glm::mat4& viewProjection,
    const LocalPlayerRenderableInfo& localPlayerInfo)
{
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
        if (it == renderables.cbegin() ||
            shader.get_id() != std::prev(it)->sprite.get().shader.get_id())
        {
            shader.use();
        }

        shader.set_mat4x4("modelMatrix", transform.get_matrix());
        shader.set_mat4x4("viewProjectionMatrix", viewProjection);
        shader.set_vec4("color", renderable.color ? *renderable.color : vec4(1.f));
        shader.set_vec4("uvOffsetScale", vec4(sprite.offset, sprite.scale));
        SetShaderPrimitiveShadowsUniforms(shader, localPlayerInfo, 0.1f);
        sprite.texture->bind(shader, "sprite", 0);
        wr.quadVao.render();
    }
}

void RenderFog(const WorldRenderer& wr, const glm::mat4& viewProjection,
    const LocalPlayerRenderableInfo& localPlayerInfo)
{
    const auto shader = get_shader("fog_shader");
    shader.use();
    shader.set_mat4x4("viewProjectionInversed", glm::inverse(viewProjection));
    shader.set_float("time", Time::time());
    shader.set_float("visibleDistance", 12.5f);
    SetShaderPrimitiveShadowsUniforms(shader, localPlayerInfo, 0.35f);
    wr.quadVao.render();
}

void RenderHealthBar(const WorldRenderer& wr, const LocalPlayerRenderableInfo& localPlayerInfo)
{
    const auto shader = get_shader("healthbar_shader");
    static Transform2D transform(vec2(1.0f - 0.2f - 0.01f, -0.95f), vec2(0.2f, 0.0275f));
    static auto transformMatrix = transform.get_matrix();
    constexpr auto borderThicknessYRatio = 0.1f;
    shader.use();
    shader.set_float("health", glm::clamp(localPlayerInfo.health, 0.0f, 1.0f));
    shader.set_mat4x4("transform", transformMatrix);
    shader.set_vec4("backgroundColor", vec4(vec3(0), 1));
    shader.set_vec2(
        "borderThickness",
        borderThicknessYRatio * vec2(transform.scale.y / transform.scale.x * wr.resolution.y / wr.resolution.x, 1));
    wr.quadVao.render();
}

template<typename Callable>
void gatherEnemiesTransform(Callable);

SYSTEM(ecs::SystemOrder::RENDER) RenderScene(WorldRenderer &wr, const Camera &camera)
{
    auto viewProjection = camera.projection * glm::inverse(camera.transform.get_matrix());
    wr.screenToWorld = camera.transform.get_matrix();
    auto localPlayerInfo = GetLocalPlayerRenderableInfo();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    RenderSprites(wr, viewProjection, localPlayerInfo);
    RenderFog(wr, viewProjection, localPlayerInfo);
    RenderHealthBar(wr, localPlayerInfo);

    glEnable(GL_DEPTH_TEST);
}
