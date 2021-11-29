#pragma once
#include <string>
#include <vector>
#include "Texture/texture2d.h"
#include "Shader/shader.h"
#include <ecs/singleton.h>
#include "vertex_array_object.h"

class WorldRenderer : ecs::Singleton
{
public:
  mat4 screenToWorld;
  ivec2 resolution;
  VertexArrayObject quadVao;
  WorldRenderer();

  vec2 screen_to_world(int x, int y) const;
};