#include "world_renderer.h"

WorldRenderer::WorldRenderer()
{
  vector<uint> indices = {0,1,2,0,2,3};
  vector<vec2> corners =  {vec2(-1, -1), vec2(1,-1), vec2(1,1),vec2(-1,1)};
  quadVao = VertexArrayObject(indices, corners);
}

Texture2D *WorldRenderer::add_texture(Texture2D *texture)
{
  if (texture)
    textures.emplace_back(texture);
  return texture;
}

Texture2D *WorldRenderer::get_texture(const std::string &name)
{
  for (Texture2D *texture : textures)
    if (texture->get_name() == name)
      return texture;
  return nullptr;
}

vec2 WorldRenderer::screen_to_world(int x, int y) const
{
  vec3 screenPos(x*2 - resolution.x, resolution.y - y*2, 1);
  return screenToWorld * screenPos;
}