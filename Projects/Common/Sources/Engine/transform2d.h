#pragma once
#include "3dmath.h"

struct Transform2D
{
  vec2 position, scale;
  //in radians
  float rotation;
  Transform2D(vec2 position = vec2(0.f), vec2 scale = vec2(1.f), float rotation = 0):
    position(position), scale(scale), rotation(rotation)
  {}
  mat3 get_matrix() const;
};