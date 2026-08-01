#include "components/transform.hpp"

#include <utility>

namespace rh::C::internal {

Transform::Transform(const glm::mat4& value) noexcept
:
	_matrix{value}
{
}

Transform::Transform(glm::mat4&& value) noexcept
:
	_matrix{std::move(value)}
{
}

auto Transform::matrix() const noexcept -> glm::mat4
{
	return _matrix;
}

auto Transform::matrix(const glm::mat4& value) noexcept -> void
{
	_matrix = value;
}

auto Transform::matrix(glm::mat4&& value) noexcept -> void
{
	_matrix = std::move(value);
}

} // namespace rh::C::internal

