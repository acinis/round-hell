#ifndef ROUNDHELL_COMPONENTS_SPRITE_HPP
#define ROUNDHELL_COMPONENTS_SPRITE_HPP

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_blendmode.h>

#include "subtexture.hpp"

namespace rh::C {

// Sprite component used in SpriteRenderer.
// Sprite has assigned texture and optionally texture rectangle.
// Texture rectangle is set to texture size by default.
// ATTENTION Texture must be created, loaded and freed elsewhere (but be valid
// as long as some sprite wants to use it).

class Sprite
{
public:
	static inline constexpr SDL_BlendMode DEFAULT_BLEND_MODE = SDL_BLENDMODE_BLEND;

private:
	mutable Subtexture _subtexture;
	SDL_Color _color;
	SDL_BlendMode _blend_mode;

public:
	Sprite() = delete;

	Sprite(const Subtexture& subtexture);
	Sprite(const Subtexture& subtexture, SDL_Color color);

	Sprite(const Sprite&) = default;
	Sprite(Sprite&&) = default;
	auto operator=(const Sprite&) -> Sprite& = default;
	auto operator=(Sprite&&) -> Sprite& = default;

	~Sprite() = default;

	auto subtexture() -> Subtexture;

	auto rect(SDL_Rect rect) -> void;
	auto rect() const -> SDL_Rect;

	auto color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = SDL_ALPHA_OPAQUE) -> void;
	auto color(SDL_Color color) -> void;
	auto color() const -> SDL_Color;

	auto blend_mode(SDL_BlendMode blend_mode) -> void;
	auto blend_mode() const -> SDL_BlendMode;

	// Setters/getters do *not* change anything on texture (cos many sprites can use same texture).
	// You must call `apply_*()` methods to affect texture (these will call appropriate SDL's
	// functions).
	// TODO Apply methods can be more automatic? Maybe combine `apply_all()` with subtexture getter?
	// TODO Track last applied texture properties, and do *not* call relevant SDL functions again with same arguments.
	auto apply_color() const -> void;
	auto apply_blend_mode() const -> void;
	auto apply_all() const -> void;
};

} // namespace rh::C

#endif // ROUNDHELL_COMPONENTS_SPRITE_HPP

