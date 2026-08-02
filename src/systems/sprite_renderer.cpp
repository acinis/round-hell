#include "systems/sprite_renderer.hpp"

#include <SDL3/SDL_render.h>

#include "utils.hpp"

#include "components/sprite.hpp"
#include "components/transform.hpp"

namespace rh::S {

auto SpriteRenderer::run(Uint64 dt, SDL_Renderer* sdl_renderer, entt::registry& registry, entt::entity top) -> void
{
	RH_UNUSED(dt);
	RH_UNUSED(top);

	auto view = registry.view<C::Sprite, C::WorldTransform>();

	for (auto &&[entity, c_sprite, c_world_transform] : view.each()) {

		c_sprite.apply_all();

		auto src_rect = to_frect(c_sprite.rect());

		auto dst_pos = transform_point(c_world_transform.matrix(), 0.0f, 0.0f);

		auto dst_rect = SDL_FRect{
			dst_pos.x,
			dst_pos.y,
			static_cast<float>(c_sprite.rect().w),
			static_cast<float>(c_sprite.rect().h)
		};

		SDL_RenderTexture(sdl_renderer, c_sprite.subtexture().raw(), &src_rect, &dst_rect);
	}
}

} // namespace rh::S

