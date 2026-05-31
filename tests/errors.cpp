#include <catch2/catch_test_macros.hpp>

#include <expected>
#include <string>
#include <string_view>
using namespace std::string_literals;

#include <SDL3/SDL_error.h>

#include "errors.hpp"
#include "utils.hpp"

namespace {

// Helper for comparing source locations
auto is_eq_src_loc(const std::source_location& a, const std::source_location& b) noexcept -> bool
{
	return
		   a.line() == b.line()
		&& a.column() == b.column()
		&& std::string_view{a.file_name()} == std::string_view{b.file_name()}
		&& std::string_view{a.function_name()} == std::string_view{b.function_name()}
	;
}

} // namespace

TEST_CASE("`rh::Error` class", "[errors]")
{
	SECTION("Construction")
	{
		REQUIRE_FALSE(std::is_default_constructible_v<rh::Error>);

		REQUIRE(std::is_nothrow_constructible_v<rh::Error, std::source_location>);
		REQUIRE(std::is_nothrow_constructible_v<rh::Error, std::string>);
		REQUIRE(std::is_nothrow_constructible_v<rh::Error, std::string, std::source_location>);

		REQUIRE(std::is_nothrow_copy_constructible_v<rh::Error>);
		REQUIRE(std::is_nothrow_move_constructible_v<rh::Error>);
		REQUIRE(std::is_nothrow_copy_assignable_v<rh::Error>);
		REQUIRE(std::is_nothrow_move_assignable_v<rh::Error>);
	}

	SECTION("Equality comparison")
	{
		auto location = std::source_location::current();

		auto a1 = rh::Error{"Message", location};
		auto a2 = rh::Error{"Message", location};

		auto b1 = rh::Error{"Other text", location};
		auto b2 = rh::Error{"Message"};

		REQUIRE(a1 == a2);
		REQUIRE_FALSE(a1 == b1);
		REQUIRE_FALSE(a1 == b2);
	}

	SECTION("Conversion to bool")
	{
		REQUIRE_FALSE(rh::Error{""});
		REQUIRE_FALSE(rh::Error{"Some message"});
	}

	SECTION("Stringification")
	{
		auto message = "Some message"s;
		auto location = std::source_location::current();

		auto str = std::format(
			"{} ## {}", // TODO Hardcoded error format string
			message,
			rh::to_string(location)
		);

		REQUIRE(str == rh::Error{message, location}.to_string());
	}
}

TEST_CASE("`rh::Error` class - Setters and getters", "[errors]")
{
	auto location = std::source_location::current();
	auto error = rh::Error{"Message", location};

	SECTION("Getters")
	{
		REQUIRE(error.message() == "Message"s);
		REQUIRE(is_eq_src_loc(error.location(), location));
	}

	SECTION("Setters - message()")
	{
		error.message("New message");
		REQUIRE(error.message() == "New message"s);
	}

	SECTION("Setters - location()")
	{
		auto new_location = std::source_location::current();
		error.location(new_location);
		REQUIRE(is_eq_src_loc(error.location(), new_location));
	}
}

TEST_CASE("`std::expected` aliases", "[errors]")
{
	REQUIRE(std::is_same_v<std::expected<int, rh::Error>, rh::Expected<int>>);
	REQUIRE(std::is_same_v<std::unexpected<rh::Error>, rh::Unexpected>);
}

TEST_CASE("`make_sdl_error()` helper", "[errors]")
{
	auto location = std::source_location::current();
	auto message = "Some error message"s;
	SDL_SetError(message.c_str());

	SECTION("Default message")
	{
		auto error_1 = rh::make_sdl_error({}, location);
		auto error_2 = rh::Error{"[SDL] " + message, location};
		REQUIRE(error_1 == error_2);
		REQUIRE(SDL_GetError() == message);
	}

	SECTION("Default message - default arguments")
	{
		auto error_1 = rh::make_sdl_error();
		auto error_2 = rh::Error{"[SDL] " + message};
		REQUIRE(error_1.message() == error_2.message());
		REQUIRE(SDL_GetError() == message);
	}

	SECTION("Custom message")
	{
		auto custom_message = "Custom message"s;
		auto error = rh::make_sdl_error(custom_message);
		REQUIRE(error.message() == custom_message + ": [SDL] " + message);
		REQUIRE(SDL_GetError() == message);
	}
}

