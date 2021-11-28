#include "texture.h"

void Texture::bind(const Shader &shader, const char * textureName, int slot) const
{
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(textureType, textureObject);
  glUniform1i(glGetUniformLocation(shader.get_shader_program(), textureName), slot);
}
const string &Texture::get_name() const
{
  return textureName;
}
void Texture::dispose()
{
  glDeleteTextures(1, &textureObject);
  textureName = "Bad texture";
}
int Texture::width() const
{
  return textureWidth;
}
int Texture::height() const
{
  return textureHeight;
}
float Texture::get_aspect_ratio() const
{
  return static_cast<float>(width()) / height();
}
vec2 Texture::get_normalized_scale() const
{
  auto aspectRatio = get_aspect_ratio();
  return aspectRatio < 1 ? vec2(aspectRatio, 1) : vec2(1, 1 / aspectRatio);
}
uint Texture::get_texture_object() const
{
  return textureObject;
}
