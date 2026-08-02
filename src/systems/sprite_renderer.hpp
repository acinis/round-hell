#ifndef ROUNDHELL_SYSTEMS_SPRITE_RENDERER_HPP
#define ROUNDHELL_SYSTEMS_SPRITE_RENDERER_HPP

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

namespace rh::S {

class SpriteRenderer
{
public:
	auto run(Uint64 dt, SDL_Renderer* sdl_renderer, entt::registry& registry, entt::entity top) -> void;
};

} // namespace rh::S

#endif // ROUNDHELL_SYSTEMS_SPRITE_RENDERER_HPP

