#ifndef ROUNDHELL_COMPONENTS_ANIMATION_HPP
#define ROUNDHELL_COMPONENTS_ANIMATION_HPP

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>

#include "components/sprite.hpp"

namespace rh::C {

// Simple sprite sheet animation. Each frame must have same size.

class Animation
{
	Uint64 _accumulator; // in ms
	Uint16 _frame_index; // current
	Uint16 _frame_count;
	Uint64 _frame_duration; // in ms
	bool _looped;
	bool _horizontal;

	auto _move_rect(C::Sprite& c_sprite, Uint16 old_frame_index, Uint16 new_frame_index) -> void;

public:

	Animation() = delete;

	// TODO Boolean flags as constructor arguments.
	Animation(Uint16 frame_count, Uint64 frame_duration, bool looped = true, bool horizontal = true);

	Animation(const Animation&) = default;
	Animation(Animation&&) = default;
	Animation& operator=(const Animation&) = default;
	Animation& operator=(Animation&&) = default;

	~Animation() = default;

	auto frame_index(Uint16 frame_index) -> void;
	auto frame_index() const -> Uint16;

	auto frame_count(Uint16 frame_count) -> void;
	auto frame_count() const -> Uint16;

	auto frame_duration(Uint64 frame_duration) -> void;
	auto frame_duration() const -> Uint64;

	auto looped(bool value) -> void;
	auto looped() const -> bool;

	auto horizontal(bool value) -> void;
	auto horizontal() const -> bool;

	auto last_frame_index() const -> Uint16;

	// These will return new frame index.
	auto advance_frame(C::Sprite& c_sprite) -> Uint16;
	auto advance_frame(C::Sprite& c_sprite, Uint16 amount) -> Uint16;

	auto animate(C::Sprite& c_sprite, Uint64 dt) -> void;
};

} // namespace rh::C

#endif // ROUNDHELL_COMPONENTS_ANIMATION_HPP

