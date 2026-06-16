#include "systems/frame_counter.hpp"

namespace rh::S {

auto FrameCounter::reset() noexcept -> void
{
	// _app_clock is not restarted on purpose
	_engine_clock.restart();
	_frame_clock.restart();
	_frame_count = 0;
	_last_frame_time = 0;
}

auto FrameCounter::frame_done() noexcept -> void
{
	_last_frame_time = _frame_clock.restart();
	_frame_count += 1;
}

auto FrameCounter::total_time() const noexcept -> Uint64
{
	return _app_clock.elapsed();
}

auto FrameCounter::engine_time() const noexcept -> Uint64
{
	return _engine_clock.elapsed();
}

auto FrameCounter::last_frame_time() const noexcept -> Uint64
{
	return _last_frame_time;
}

auto FrameCounter::frame_count() const noexcept -> Uint64
{
	return _frame_count;
}

auto FrameCounter::average_frame_rate() const noexcept -> float
{
	return frame_count() / (engine_time() / 1000.0f);
}

auto FrameCounter::average_frame_time() const noexcept -> float // in ms
{
	return static_cast<float>(engine_time()) / static_cast<float>(frame_count());
}

} // namespace rh::S

