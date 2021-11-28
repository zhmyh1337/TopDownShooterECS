#pragma once
#include "Texture/texture2d.h"
#include "3dmath.h"

struct Sprite
{
  Texture2D *texture;
  Shader shader;
  vec2 offset, scale;
  bool flipX, flipY;
  Sprite(): texture(nullptr), shader{}, offset(0), scale(1), flipX(false), flipY(false)
  {

  }
  Sprite(Texture2D *texture, Shader shader, vec2 offset, vec2 scale, bool flipX = false, bool flipY = false): 
  texture(texture), shader(shader), offset(offset), scale(scale), flipX(flipX), flipY(flipY)
  {
    
  }
  Sprite(Texture2D *texture, Shader shader, bool flipX = false, bool flipY = false): 
  texture(texture), shader(shader), offset(0), scale(1), flipX(flipX), flipY(flipY)
  {
    
  }
};