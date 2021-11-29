#include "world_renderer.h"

WorldRenderer::WorldRenderer()
{
  vector<uint> indices = {0,1,2,0,2,3};
  vector<vec2> corners =  {vec2(-1, -1), vec2(1,-1), vec2(1,1),vec2(-1,1)};
  quadVao = VertexArrayObject(indices, corners);
}

vec2 WorldRenderer::screen_to_world(int x, int y) const
{
  vec4 screenPos(x*2 - resolution.x, resolution.y - y*2, 1, 1);
  return screenToWorld * screenPos;
}
