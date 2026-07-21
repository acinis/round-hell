#ifndef ROUNDHELL_LOADERS_SUBTEXTURE_LOADER_HPP
#define ROUNDHELL_LOADERS_SUBTEXTURE_LOADER_HPP

/**
 * @file src/loaders/subtexture_loader.hpp
 * @brief Loaders for Subtexture resource.
 */

#include <memory>
#include <optional>

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include <entt/resource/resource.hpp>

#include "errors.hpp"
#include "resource_loader_for.hpp"
#include "subtexture.hpp"

namespace rh {

/**
 * @brief Loader for `rh::Subtexture`.
 */
struct SubtextureLoader
{
	using result_type = std::shared_ptr<Subtexture>;

	/**
	 * @brief
	 *
	 * @param error Reference to optional `rh::Error` instance for error reporting.
	 * @param
	 * @return `rh::Subtexture*` (or nullptr on failure) as `std::shared_ptr`.
	 */

	auto operator()(std::optional<Error>& error, entt::resource<SDL_Texture> texture, SDL_FRect rect) const noexcept -> result_type;

	auto operator()(std::optional<Error>& error, entt::resource<SDL_Texture> texture, SDL_Rect rect) const noexcept -> result_type;

	auto operator()(std::optional<Error>& error, entt::resource<SDL_Texture> texture) const noexcept -> result_type;
};

template<>
struct ResourceLoaderFor<Subtexture>
{
	using Type = SubtextureLoader;
};

} // namespace rh

#endif // ROUNDHELL_LOADERS_SUBTEXTURE_LOADER_HPP

