#include "camera.h"

REG_TYPE(Camera)

void Camera::Init(mat4 projection, vec3 zoom)
{
    this->projection = projection;
    this->zoom = zoom;
    UpdateTransformScale();
}

void Camera::UpdateTransformScale()
{
    transform.scale = vec2(lerp(zoom.x, zoom.y, zoom.z));
}
