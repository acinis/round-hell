#include "any_component.hpp"

namespace rh {

auto AnyComponent::emplace_into(entt::registry& registry, entt::entity entity) const noexcept -> void
{
	_emplacer(registry, entity, _component);
}

} // namespace rh

