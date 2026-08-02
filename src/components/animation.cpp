#include "components/animation.hpp"

#include <cstdlib>

namespace rh::C {

auto Animation::_move_rect(C::Sprite& c_sprite, Uint16 old_frame_index, Uint16 new_frame_index) -> void
{
	auto index_diff = new_frame_index - old_frame_index;
	auto frame_rect = c_sprite.rect();

	if (horizontal()) {
		auto distance = index_diff * frame_rect.w;
		frame_rect.x += distance;
	}
	else {
		auto distance = index_diff * frame_rect.h;
		frame_rect.y += distance;
	}

	c_sprite.rect(frame_rect);
}

Animation::Animation(Uint16 frame_count, Uint64 frame_duration, bool looped, bool horizontal)
:
	_accumulator{0},
	_frame_index{0},
	_frame_count{frame_count},
	_frame_duration{frame_duration},
	_looped{looped},
	_horizontal{horizontal}
{
}

auto Animation::frame_index(Uint16 frame_index) -> void
{
	if (frame_index < _frame_count) {
		_frame_index = frame_index;
	}
}

auto Animation::frame_index() const -> Uint16
{
	return _frame_index;
}

auto Animation::frame_count(Uint16 frame_count) -> void
{
	_frame_count = frame_count;

	// Adjust current frame index
	if (frame_count == 0) {
		_frame_index = 0;
	}
	else if (_frame_index >= frame_count) {
		// Cannot wrap - count is non-zero at this point
		_frame_index = frame_count - 1;
	}
}

auto Animation::frame_count() const -> Uint16
{
	return _frame_count;
}

auto Animation::frame_duration(Uint64 frame_duration) -> void
{
	_frame_duration = frame_duration;
}

auto Animation::frame_duration() const -> Uint64
{
	return _frame_duration;
}

auto Animation::looped(bool value) -> void
{
	_looped = value;
}

auto Animation::looped() const -> bool
{
	return _looped;
}

auto Animation::horizontal(bool value) -> void
{
	_horizontal = value;
}

auto Animation::horizontal() const -> bool
{
	return _horizontal;
}

auto Animation::last_frame_index() const -> Uint16
{
	if (frame_count() == 0) {
		return 0;
	}
	else {
		return frame_count() - 1;
	}
}

auto Animation::advance_frame(C::Sprite& c_sprite) -> Uint16
{
	auto old_frame_index = frame_index();
	auto new_frame_index = old_frame_index + 1;
	if (new_frame_index >= frame_count()) {
		if (looped()) {
			new_frame_index = 0;
		}
		else {
			new_frame_index = last_frame_index();
		}
	}

	frame_index(new_frame_index);
	_move_rect(c_sprite, old_frame_index, new_frame_index);

	return new_frame_index;
}

auto Animation::advance_frame(C::Sprite& c_sprite, Uint16 amount) -> Uint16
{
	auto old_frame_index = _frame_index;

	auto new_frame_index = 0;
	if (looped()) {
		new_frame_index = (old_frame_index + amount) % _frame_count;
	}
	else {
		if (old_frame_index + amount < _frame_count) {
			new_frame_index = old_frame_index + amount;
		}
		else {
			new_frame_index = last_frame_index();
		}
	}

	frame_index(new_frame_index);
	_move_rect(c_sprite, old_frame_index, new_frame_index);

	return new_frame_index;
}

auto Animation::animate(C::Sprite& c_sprite, Uint64 dt) -> void
{
	auto time = _accumulator + dt;
	_accumulator = time % _frame_duration;
	advance_frame(c_sprite, time / _frame_duration);
}

} // namespace rh::C

