#shader standard_shader

#vertex_shader

layout(location = 0) in vec2 Position;

out vec2 uv;

uniform mat4 mvp;
uniform vec4 uvOffsetScale;

void main() 
{
    uv = (Position + vec2(1, 1)) * 0.5;
    uv = uvOffsetScale.xy + uv * uvOffsetScale.zw;
    gl_Position = mvp * vec4(Position, 1, 1);
}

#pixel_shader

in vec2 uv;
out vec4 outColor;

uniform sampler2D sprite;
uniform vec4 color;

void main()
{
    outColor = color * texture(sprite, uv);
}