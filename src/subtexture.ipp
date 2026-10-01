#include <cassert>
#include <stdexcept>

#include "errors.hpp"

namespace rh {

template<SdlTexturePointerLike TextureHandleType>
BasicSubtexture<TextureHandleType>::BasicSubtexture(TextureHandleType texture, float x, float y, float w, float h) noexcept
:
	_texture {texture},
	_x {x},
	_y {y},
	_w {w},
	_h {h}
{
	assert(texture && "rh::BasicSubtexture::BasicSubtexture(): Invalid `texture` passed to constructor");
	assert((x >= 0.0f) && "rh::BasicSubtexture::BasicSubtexture(): `x` is less than zero");
	assert((y >= 0.0f) && "rh::BasicSubtexture::BasicSubtexture(): `y` is less than zero");
	assert((w >= 0.0f) && "rh::BasicSubtexture::BasicSubtexture(): `w` is less than zero");
	assert((h >= 0.0f) && "rh::BasicSubtexture::BasicSubtexture(): `h` is less than zero");
}

template<SdlTexturePointerLike TextureHandleType>
BasicSubtexture<TextureHandleType>::BasicSubtexture(TextureHandleType texture, SDL_FPoint offset, SDL_FPoint size) noexcept
:
	BasicSubtexture(texture, offset.x, offset.y, size.x, size.y)
{
}

template<SdlTexturePointerLike TextureHandleType>
BasicSubtexture<TextureHandleType>::BasicSubtexture(TextureHandleType texture, SDL_FRect rect) noexcept
:
	BasicSubtexture(texture, rect.x, rect.y, rect.w, rect.h)
{
}

template<SdlTexturePointerLike TextureHandleType>
BasicSubtexture<TextureHandleType>::BasicSubtexture(TextureHandleType texture)
:
	BasicSubtexture(texture, 0.0f, 0.0f, 0.0f, 0.0f)
{
	float w {0.0f};
	float h {0.0f};

	if (! SDL_GetTextureSize(raw(), &w, &h)) {
		throw std::runtime_error{make_sdl_error().to_string()};
	}

	_w = w;
	_h = h;
}

template<SdlTexturePointerLike TextureHandleType>
BasicSubtexture<TextureHandleType>::BasicSubtexture(TextureHandleType texture, float w, float h) noexcept
:
	BasicSubtexture(texture, 0.0f, 0.0f, w, h)
{
}

template<SdlTexturePointerLike TextureHandleType>
BasicSubtexture<TextureHandleType>::BasicSubtexture(TextureHandleType texture, SDL_FPoint size) noexcept
:
	BasicSubtexture(texture, 0.0f, 0.0f, size.x, size.y)
{
}

template<SdlTexturePointerLike TextureHandleType>
auto BasicSubtexture<TextureHandleType>::handle() noexcept -> TextureHandleType
{
	return _texture;
}

template<SdlTexturePointerLike TextureHandleType>
auto BasicSubtexture<TextureHandleType>::raw() noexcept -> SDL_Texture*
{
	return _texture.handle().get();
}

template<SdlTexturePointerLike TextureHandleType>
auto BasicSubtexture<TextureHandleType>::offset() const noexcept -> SDL_FPoint
{
	return SDL_FPoint{_x, _y};
}

template<SdlTexturePointerLike TextureHandleType>
auto BasicSubtexture<TextureHandleType>::size() const noexcept -> SDL_FPoint
{
	return SDL_FPoint{_w, _h};
}

template<SdlTexturePointerLike TextureHandleType>
auto BasicSubtexture<TextureHandleType>::rect() const noexcept -> SDL_FRect
{
	return SDL_FRect{_x, _y, _w, _h};
}

template<SdlTexturePointerLike TextureHandleType>
auto BasicSubtexture<TextureHandleType>::x() const noexcept -> float
{
	return _x;
}

template<SdlTexturePointerLike TextureHandleType>
auto BasicSubtexture<TextureHandleType>::y() const noexcept -> float
{
	return _y;
}

template<SdlTexturePointerLike TextureHandleType>
auto BasicSubtexture<TextureHandleType>::w() const noexcept -> float
{
	return _w;
}

template<SdlTexturePointerLike TextureHandleType>
auto BasicSubtexture<TextureHandleType>::h() const noexcept -> float
{
	return _h;
}

} // namespace rh

