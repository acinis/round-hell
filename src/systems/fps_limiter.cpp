#include "systems/fps_limiter.hpp"

#include <concepts>

#include <SDL3/SDL_timer.h>

#include "utils.hpp"

namespace rh::S {

FpsLimiter::FpsLimiter(std::size_t fps_limit) noexcept
:
	_fps_limit {fps_limit}
{
}

auto FpsLimiter::limit(std::size_t value) noexcept -> void
{
	_fps_limit = value;
}

auto FpsLimiter::limit() const noexcept -> std::size_t
{
	return _fps_limit;
}

auto FpsLimiter::run(Uint64 elapsed) const noexcept -> Uint64
{
	if (_fps_limit > 0) {
		Uint64 min_time_per_frame = from_seconds(1) / _fps_limit; // in [ns]
		Uint64 sleep_time = saturating_sub(min_time_per_frame, elapsed);
		if (sleep_time > 0) {
			SDL_DelayPrecise(sleep_time);
			return sleep_time;
		}
	}
	return 0;
}

} // namespace rh::S

