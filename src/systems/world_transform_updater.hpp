#ifndef ROUNDHELL_SYSTEMS_WORLD_TRANSFORM_UPDATER_HPP
#define ROUNDHELL_SYSTEMS_WORLD_TRANSFORM_UPDATER_HPP

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

namespace rh::S {

class WorldTransformUpdater
{
public:
	auto run(entt::registry& registry, entt::entity top) -> void;
};

} // namespace rh::S

#endif // ROUNDHELL_SYSTEMS_WORLD_TRANSFORM_UPDATER_HPP

