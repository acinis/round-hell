#include "subtexture.hpp"

#include <cassert>
#include <stdexcept>

#include "errors.hpp"

namespace rh {

Subtexture::Subtexture(SDL_Texture *texture, float x, float y, float w, float h) noexcept
:
	_texture {texture},
	_x {x},
	_y {y},
	_w {w},
	_h {h}
{
	assert(texture && "rh::Subtexture::Subtexture(): `nullptr` passed as `texture`");
	assert((x >= 0.0f) && "rh::Subtexture::Subtexture(): `x` is less than zero");
	assert((y >= 0.0f) && "rh::Subtexture::Subtexture(): `y` is less than zero");
	assert((w >= 0.0f) && "rh::Subtexture::Subtexture(): `w` is less than zero");
	assert((h >= 0.0f) && "rh::Subtexture::Subtexture(): `h` is less than zero");
}

Subtexture::Subtexture(SDL_Texture *texture, SDL_FPoint offset, SDL_FPoint size) noexcept
:
	Subtexture(texture, offset.x, offset.y, size.x, size.y)
{
}

Subtexture::Subtexture(SDL_Texture *texture, SDL_FRect rect) noexcept
:
	Subtexture(texture, rect.x, rect.y, rect.w, rect.h)
{
}

Subtexture::Subtexture(SDL_Texture *texture)
:
	Subtexture(texture, 0.0f, 0.0f, 0.0f, 0.0f)
{
	float w {0.0f};
	float h {0.0f};

	if (! SDL_GetTextureSize(raw(), &w, &h)) {
		throw std::runtime_error{make_sdl_error().to_string()};
	}

	_w = w;
	_h = h;
}

Subtexture::Subtexture(SDL_Texture *texture, float w, float h) noexcept
:
	Subtexture(texture, 0.0f, 0.0f, w, h)
{
}

Subtexture::Subtexture(SDL_Texture *texture, SDL_FPoint size) noexcept
:
	Subtexture(texture, 0.0f, 0.0f, size.x, size.y)
{
}

auto Subtexture::raw() noexcept -> SDL_Texture*
{
	return _texture;
}

auto Subtexture::offset() const noexcept -> SDL_FPoint
{
	return SDL_FPoint{_x, _y};
}

auto Subtexture::size() const noexcept -> SDL_FPoint
{
	return SDL_FPoint{_w, _h};
}

auto Subtexture::rect() const noexcept -> SDL_FRect
{
	return SDL_FRect{_x, _y, _w, _h};
}

auto Subtexture::x() const noexcept -> float
{
	return _x;
}

auto Subtexture::y() const noexcept -> float
{
	return _y;
}

auto Subtexture::w() const noexcept -> float
{
	return _w;
}

auto Subtexture::h() const noexcept -> float
{
	return _h;
}

} // namespace rh

