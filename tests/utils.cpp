#include <catch2/catch_test_macros.hpp>

#include <array>
#include <stdfloat>
#include <string>
#include <utility>
using namespace std::string_literals;

#include <SDL3/SDL_version.h>

#include "config/project_path.hpp"
#include "utils.hpp"

TEST_CASE("Utils", "[utils]")
{
	SECTION("format_sdl_version()")
	{
		auto v123 = rh::format_sdl_version(SDL_VERSIONNUM(1, 2, 3));
		auto v123_456 = rh::format_sdl_version(SDL_VERSIONNUM(1, 2, 3), SDL_VERSIONNUM(4, 5, 6));
		REQUIRE(v123 == "v1.2.3"s);
		REQUIRE(v123_456 == "v1.2.3 (v4.5.6)"s); // TODO Hardcoded version format string
	}

	SECTION("project_relative_path()")
	{
		auto base = std::string{rh::PROJECT_PATH};
		auto proj = "foo/bar"s;
		auto full = base + proj;
		REQUIRE(rh::project_relative_path(full) == proj);
	}

	SECTION("uround()")
	{
		auto pairs = std::array<std::pair<double, unsigned>, 8>{
			std::make_pair(-5.55, 0),

			std::make_pair(-1.00, 0),
			std::make_pair( 0.00, 0),
			std::make_pair( 1.00, 1),

			std::make_pair( 5.00, 5),
			std::make_pair( 5.21, 5),
			std::make_pair( 5.50, 6),
			std::make_pair( 5.76, 6)
		};

		// Test with various floating-point types.
		for (const auto& p : pairs) {
			REQUIRE(rh::uround<unsigned>(p.first) == p.second);
			REQUIRE(rh::uround<unsigned>(static_cast<float>(p.first)) == p.second);
			REQUIRE(rh::uround<unsigned>(static_cast<std::float32_t>(p.first)) == p.second);
			REQUIRE(rh::uround<unsigned>(static_cast<std::bfloat16_t>(p.first)) == p.second);
		}

		// Extra test with different unsigned integral type.
		REQUIRE(rh::uround<unsigned char>(76.77777) == static_cast<unsigned char>(77));
	}
}

