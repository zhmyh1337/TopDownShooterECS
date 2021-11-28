#pragma once

#include <ecs/ecs.h>
#include <Engine/transform2d.h>

class Camera : ecs::Singleton
{
public:
    mat3 projection;
    vec3 zoom;
    Transform2D transform;

    void Init(mat3 projection, vec3 zoom);
    void UpdateTransformScale();
};
