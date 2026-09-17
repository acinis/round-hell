#ifndef ROUNDHELL_SYSTEMS_ANIMATION_HPP
#define ROUNDHELL_SYSTEMS_ANIMATION_HPP

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

namespace rh::S {

class Animation
{
public:
	auto run(Uint64 dt, entt::registry& registry, entt::entity top) -> void;
};

} // namespace rh::S

#endif // ROUNDHELL_SYSTEMS_ANIMATION_HPP

