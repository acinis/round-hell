#ifndef ROUNDHELL_COMPONENTS_RELATION_HPP
#define ROUNDHELL_COMPONENTS_RELATION_HPP

#include <cstddef>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

namespace rh {

// Create empty C::Relation if entity do not have one already
void ensure_relation(entt::registry& registry, entt::entity entity);

} // namespace rh

namespace rh::C {

class Relation
{
	entt::entity _parent;
	entt::entity _prev; // prev sibling
	entt::entity _next; // next sibling
	entt::entity _first; // first child
	std::size_t _children; // number of children

public:
	Relation();
	~Relation() = default;

	auto parent() const -> entt::entity;

	auto prev() const -> entt::entity;
	auto next() const -> entt::entity;

	auto first() const -> entt::entity;
	auto children() const -> std::size_t; // TODO Misleading name.

	auto has_parent() const -> bool;
	auto has_siblings() const -> bool;
	auto has_children() const -> bool;

	// Helpers:

	static auto make_relation(
		entt::registry& registry,
		entt::entity parent,
		C::Relation& c_parent,
		entt::entity child,
		C::Relation& c_child
	) -> void;

	static auto make_relation(
		entt::registry& registry,
		entt::entity parent,
		C::Relation& c_parent,
		entt::entity child
	) -> void;

	static auto make_relation(
		entt::registry& registry,
		entt::entity parent,
		entt::entity child,
		C::Relation& c_child
	) -> void;

	static auto make_relation(
		entt::registry& registry,
		entt::entity parent,
		entt::entity child
	) -> void;
};

} // namespace rh::C

#endif // ROUNDHELL_COMPONENTS_RELATION_HPP

