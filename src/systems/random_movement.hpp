#ifndef ROUNDHELL_SYSTEMS_RANDOM_MOVEMENT_HPP
#define ROUNDHELL_SYSTEMS_RANDOM_MOVEMENT_HPP

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

namespace rh::S {

class RandomMovement
{
	SDL_Rect _area; // Area of movement - eg. `{0, 0, window_size_x, window_size_y}`.

	// We will change movement each `_amax` milliseconds.
	Uint64 _accu = 0;
	Uint64 _amax = 2500;

public:
	RandomMovement() = delete;
	RandomMovement(SDL_Rect area) noexcept;
	RandomMovement(int x, int y, int w, int h) noexcept;

	RandomMovement(const RandomMovement&) = default;
	RandomMovement(RandomMovement&&) = default;
	auto operator=(const RandomMovement&) -> RandomMovement& = default;
	auto operator=(RandomMovement&&) -> RandomMovement& = default;

	~RandomMovement() = default;

	auto area() const noexcept -> SDL_Rect;
	auto area(SDL_Rect area) noexcept -> void;
	auto area(int x, int y, int w, int h) noexcept -> void;

	auto run(Uint64 dt, entt::registry& registry, entt::entity top) -> void;
};

} // namespace rh::S

#endif // ROUNDHELL_SYSTEMS_RANDOM_MOVEMENT_HPP

