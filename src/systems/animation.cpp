#include "systems/animation.hpp"

#include "utils.hpp"

#include "components/animation.hpp"
#include "components/sprite.hpp"

namespace rh::S {

auto Animation::run(Uint64 dt, entt::registry& registry, entt::entity top) -> void
{
	RH_UNUSED(top);

	auto view = registry.view<C::Animation, C::Sprite>();

	for (auto &&[entity, c_animation, c_sprite] : view.each()) {
		c_animation.animate(c_sprite, dt);
	}
}

} // namespace rh::S

