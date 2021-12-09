#shader standard_shader

#vertex_shader

layout(location = 0) in vec2 Position;

out vec2 uv;
out vec2 world;

uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;
uniform vec4 uvOffsetScale;

void main()
{
    uv = (Position + vec2(1, 1)) * 0.5;
    uv = uvOffsetScale.xy + uv * uvOffsetScale.zw;
    const vec4 world4 = modelMatrix * vec4(Position, 1, 1);
    world = world4.xy;
    gl_Position = viewProjectionMatrix * world4;
}

#pixel_shader

in vec2 uv;
in vec2 world;
out vec4 outColor;

uniform sampler2D sprite;
uniform vec4 color;

uniform vec2 viewDirection;
uniform vec2 localPlayerPosition;
uniform vec2 flashlightPosition;
uniform float fullDarknessLevel;
uniform float fov;

void SetPrimitiveShadows()
{
    const vec2 vecFromLocalPlayer = world - localPlayerPosition;
    const vec2 vecFromFlashlight = world - flashlightPosition;
    const vec2 vecFromFlashlightNormalized = normalize(vecFromFlashlight);
    const float angle = acos(clamp(dot(viewDirection, vecFromFlashlightNormalized), -1, 1));
    outColor.rgb *=
        max(
            (1 - (1 - fullDarknessLevel) * smoothstep(fov, fov + fov * 0.2, angle)) *
                (1 - 0.01 * dot(vecFromFlashlight, vecFromFlashlight)),
            1 - 0.1 * dot(vecFromLocalPlayer, vecFromLocalPlayer));
}

void main()
{
    outColor = color * texture(sprite, uv);
    SetPrimitiveShadows();
}
