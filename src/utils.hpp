#ifndef ROUNDHELL_UTILS_HPP
#define ROUNDHELL_UTILS_HPP

#include <concepts>
#include <optional>
#include <source_location>
#include <string>
#include <string_view>
#include <vector>

#include <type_traits>

#include <SDL3/SDL_rect.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * @brief Silence compiler error about unused variable.
 *
 * @param x Unused variable.
 */
#define RH_UNUSED(x) (void)(x)

namespace rh {

/**
 * @brief Format SDL (and it's satellite extensions) version into string.
 *
 * Returned version string will be in format 'vX.Y.Z'. If linked version is provided and varies from
 * compiled one then format will be 'vX.Y.Z (vA.B.C)', the latter is linked version.
 *
 * @param compiled Version you compiled against (eg. from `SDL_VERSION` macro).
 * @param linked Version you linked with (eg. from `SDL_GetVersion()` function) (optional).
 * @return Formatted version string.
 */
[[nodiscard]] auto format_sdl_version(int compiled, std::optional<int> linked = {}) noexcept -> std::string;

// TODO Report error instead of returning malformed path (bare '?').
/**
 * @brief Remove project directory prefix from given path.
 * @param path Path.
 * @return Path relative to project directory, or "?" in case of error.
 */
[[nodiscard]] auto project_relative_path(const std::string_view path) -> std::string;

// Make `vector` of `string_view`s with command line arguments.
[[nodiscard]] auto make_args(int argc, char *argv[]) -> std::vector<std::string_view>;

/**
 * @brief Convert standard's source location to string.
 * @param location `std::source_location` instance to convert.
 * @return Source location formatted as string.
 */
[[nodiscard]] auto to_string(const std::source_location& location) -> std::string;

template<class T>
auto iround(T v) -> int;

/**
 * @brief Round floating point value to *unsigned* integral type.
 * @tparam R Return type (must be unsigned integral type).
 * @tparam T Rounded value type (must be floating point type).
 * @param T Value to be rounded.
 * @return Rounded value, zero if result will be negative.
 */
template<std::unsigned_integral R, std::floating_point T>
constexpr auto uround(T value) -> R;

template<typename T>
	requires std::is_arithmetic_v<T>
auto smooth(T value, T prev_value, float smoothing) -> T;

template<class T>
auto default_if_nullptr(const T* what, const T& default_value) -> const T&;

// Prohibit passing a temporary as a default value.
template<class T>
auto default_if_nullptr(const T* what, const T&& default_value) -> const T& = delete;

auto to_rect(SDL_FRect rect) -> SDL_Rect;
auto to_frect(SDL_Rect rect) -> SDL_FRect;

auto transform_point(glm::mat4 m) -> glm::vec4;
auto transform_point(glm::mat4 m, int x, int y, int z = 0) -> glm::vec4;
auto transform_point(glm::mat4 m, float x, float y, float z = 0.0f) -> glm::vec4;
auto transform_point(glm::mat4 m, SDL_Point p) -> glm::vec4;
auto transform_point(glm::mat4 m, SDL_FPoint p) -> glm::vec4;
auto transform_point(glm::mat4 m, glm::vec4 v) -> glm::vec4;

template<class X, class Y, class Z>
inline auto to_mat4(X x, Y y, Z z) -> glm::mat4
{
	return glm::translate(glm::mat4{1.0f}, glm::vec3{x, y, z});
}

template<class X, class Y>
inline auto to_mat4(X x, Y y) -> glm::mat4
{
	return to_mat4(x, y, 0);
}

// Return random number from closed range [a, b].
// Result is casted to ReturnType.
// Note that generator is created and seeded at first use, and cannot be altered later.
// TODO Add requirements:
// - Requirement from `std::uniform_int_distribution` for `IntType`:
//   `IntType` must be one of: short, int, long, long long, unsigned short, unsigned int, unsigned long, unsigned long long
// - `IntType` must be convertible to `ReturnType`.
template<typename ReturnType = int, typename IntType = int>
auto rand(IntType a, IntType b) -> ReturnType;

// Saturation arithmetic will be available since C++26, for now implement just what we need.
// TODO C++26 Use standard function instead.
template<std::unsigned_integral T>
constexpr auto saturating_sub(T x, T y) noexcept -> T;

} // namespace rh

#include "utils.ipp"

#endif // ROUNDHELL_UTILS_HPP

