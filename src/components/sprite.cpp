#include "components/sprite.hpp"

#include "utils.hpp"

namespace rh::C {

Sprite::Sprite(const Subtexture& subtexture)
:
	Sprite(subtexture, {255, 255, 255, SDL_ALPHA_OPAQUE})
{
}

Sprite::Sprite(const Subtexture& subtexture, SDL_Color color)
:
	_subtexture{subtexture},
	_color{color},
	_blend_mode{DEFAULT_BLEND_MODE}
{
}

auto Sprite::subtexture() -> Subtexture
{
	return _subtexture;
}

auto Sprite::rect(SDL_Rect rect) -> void
{
	auto sdl_texture = _subtexture.raw();
	_subtexture = Subtexture{sdl_texture, to_frect(rect)};
}

auto Sprite::rect() const -> SDL_Rect
{
	return to_rect(_subtexture.rect());
}

auto Sprite::color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) -> void
{
	_color = SDL_Color{r, g, b, a};
}

auto Sprite::color(SDL_Color color) -> void
{
	_color = color;
}

auto Sprite::color() const -> SDL_Color
{
	return _color;
}

auto Sprite::blend_mode(SDL_BlendMode blend_mode) -> void
{
	_blend_mode = blend_mode;
}

auto Sprite::blend_mode() const -> SDL_BlendMode
{
	return _blend_mode;
}

auto Sprite::apply_color() const -> void
{
	SDL_SetTextureColorMod(_subtexture.raw(), _color.r, _color.g, _color.b);
	SDL_SetTextureAlphaMod(_subtexture.raw(), _color.a);
}

auto Sprite::apply_blend_mode() const -> void
{
	SDL_SetTextureBlendMode(_subtexture.raw(), _blend_mode);
}

auto Sprite::apply_all() const -> void
{
	apply_color();
	apply_blend_mode();
}

} // namespace rh::C

