#include "utils/entt.hpp"

namespace rh {

auto create_entity_if_null(entt::registry& registry, entt::entity entity) -> entt::entity
{
	if (entt::null == entity) {
		entity = registry.create();
	}

	return entity;
}

} // namespace rh

