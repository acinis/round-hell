#ifndef ROUNDHELL_LOADERS_ANIMATION_DATA_LOADER_HPP
#define ROUNDHELL_LOADERS_ANIMATION_DATA_LOADER_HPP

/**
 * @file src/loaders/animation_data_loader.hpp
 * @brief Loaders for animation data needed in `C::Animation`.
 */

#include <memory>
#include <optional>
#include <tuple>

#include <SDL3/SDL_stdinc.h>

#include "errors.hpp"
#include "resource_loader_for.hpp"

namespace rh {

/**
 * @brief Simple tuple that holds data needed for creating `C::Animation`.
 */
using AnimationData = std::tuple<Uint16, Uint64, bool, bool>;

/**
 * @brief Loader for animation data.
 */
struct AnimationDataLoader
{
	using result_type = std::shared_ptr<AnimationData>;

	/**
	 * @brief
	 *
	 * @param error Reference to optional `rh::Error` instance for error reporting.
	 * @param data
	 * @return `rh::AnimationData*` (or nullptr on failure) as `std::shared_ptr`.
	 */
	auto operator()(std::optional<Error>& error, const AnimationData& data) const noexcept -> result_type;
};

template<>
struct ResourceLoaderFor<AnimationData>
{
	using Type = AnimationDataLoader;
};

} // namespace rh

#endif // ROUNDHELL_LOADERS_ANIMATION_DATA_LOADER_HPP

