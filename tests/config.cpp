#include <catch2/catch_test_macros.hpp>

#include <string_view>

#include "config/commit.hpp"
#include "config/project_path.hpp"

TEST_CASE("CMake configured last commit ID", "[config]")
{
	REQUIRE_FALSE(std::string_view{ROUNDHELL_COMMIT}.empty());
}

TEST_CASE("CMake configured project path", "[config]")
{
	REQUIRE_FALSE(rh::PROJECT_PATH.empty());
}

