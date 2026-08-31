#include "components/movement.hpp"

namespace rh::C {

Movement::Movement(float speed) noexcept
:
	Movement({0.0f, 0.0f, 0.0f, 1.0f}, speed)
{
	_done = true;
}

Movement::Movement(glm::vec4 destination, float speed) noexcept
:
	_destination{destination},
	_speed{speed},
	_done{false}
{
}

Movement::Movement(float destination_x, float destination_y, float speed) noexcept
:
	Movement({destination_x, destination_y, 0.0f, 1.0f}, speed)
{
}

Movement::Movement(float destination_x, float destination_y, float destination_z, float speed) noexcept
:
	Movement({destination_x, destination_y, destination_z, 1.0f}, speed)
{
}

auto Movement::destination() const noexcept -> glm::vec4
{
	return _destination;
}

auto Movement::destination(glm::vec4 value) noexcept -> void
{
	_destination = value;
}

auto Movement::speed() const noexcept -> float
{
	return _speed;
}

auto Movement::speed(float value) noexcept -> void
{
	_speed = value;
}

auto Movement::done() const noexcept -> bool
{
	return _done;
}

auto Movement::done(bool value) noexcept -> void
{
	_done = value;
}

} // namespace rh::C

