#include "texture2d.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static bool is_power_of_2(int x) 
{
  return x > 0 && !(x & (x - 1));
}

Texture2D::Texture2D(const string &path,
  TextureColorFormat colorFormat, 
  TextureFormat textureFormat, 
  TexturePixelFormat pixelFormat,
  TextureWrappFormat wrapping, 
  bool generate_mips)
{
  generateMips = generate_mips;
  textureType = TextureType::Texture2DType;
  
  glGenTextures(1, &textureObject);

  textureName = path;
  int w, h, ch;
  stbi_set_flip_vertically_on_load(true);
  auto image = stbi_load(path.c_str(), &w, &h, &ch, 0);
  if (image)
  {
    bool powerOfTwo = is_power_of_2(w) && is_power_of_2(h);

    glBindTexture(textureType, textureObject);
    textureWidth = w;
    textureHeight = h;

    size_t size = sizeof(image[0]);
    switch(textureFormat)
    {
      case TextureFormat::UnsignedByte:
      if (size == 1) 
        glTexImage2D(textureType, 0, colorFormat, textureWidth, textureHeight, 0, colorFormat, textureFormat, image);
      else
        debug_error("Wrong sizeof for texture format");
      break; 
    }
    if (!powerOfTwo && wrapping != TextureWrappFormat::ClampToEdge)
    {
      glTexParameteri(textureType, GL_TEXTURE_WRAP_S, wrapping);
      glTexParameteri(textureType, GL_TEXTURE_WRAP_T, wrapping);
    }
    if (generateMips)
    {
      glGenerateMipmap(textureType);
      GLenum mipmapMinPixelFormat = pixelFormat == TexturePixelFormat::Linear ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_NEAREST;
      GLenum mipmapMagPixelFormat = pixelFormat == TexturePixelFormat::Linear ? GL_LINEAR : GL_NEAREST;
      
      glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, mipmapMinPixelFormat);
      glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, mipmapMagPixelFormat);
    }
    else
    {
      GLenum minMagixelFormat = pixelFormat == TexturePixelFormat::Linear ? GL_LINEAR : GL_NEAREST;
      glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, minMagixelFormat);
      glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, minMagixelFormat);
    }
    glBindTexture(textureType, 0); 
    stbi_image_free(image);
  }
  else
  {
    debug_error("Can't load texture %s!",textureName.c_str());
    return;
  }
}
