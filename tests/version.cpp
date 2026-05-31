#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <format>
#include <string>
using namespace std::string_literals;

#include "version.hpp"

#define RH_STR(arg) #arg
#define RH_XSTR(arg) RH_STR(arg)

TEST_CASE("Version preprocessor constants", "[version]")
{
	SECTION("Is defined?")
	{
		#if defined(ROUNDHELL_VERSION_MAJOR) \
		 && defined(ROUNDHELL_VERSION_MINOR) \
		 && defined(ROUNDHELL_VERSION_PATCH)
			SUCCEED("Version macros defined");
		#else
			FAIL("Version macros not defined");
		#endif
	}

	SECTION("Is valid?")
	{
		auto matcher = Catch::Matchers::Matches("^(0|[1-9]{1}[0-9]*)$");
		REQUIRE_THAT(RH_XSTR(ROUNDHELL_VERSION_MAJOR), matcher);
		REQUIRE_THAT(RH_XSTR(ROUNDHELL_VERSION_MINOR), matcher);
		REQUIRE_THAT(RH_XSTR(ROUNDHELL_VERSION_PATCH), matcher);
	}
}

TEST_CASE("Version preprocessor helpers", "[version]")
{
	SECTION("Version string")
	{
		auto version_str = std::format(
			"{}.{}.{}",
			ROUNDHELL_VERSION_MAJOR,
			ROUNDHELL_VERSION_MINOR,
			ROUNDHELL_VERSION_PATCH
		);

		REQUIRE(std::string{ROUNDHELL_MAKE_VERSION(1, 2, 3)} == "1.2.3"s);
		REQUIRE(std::string{ROUNDHELL_VERSION} == version_str);
	}

	SECTION("Version number")
	{
		auto version_number = ROUNDHELL_MAKE_VERSION_NUMBER(
			ROUNDHELL_VERSION_MAJOR,
			ROUNDHELL_VERSION_MINOR,
			ROUNDHELL_VERSION_PATCH
		);

		REQUIRE(ROUNDHELL_MAKE_VERSION_NUMBER(1, 2, 3) == 1002003);
		REQUIRE(ROUNDHELL_VERSION_NUMBER == version_number);
	}
}

