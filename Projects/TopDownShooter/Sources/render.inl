#include <ecs/ecs.h>
#include <Engine/Render/world_renderer.h>
#include <Engine/Render/Shader/shader.h>
#include <Engine/transform2d.h>
#include <Engine/Render/sprite.h>
#include "camera.h"

template<typename Callable>
void gatherSprites(Callable);

SYSTEM(ecs::SystemOrder::RENDER) RenderScene(WorldRenderer &wr,const Camera &camera)
{
    auto viewProjection = camera.projection * glm::inverse(camera.transform.get_matrix());
    wr.screenToWorld = camera.transform.get_matrix();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    QUERY() gatherSprites([&](
        const Sprite &sprite,
        const Transform2D &transform,
        const vec4 *color)
    {
        // culling
        vec2 minPos = viewProjection * vec3(transform.position - transform.scale * 0.5f, 1);
        vec2 maxPos = viewProjection * vec3(transform.position + transform.scale * 0.5f, 1);
        if (1.f < minPos.x || 1.f < minPos.y || maxPos.x < -1.f || maxPos.y < -1.f)
        {
            return;
        }

        if (sprite.texture)
        {
            const Shader& sh = sprite.shader;
            sh.use();
            sprite.texture->bind(sh, "sprite", 0);
            sh.set_mat3x3(sh.get_uniform_location("transformViewProjection"), viewProjection * transform.get_matrix());
            sh.set_vec4(sh.get_uniform_location("uvOffsetScale"), vec4(sprite.offset, sprite.scale));
            sh.set_vec4(sh.get_uniform_location("color"), color ? *color : vec4(1.f));
            wr.quadVao.render();
        }
    });

    glEnable(GL_DEPTH_TEST);
}
