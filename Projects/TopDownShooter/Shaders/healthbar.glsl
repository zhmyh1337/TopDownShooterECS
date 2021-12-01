#shader healthbar_shader
#vertex_shader

layout(location = 0)in vec2 Position;

out vec2 uv;

uniform mat4 transform;

void main() 
{
    uv = (Position + vec2(1, 1)) * 0.5;
    gl_Position = transform * vec4(Position, 1, 1);
}

#pixel_shader

in vec2 uv;
out vec4 outColor;

uniform float health;
uniform vec4 backgroundColor;
uniform vec2 borderThickness;

void main()
{
    const float uvHealth = (uv.x - borderThickness.x) / (1 - borderThickness.x * 2);
    if (uvHealth >= 0 && uvHealth <= health && uv.y >= borderThickness.y && uv.y <= 1 - borderThickness.y)
    {
        outColor = vec4(1 - uvHealth, uvHealth, 0, 1);
    }
    else
    {
        outColor = vec4(0, 0, 0, 1);
    }
}
