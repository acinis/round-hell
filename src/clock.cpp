#include "clock.hpp"

#include <SDL3/SDL_timer.h>

namespace rh {

Clock::Clock() noexcept
:
	_start {SDL_GetPerformanceCounter()}
{
}

auto Clock::elapsed() const noexcept -> Uint64
{
	auto now = SDL_GetPerformanceCounter();
	auto freq = SDL_GetPerformanceFrequency();

	auto delta = ((now - _start) * 1000) / freq;

	return delta;
}

auto Clock::restart() noexcept -> Uint64
{
	auto delta = elapsed();

	_start = SDL_GetPerformanceCounter();

	return delta;
}

}; // namespace rh

