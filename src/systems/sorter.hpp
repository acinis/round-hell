#ifndef ROUNDHELL_SYSTEMS_SORTER_HPP
#define ROUNDHELL_SYSTEMS_SORTER_HPP

#include <entt/entity/registry.hpp>

namespace rh::S {

// Example usage:
// rh::S::Sorter sorter;
// sorter.sort<rh::C::Sprite>(registry);

class Sorter
{
public:
	// Sorts entities that have given `ComponentType` by its `C::Order` (or `C::Order::DEFAULT` if entity have no `C::Order`).
	template<class ComponentType>
	auto run(entt::registry& registry) -> void;
};

} // namespace rh::S

#include "systems/sorter.ipp"

#endif // ROUNDHELL_SYSTEMS_SORTER_HPP

