#include "systems/world_transform_updater.hpp"

#include "components/transform.hpp"
#include "components/relation.hpp"
#include "utils.hpp"
#include "utils/entt.hpp"
#include "utils/traverse.hpp"

namespace rh::S {

auto WorldTransformUpdater::run(entt::registry& registry, entt::entity top) -> void
{
	pre_order_traverse(
		registry,
		top,
		[](entt::registry& registry_, entt::entity entity)
		{
			if (! registry_.all_of<C::WorldTransform>(entity)) {
				return;
			}

			auto& c_world_transform = registry_.get<C::WorldTransform>(entity);

			// By default use identity transform if there is no parent
			auto default_c_world_transform = C::WorldTransform{glm::mat4{1.0f}};
			const auto& parent_c_world_transform = get_from_parent<C::WorldTransform>(registry_, entity, default_c_world_transform);

			auto default_c_transform = C::LocalTransform{glm::mat4{1.0f}};
			const auto& c_transform = default_if_nullptr(registry_.try_get<C::LocalTransform>(entity), default_c_transform);

			// Global Transform = Local Transform * Parent Global Transform
			c_world_transform.matrix(c_transform.matrix() * parent_c_world_transform.matrix());
		}
	);
}

} // namespace rh::S

