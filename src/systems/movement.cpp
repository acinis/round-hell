#include "systems/movement.hpp"

#include <algorithm>
#include <cmath>

#include <glm/glm.hpp>

#include "utils.hpp"

#include "components/movement.hpp"
#include "components/transform.hpp"

namespace rh::S {

auto Movement::run(Uint64 dt, entt::registry& registry, entt::entity top) -> void
{
	RH_UNUSED(top);

	auto view = registry.view<C::Movement, C::WorldTransform, C::LocalTransform>();

	for (auto &&[entity, c_movement, c_world_transform, c_local_transform] : view.each()) {

		if (c_movement.done()) {
			continue;
		}

		// World position, ie. world vector.
		auto world_position = transform_point(c_world_transform.matrix());

		auto distance = glm::distance(world_position, c_movement.destination());

		// Time needed for whole distance (in miliseconds, converted to Uint64).
		auto time_needed = static_cast<decltype(dt)>(std::nearbyint(distance / c_movement.speed() * 1000.f));

		// Time for current frame - use `dt` unless remaining time for completing distance is smaller.
		auto time = std::min(dt, time_needed);

		// Compute how much we must move forward.
		auto to_move = c_movement.speed() * (time / 1000.0f); // Divide by 1000 to change units beetwen [s] and [ms].

		// Get vector that is pointing from entity to its destination, ie. destination_vector - entity_vector.
		auto v = c_movement.destination() - world_position;

		// Normalize it - so it will has length equal 1.
		auto n = glm::normalize(v);

		// Set length to amount of distance we must move.
		auto m = n * to_move;

		// Perform move.
		// TODO This is ugly, but it works. `mat4 += vec4` is ok, but `mat4 + vec4` gives error about not supported types for `operator+()`.
		c_local_transform.matrix(c_local_transform.matrix() += m);

		if (time_needed <= dt) {
			// This was last step - we are at destination now.
			c_movement.done(true);
		}
	}
}

} // namespace rh::S

