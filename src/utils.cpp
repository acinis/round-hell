#include "utils.hpp"

#include <format>
using namespace std::string_literals;
using namespace std::string_view_literals;

#include <SDL3/SDL_version.h>

#include "config/project_path.hpp"

namespace rh {

auto format_sdl_version(int compiled, std::optional<int> linked) noexcept -> std::string
{
	auto result = std::format(
		"v{}.{}.{}",
		SDL_VERSIONNUM_MAJOR(compiled),
		SDL_VERSIONNUM_MINOR(compiled),
		SDL_VERSIONNUM_MICRO(compiled)
	);

	if (linked && *linked != compiled) {
		result += std::format(
			" (v{}.{}.{})",
			SDL_VERSIONNUM_MAJOR(*linked),
			SDL_VERSIONNUM_MINOR(*linked),
			SDL_VERSIONNUM_MICRO(*linked)
		);
	}

	return result;
}

auto project_relative_path(const std::string_view path) -> std::string
{
	const auto base = std::string_view{PROJECT_PATH};
	auto relative = "?"s;

	if (path.starts_with(base)) {
		relative = path.substr(base.length());
	}

	return relative;
}

auto make_args(int argc, char *argv[]) -> std::vector<std::string_view>
{
	auto args = std::vector<std::string_view>{};

	for(int i = 0; i < argc; i++) {
		args.emplace_back(argv[i]);
	}

	return args;
}

auto to_string(const std::source_location& location) -> std::string
{
	return std::format(
		"{}:{}:{}: {}",
		project_relative_path(location.file_name()),
		location.line(),
		location.column(),
		location.function_name()
	);
}

auto to_rect(SDL_FRect rect) -> SDL_Rect
{
	return {
		static_cast<int>(rect.x),
		static_cast<int>(rect.y),
		static_cast<int>(rect.w),
		static_cast<int>(rect.h)
	};
}

auto to_frect(SDL_Rect rect) -> SDL_FRect
{
	return {
		static_cast<float>(rect.x),
		static_cast<float>(rect.y),
		static_cast<float>(rect.w),
		static_cast<float>(rect.h)
	};
}

auto transform_point(glm::mat4 m) -> glm::vec4
{
	return transform_point(m, glm::vec4{0.0f, 0.0f, 0.0f, 1.0f});
}

auto transform_point(glm::mat4 m, int x, int y, int z) -> glm::vec4
{
	return transform_point(m, glm::vec4{
		static_cast<float>(x),
		static_cast<float>(y),
		static_cast<float>(z),
		1.0f
	});
}

auto transform_point(glm::mat4 m, float x, float y, float z) -> glm::vec4
{
	return transform_point(m, glm::vec4{x, y, z, 1.0f});
}

auto transform_point(glm::mat4 m, SDL_Point p) -> glm::vec4
{
	return transform_point(m, glm::vec4{p.x, p.y, 0.0f, 1.0f});
}

auto transform_point(glm::mat4 m, SDL_FPoint p) -> glm::vec4
{
	return transform_point(m, glm::vec4{p.x, p.y, 0.0f, 1.0f});
}

auto transform_point(glm::mat4 m, glm::vec4 v) -> glm::vec4
{
	return m * v;
}

} // namespace rh

