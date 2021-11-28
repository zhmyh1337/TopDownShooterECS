#pragma once
#include "../Shader/shader.h"
enum TextureType
{
  Texture2DType = GL_TEXTURE_2D
};
enum TextureColorFormat
{
  R = GL_RED,
  RG = GL_RG,
  RGB = GL_RGB,
  RGBA = GL_RGBA
};
enum TextureFormat
{
  UnsignedByte =  GL_UNSIGNED_BYTE
};
enum TextureWrappFormat
{
  Repeat = GL_REPEAT,
  ClampToEdge = GL_CLAMP_TO_EDGE,
  ClampToBorder = GL_CLAMP_TO_BORDER
};
enum TexturePixelFormat
{
  Pixel,
  Linear
};
class Texture
{
  
protected:
  GLuint textureObject, textureType;
  int textureWidth, textureHeight;
  string textureName;
public:
  Texture():textureObject(0){}
  void bind(const Shader &shader, const char * textureName, int slot) const;
  const string &get_name() const;
  uint get_texture_object() const;
  void dispose();
  int width() const;
  int height() const;
  
};