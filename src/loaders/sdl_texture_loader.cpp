#include "loaders/sdl_texture_loader.hpp"

#include <cassert>

#include <SDL3_image/SDL_image.h>

namespace rh {

auto SdlTextureLoader::operator()(std::optional<Error>& error, SDL_Renderer *renderer, const std::string& path) const noexcept -> result_type
{
	SDL_Texture* texture = nullptr;

	SDL_Surface* surface = IMG_Load(path.c_str());
	if (! surface) {
		error = make_sdl_error();
		return nullptr;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (! texture) {
		error = make_sdl_error();
		return nullptr;
	}

	SDL_DestroySurface(surface);

	assert((texture) && "INTERNAL: `nullptr` texture return in `SdlTextureLoader`.");
	return std::shared_ptr<SDL_Texture>(texture, &SDL_DestroyTexture);
}

auto SdlTextureLoader::operator()(std::optional<Error>& error, SDL_Renderer *renderer, SDL_Color color) const noexcept -> result_type
{
	SDL_Window* window = SDL_GetRenderWindow(renderer);
	if (! window) {
		error = make_sdl_error();
		return nullptr;
	}

	return operator()(error, renderer, window, color);
}

auto SdlTextureLoader::operator()(std::optional<Error>& error, SDL_Renderer *renderer, SDL_Window *window, SDL_Color color) const noexcept -> result_type
{
	SDL_DisplayID display_id = SDL_GetDisplayForWindow(window);
	if (! display_id) {
		error = make_sdl_error();
		return nullptr;
	}

	return operator()(error, renderer, display_id, color);
}

auto SdlTextureLoader::operator()(std::optional<Error>& error, SDL_Renderer *renderer, SDL_DisplayID display_id, SDL_Color color) const noexcept -> result_type
{
	const SDL_DisplayMode* display_mode = SDL_GetCurrentDisplayMode(display_id);
	if (! display_mode) {
		error = make_sdl_error();
		return nullptr;
	}

	return operator()(error, renderer, display_mode->format, display_mode->w, display_mode->h, color);
}

auto SdlTextureLoader::operator()(std::optional<Error>& error, SDL_Renderer *renderer, SDL_PixelFormat format, int w, int h, SDL_Color color) const noexcept -> result_type
{
	SDL_Texture* texture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, w, h);
	if (! texture) {
		error = make_sdl_error();
		return nullptr;
	}

	if (! SDL_SetRenderTarget(renderer, texture)) {
		error = make_sdl_error();
		return nullptr;
	}

	// TODO Storing and resetting old color is not needed?
	if (! SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a)) {
		error = make_sdl_error();
		return nullptr;
	}

	if (! SDL_RenderClear(renderer)) {
		error = make_sdl_error();
		return nullptr;
	}

	if (! SDL_SetRenderTarget(renderer, nullptr)) {
		error = make_sdl_error();
		return nullptr;
	}

	assert((texture) && "INTERNAL: `nullptr` texture return in `SdlTextureLoader`.");
	return std::shared_ptr<SDL_Texture>(texture, &SDL_DestroyTexture);
}

} // namespace rh

