#include "sprite_sheet.h"

SpriteSheet::SpriteSheet(Texture2D* texture, Shader shader, size_t spritesCount, float spriteWidth, float spriteHeight)
    : m_texture(texture), m_shader(shader), m_spritesCount(spritesCount), m_spriteWidth(spriteWidth), m_spriteHeight(spriteHeight)
{
}

Sprite SpriteSheet::get_sprite(size_t num, vec2 scale, bool flipX, bool flipY) const
{
    scale *= vec2(m_spriteWidth / m_texture->width(), 1);
    return Sprite(m_texture, m_shader, vec2(static_cast<float>(num) / m_spritesCount, 0), scale, flipX, flipY);
}

size_t SpriteSheet::get_count() const
{
    return m_spritesCount;
}

float SpriteSheet::get_aspect_ratio() const
{
    return m_spriteWidth / m_spriteHeight;
}
