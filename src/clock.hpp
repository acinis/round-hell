#ifndef ROUNDHELL_CLOCK_HPP
#define ROUNDHELL_CLOCK_HPP

/**
 * @file src/clock.hpp
 * @brief Simple time measuring.
 */

#include <SDL3/SDL_stdinc.h>

namespace rh {

/**
 * @brief Simple time measuring.
 */
class Clock final
{
	Uint64 _start; //!< Clock start time, in milliseconds.

public:

	/**
	 * @brief Create clock - it will count time since creation.
	 */
	Clock() noexcept;

	/**
	 * @brief Default destructor.
	 */
	~Clock() = default;

	/**
	 * @brief Elapsed time since this `Clock` creation or last call to `restart()`.
	 *
	 * @return Elapsed time (in milliseconds).
	 */
	[[nodiscard]] auto elapsed() const noexcept -> Uint64;

	/**
	 * @brief Restart clock so it will measure elapsed time since now.
	 *
	 * @return Elapsed time (in milliseconds).
	 */
	auto restart() noexcept -> Uint64;
};

} // namespace rh

#endif // ROUNDHELL_CLOCK_HPP

