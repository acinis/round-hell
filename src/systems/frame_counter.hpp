#ifndef ROUNDHELL_SYSTEMS_FRAME_COUNTER_HPP
#define ROUNDHELL_SYSTEMS_FRAME_COUNTER_HPP

#include <cstdint>

#include <SDL3/SDL_stdinc.h>

#include "clock.hpp"

namespace rh::S {

class FrameCounter
{
	// Clock measuring time for which app is running (cannot be restarted)
	Clock _app_clock;

	// Clock measuring time for which engine is running (will be restarted in `reset()` call)
	Clock _engine_clock;

	// Last frame time clock
	Clock _frame_clock;

	// Total number of frames.
	Uint64 _frame_count = 0;

	Uint64 _last_frame_time = 0;

public:

	FrameCounter() noexcept = default;

	~FrameCounter() = default;

	auto reset() noexcept -> void;

	auto frame_done() noexcept -> void;

	auto total_time() const noexcept -> Uint64;

	auto engine_time() const noexcept -> Uint64;

	auto last_frame_time() const noexcept -> Uint64;

	auto frame_count() const noexcept -> Uint64;

	auto average_frame_rate() const noexcept -> float;

	auto average_frame_time() const noexcept -> float; // in ms
};

} // namespace rh::S

#endif // ROUNDHELL_SYSTEMS_FRAME_COUNTER_HPP

