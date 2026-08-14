#ifndef ROUNDHELL_SYSTEMS_FPS_LIMITER_HPP
#define ROUNDHELL_SYSTEMS_FPS_LIMITER_HPP

#include <cstddef>

#include <SDL3/SDL_stdinc.h>

namespace rh::S {

class FpsLimiter
{
	// zero means no limit
	std::size_t _fps_limit;

public:

	FpsLimiter(std::size_t fps_limit = 0) noexcept;

	auto limit(std::size_t value) noexcept -> void;
	auto limit() const noexcept -> std::size_t;

	// Wait (if needed) until frame duration will match given FPS limit.
	// `elapsed` - time elapsed since beginning of current frame.
	// Return delayed time in [ms] or zero if no delay was performed.
	auto run(Uint64 elapsed) const noexcept -> Uint64;
};

} // namespace rh::S

#endif // ROUNDHELL_SYSTEMS_FPS_LIMITER_HPP

