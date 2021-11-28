#pragma once

#include "Texture/texture2d.h"
#include "sprite.h"

class SpriteSheet
{
public:
    SpriteSheet() : m_texture{}, m_shader{} {}

    SpriteSheet(Texture2D* texture, Shader shader, size_t spritesCount);

    Sprite get_sprite(size_t num, vec2 scale = vec2(1), bool flipX = false, bool flipY = false) const;

    size_t get_count() const;

    float get_aspect_ratio() const;

    vec2 get_normalized_scale() const;

private:
    Texture2D* m_texture;
    Shader m_shader;
    size_t m_spritesCount;
};
