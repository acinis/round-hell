#include "entity_builder.hpp"

#include <entt/core/hashed_string.hpp>
using namespace entt::literals;

#include "components/relation.hpp"

namespace rh {

EntityBuilder::EntityBuilder(entt::registry& registry)
:
	_registry{registry}
{
	_entity = _registry.create();
}

auto EntityBuilder::emplace(const AnyComponent& any_component) noexcept -> void
{
	any_component.emplace_into(_registry, _entity);
}

auto EntityBuilder::get_entity() const -> entt::entity
{
	return _entity;
}

auto make_entity(entt::registry& registry) -> EntityBuilder
{
	return EntityBuilder{registry};
}

auto make_entity(entt::registry& registry, entt::entity parent) -> EntityBuilder
{
	auto eb = make_entity(registry);

	ensure_relation(eb._registry, eb._entity);
	ensure_relation(eb._registry, parent);

	C::Relation::make_relation(eb._registry, parent, eb._entity);

	return eb;
}

} // namespace rh

