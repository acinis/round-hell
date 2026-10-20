#include "systems/random_movement.hpp"

#include <glm/glm.hpp>

#include "utils.hpp"

#include "components/movement.hpp"

namespace rh::S {

RandomMovement::RandomMovement(SDL_Rect area) noexcept
:
	_area{area}
{
}

RandomMovement::RandomMovement(int x, int y, int w, int h) noexcept
:
	RandomMovement(SDL_Rect{x, y, w, h})
{
}



RandomMovement::RandomMovement(SDL_Rect area, Uint64 interval) noexcept
:
	_area{area},
	_interval{interval}
{
}

RandomMovement::RandomMovement(int x, int y, int w, int h, Uint64 interval) noexcept
:
	RandomMovement(SDL_Rect{x, y, w, h}, interval)
{
}

auto RandomMovement::area() const noexcept -> SDL_Rect
{
	return _area;
}

auto RandomMovement::area(SDL_Rect area) noexcept -> void
{
	_area = area;
}

auto RandomMovement::area(int x, int y, int w, int h) noexcept -> void
{
	_area = {x, y, w, h};
}

auto RandomMovement::interval() const noexcept -> Uint64
{
	return _interval;
}

auto RandomMovement::interval(Uint64 interval) noexcept -> void
{
	_interval = interval;
}

auto RandomMovement::run(Uint64 dt, entt::registry& registry, entt::entity top) -> void
{
	RH_UNUSED(top);

	_accumulator += dt;
	if (_accumulator >= _interval) {
		_accumulator = 0;
	}
	if (_accumulator != dt) {
		return;
	}

	auto view = registry.view<C::Movement>();

	for (auto &&[entity, c_movement] : view.each()) {

		if (! c_movement.done()) {
			continue;
		}

		// TODO Temporary change: Make entities more aligned inside window.
		//auto x = rand<int>(_area.x, _area.x + _area.w - 1);
		//auto y = rand<int>(_area.y, _area.y + _area.h - 1);
		auto x = rand<int>(_area.x - 60, _area.x + _area.w - 1 - 105);
		auto y = rand<int>(_area.y - 86, _area.y + _area.h - 1 - 143);

		auto v = glm::vec4{x, y, 0, 1};
		c_movement.destination(v);

		c_movement.done(false);

	}
}

} // namespace rh::S

