#include "clock.hpp"

#include <SDL3/SDL_timer.h>

namespace rh {

Clock::Clock() noexcept
:
	_start {SDL_GetTicksNS()}
{
}

auto Clock::elapsed() const noexcept -> Uint64
{
	auto now = SDL_GetTicksNS();
	auto delta = now - _start;
	return delta;
}

auto Clock::restart() noexcept -> Uint64
{
	auto delta = elapsed();
	_start = SDL_GetTicksNS();
	return delta;
}

}; // namespace rh

