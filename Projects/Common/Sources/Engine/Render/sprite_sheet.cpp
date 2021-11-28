#include "sprite_sheet.h"

SpriteSheet::SpriteSheet(Texture2D* texture, Shader shader, size_t spritesCount)
    : m_texture(texture), m_shader(shader), m_spritesCount(spritesCount)
{
}

Sprite SpriteSheet::get_sprite(size_t num, vec2 scale, bool flipX, bool flipY) const
{
    scale *= vec2(1.0f / m_spritesCount, 1);
    return Sprite(m_texture, m_shader, vec2(static_cast<float>(num) / m_spritesCount, 0), scale, flipX, flipY);
}

size_t SpriteSheet::get_count() const
{
    return m_spritesCount;
}

float SpriteSheet::get_aspect_ratio() const
{
    return m_texture->get_aspect_ratio() / m_spritesCount;
}

vec2 SpriteSheet::get_normalized_scale() const
{
    auto aspectRatio = get_aspect_ratio();
    return aspectRatio < 1 ? vec2(aspectRatio, 1) : vec2(1, 1 / aspectRatio);
}
