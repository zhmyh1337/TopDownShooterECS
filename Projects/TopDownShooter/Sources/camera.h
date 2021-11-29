#pragma once

#include <ecs/ecs.h>
#include <Engine/transform2d.h>

class Camera : ecs::Singleton
{
public:
    mat4 projection;
    vec3 zoom;
    Transform2D transform;

    void Init(mat4 projection, vec3 zoom);
    void UpdateTransformScale();
};
