#shader quad_shader

#vertex_shader

layout(location = 0) in vec2 Position;

uniform mat4 mvp;

void main() 
{
    gl_Position = mvp * vec4(Position, 1, 1);
}

#pixel_shader

out vec4 outColor;

uniform vec4 color;

void main()
{
    outColor = color;
}
