#include "components/relation.hpp"

#include <memory>

namespace rh {

auto ensure_relation(entt::registry& registry, entt::entity entity) -> void
{
	if (nullptr == registry.try_get<C::Relation>(entity)) {
		registry.emplace<C::Relation>(entity);
	}
}

} // namespace rh

namespace rh::C {

Relation::Relation()
:
	_parent{entt::null},
	_prev{entt::null},
	_next{entt::null},
	_first{entt::null},
	_children{0}
{
}

auto Relation::parent() const -> entt::entity
{
	return _parent;
}

auto Relation::prev() const -> entt::entity
{
	return _prev;
}

auto Relation::next() const -> entt::entity
{
	return _next;
}

auto Relation::first() const -> entt::entity
{
	return _first;
}

auto Relation::children() const -> std::size_t
{
	return _children;
}

auto Relation::has_parent() const -> bool
{
	return entt::null != parent();
}

auto Relation::has_siblings() const -> bool
{
	if (entt::null == prev() && entt::null == next()) {
		return false;
	}

	return true;
}

auto Relation::has_children() const -> bool
{
	return children() != 0;
}

auto Relation::make_relation(
	entt::registry& registry,
	entt::entity parent,
	C::Relation& c_parent,
	entt::entity child,
	C::Relation& c_child
) -> void
{
	auto old_children = c_parent._children;

	// Cases:
	// (1) - adding first child, old_children == 0
	// (2) - adding second child, old_children == 1
	// (3) - adding third/nth child, old_children > 1

	// (1, 2, 3)
	c_parent._children += 1;
	c_child._parent = parent;

	if (old_children == 0) { // (1)
		c_parent._first = child;
	}
	else { // (2, 3)
		entt::entity first = c_parent._first;
		C::Relation& c_first = registry.get<C::Relation>(first);
		entt::entity last = c_first._prev; // last == first in case (2)

		c_child._next = first;
		c_child._prev = last;
		c_first._prev = child;

		if (old_children == 1) { // (2)
			c_first._next = child;
		}
		else { // (3)
			auto& c_last = registry.get<C::Relation>(last);
			c_last._next = child;
		}
	}
}

auto Relation::make_relation(
	entt::registry& registry,
	entt::entity parent,
	C::Relation& c_parent,
	entt::entity child
) -> void
{
	ensure_relation(registry, child);
	auto& c_child = registry.get<C::Relation>(child);
	return make_relation(registry, parent, c_parent, child, c_child);
}

auto Relation::make_relation(
	entt::registry& registry,
	entt::entity parent,
	entt::entity child,
	C::Relation& c_child
) -> void
{
	ensure_relation(registry, parent);
	auto& c_parent = registry.get<C::Relation>(parent);
	return make_relation(registry, parent, c_parent, child, c_child);
}

auto Relation::make_relation(
	entt::registry& registry,
	entt::entity parent,
	entt::entity child
) -> void
{
	ensure_relation(registry, parent);
	ensure_relation(registry, child);
	auto& c_parent = registry.get<C::Relation>(parent);
	auto& c_child = registry.get<C::Relation>(child);
	return make_relation(registry, parent, c_parent, child, c_child);
}

} // namespace rh::C

