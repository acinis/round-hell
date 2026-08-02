#ifndef ROUNDHELL_ENTITY_BUILDER_HPP
#define ROUNDHELL_ENTITY_BUILDER_HPP

#include <concepts>

#include <entt/core/type_traits.hpp>
#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "any_component.hpp"

namespace rh {

class EntityBuilder final
{
	friend auto make_entity(entt::registry&) -> EntityBuilder;
	friend auto make_entity(entt::registry&, entt::entity) -> EntityBuilder;

	entt::registry& _registry;
	entt::entity _entity;

	EntityBuilder(entt::registry& registry);

public:

	// Normally we are building brand-new entity so most of these methods are not needed, but just
	// for sake of other use-cases we are adding them.

	template<class Component, class... Args>
	auto emplace(Args&&... args) -> EntityBuilder&;

	template<class Component, class... Args>
	auto emplace_or_replace(Args&&... args) -> EntityBuilder&;

	template<class Component, class... Args>
	auto replace(Args&&... args) -> EntityBuilder&;

	template<class Component, std::invocable... Invocables>
	auto patch(Invocables&&... invocables) -> EntityBuilder&;

	template<class Component>
	auto erase() -> EntityBuilder&;

	template<class Component>
	auto remove() -> EntityBuilder&;

	template<entt::id_type Tag>
	auto emplace_tag() -> EntityBuilder&;

	template<entt::id_type Tag>
	auto emplace_or_replace_tag() -> EntityBuilder&;

	template<entt::id_type Tag>
	auto replace_tag() -> EntityBuilder&;

	// No need for `patch_tag`, replace will suffice in all cases.

	template<entt::id_type Tag>
	auto erase_tag() -> EntityBuilder&;

	template<entt::id_type Tag>
	auto remove_tag() -> EntityBuilder&;

	// TODO There is only `emplace()` now, cos `AnyComponent` supports only that operation.
	auto emplace(const AnyComponent& any_component) noexcept -> void;

	auto get_entity() const -> entt::entity;
};

auto make_entity(entt::registry& registry) -> EntityBuilder;
auto make_entity(entt::registry& registry, entt::entity parent) -> EntityBuilder;

} // namespace rh

#include "entity_builder.ipp"

#endif // ROUNDHELL_ENTITY_BUILDER_HPP

