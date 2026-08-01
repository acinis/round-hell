#ifndef ROUNDHELL_COMPONENTS_TRANSFORM_HPP
#define ROUNDHELL_COMPONENTS_TRANSFORM_HPP

#include <glm/glm.hpp>

namespace rh::C::internal {

class Transform
{
	glm::mat4 _matrix;

public:
	// TODO Constructor that forwards to `glm::mat4` constructor?
	Transform() noexcept = default;
	Transform(const glm::mat4& value) noexcept;
	Transform(glm::mat4&& value) noexcept;

	Transform(const Transform&) noexcept = default;
	Transform(Transform&&) noexcept = default;
	auto operator=(const Transform&) noexcept -> Transform& = default;
	auto operator=(Transform&&) noexcept -> Transform& = default;

	~Transform() = default;

	auto matrix() const noexcept -> glm::mat4;
	auto matrix(const glm::mat4& value) noexcept -> void;
	auto matrix(glm::mat4&& value) noexcept -> void;
};

} // namespace rh::C::internal

namespace rh::C {

struct LocalTransform : public internal::Transform {};

struct WorldTransform : public internal::Transform {};

} // namespace rh::C

#endif // ROUNDHELL_COMPONENTS_TRANSFORM_HPP

