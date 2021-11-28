#pragma once

#include "texture.h"

class Texture2D : public Texture
{
  bool generateMips;
  void load_from_path(const std::string &path);
public:
  Texture2D();
  Texture2D(const string &texture_path_from_textures_folder,
  TextureColorFormat color_format = TextureColorFormat::RGB, 
  TextureFormat texture_format = TextureFormat::UnsignedByte, 
  TexturePixelFormat pixelFormat = TexturePixelFormat::Linear,
  TextureWrappFormat wrapping = TextureWrappFormat::Repeat, 
  bool generate_mips = false);
};
