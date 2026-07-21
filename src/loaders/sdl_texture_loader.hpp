#ifndef ROUNDHELL_LOADERS_SDL_TEXTURE_LOADER_HPP
#define ROUNDHELL_LOADERS_SDL_TEXTURE_LOADER_HPP

/**
 * @file src/loaders/texture_loader.hpp
 * @brief Loaders for SDL_Texture resource.
 */

#include <memory>
#include <optional>
#include <string>
using namespace std::string_literals;

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include <entt/core/hashed_string.hpp>
using namespace entt::literals;

#include "errors.hpp"
#include "resource_loader_for.hpp"

namespace rh {

/**
 * @brief Loader for SDL_Texture.
 */
struct SdlTextureLoader
{
	using result_type = std::shared_ptr<SDL_Texture>;

	/**
	 * @brief Load texture from image file.
	 *
	 * @param error Reference to optional `rh::Error` instance for error reporting.
	 * @param renderer SDL's renderer (the rendering context).
	 * @param path Image file path (relative to program's working directory - typically execulable
	 *        file).
	 * @return SDL_Texture* (or nullptr on failure) as `std::shared_ptr` (with appropriate deleter).
	 */
	auto operator()(std::optional<Error>& error, SDL_Renderer *renderer, const std::string& path) const noexcept -> result_type;

	/**
	 * @brief Create fullscreen texture with given color.
	 *
	 * Fulscreen size is get from display on which is placed window associated with given renderer.
	 * Renderer asociated with said window is same as renderer used as rendering context for texture
	 * being created.
	 *
	 * @param error Reference to optional `rh::Error` instance for error reporting.
	 * @param renderer SDL's renderer (the rendering context). It must have associated a window.
	 * @param color Color of new texture.
	 * @return SDL_Texture* (or nullptr on failure) as `std::shared_ptr` (with appropriate deleter).
	 */
	auto operator()(std::optional<Error>& error, SDL_Renderer *renderer, SDL_Color color) const noexcept -> result_type;

	/**
	 * @brief Create fullscreen texture with given color.
	 *
	 * Fulscreen size is get from display on which is placed given window (and renderer asociated
	 * with that window - if any - can be different from `renderer` passed as argument here).
	 *
	 * @param error Reference to optional `rh::Error` instance for error reporting.
	 * @param renderer SDL's renderer (the rendering context).
	 * @param window Size of display where that window belong will be used as texture size.
	 * @param color Color of new texture.
	 * @return SDL_Texture* (or nullptr on failure) as `std::shared_ptr` (with appropriate deleter).
	 */
	auto operator()(std::optional<Error>& error, SDL_Renderer *renderer, SDL_Window *window, SDL_Color color) const noexcept -> result_type;

	/**
	 * @brief Create fullscreen texture with given color.
	 *
	 * Fulscreen size is get from given display.
	 *
	 * You can use eg. `SDL_GetDisplayForWindow()` to obtain `display_id`.
	 * See also other overloads of `operator()` in `SdlTextureLoader`.
	 *
	 * @param error Reference to optional `rh::Error` instance for error reporting.
	 * @param renderer SDL's renderer (the rendering context).
	 * @param display_id ID of the display that will be queried for size. This will be used as new
	 *        texture size.
	 * @param color Color of new texture.
	 * @return SDL_Texture* (or nullptr on failure) as `std::shared_ptr` (with appropriate deleter).
	 */
	auto operator()(std::optional<Error>& error, SDL_Renderer *renderer, SDL_DisplayID display_id, SDL_Color color) const noexcept -> result_type;

	/**
	 * @brief Create texture with given size and color.
	 *
	 * @param error Reference to optional `rh::Error` instance for error reporting.
	 * @param renderer SDL's renderer (the rendering context).
	 * @param format Pixel format of new texture.
	 * @param w Width of new texture.
	 * @param h Height of new texture.
	 * @param color Color of new texture.
	 * @return SDL_Texture* (or nullptr on failure) as `std::shared_ptr` (with appropriate deleter).
	 */
	auto operator()(std::optional<Error>& error, SDL_Renderer *renderer, SDL_PixelFormat format, int w, int h, SDL_Color color) const noexcept -> result_type;
};

template<>
struct ResourceLoaderFor<SDL_Texture>
{
	using Type = SdlTextureLoader;
};

} // namespace rh

#endif // ROUNDHELL_LOADERS_SDL_TEXTURE_LOADER_HPP

