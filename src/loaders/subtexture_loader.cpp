#include "loaders/subtexture_loader.hpp"

#include "utils.hpp"

namespace rh {

auto SubtextureLoader::operator()(std::optional<Error>& error, entt::resource<SDL_Texture> texture, SDL_FRect rect) const noexcept -> result_type
{
	RH_UNUSED(error);

	return std::make_shared<Subtexture>(texture.handle().get(), rect);
}

auto SubtextureLoader::operator()(std::optional<Error>& error, entt::resource<SDL_Texture> texture, SDL_Rect rect) const noexcept -> result_type
{
	return operator()(error, texture, to_frect(rect));
}

auto SubtextureLoader::operator()(std::optional<Error>& error, entt::resource<SDL_Texture> texture) const noexcept -> result_type
{
	RH_UNUSED(error);

	return std::make_shared<Subtexture>(texture.handle().get());
}

} // namespace rh

