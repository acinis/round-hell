#ifndef ROUNDHELL_COMPONENTS_MOVEMENT_HPP
#define ROUNDHELL_COMPONENTS_MOVEMENT_HPP

#include <glm/vec4.hpp>

namespace rh::C {

class Movement
{
	glm::vec4 _destination;
	float _speed; // in px/s

	bool _done;

public:
	Movement(float speed = 0.0f) noexcept; // This will make `_done == true`.
	Movement(glm::vec4 destination, float speed) noexcept;
	Movement(float destination_x, float destination_y, float speed) noexcept;
	Movement(float destination_x, float destination_y, float destination_z, float speed) noexcept;

	Movement(const Movement&) noexcept = default;
	Movement(Movement&&) noexcept = default;
	auto operator=(const Movement&) noexcept -> Movement& = default;
	auto operator=(Movement&&) noexcept -> Movement& = default;

	auto destination() const noexcept -> glm::vec4;
	auto destination(glm::vec4 value) noexcept -> void;

	auto speed() const noexcept -> float;
	auto speed(float value) noexcept -> void;

	[[nodiscard]] auto done() const noexcept -> bool;
	auto done(bool value) noexcept -> void;
};

} // namespace rh::C

#endif // ROUNDHELL_COMPONENTS_MOVEMENT_HPP

