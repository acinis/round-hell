#include "errors.hpp"

#include <format>
#include <utility>

#include <SDL3/SDL_error.h>

#include "utils.hpp"

namespace rh {

Error::Error(std::source_location location) noexcept
:
	_location{std::move(location)}
{
}

Error::Error(const std::string& message, std::source_location location) noexcept
:
	_message{message},
	_location{std::move(location)}
{
}

Error::Error(const std::string_view message, std::source_location location) noexcept
:
	_message{message},
	_location{std::move(location)}
{
}

Error::Error(const char* message, std::source_location location) noexcept
:
	_message{message},
	_location{std::move(location)}
{
}

auto Error::operator==(const Error& other) const noexcept -> bool
{
	return
		   message() == other.message()
		&& location().line() == other.location().line()
		&& location().column() == other.location().column()
		&& std::string_view{location().file_name()} == std::string_view{other.location().file_name()}
		&& std::string_view{location().function_name()} == std::string_view{other.location().function_name()}
	;
}

Error::operator bool() const noexcept
{
	return false;
}

auto Error::message(const std::string& message) noexcept -> void
{
	_message = message;
}

auto Error::message() const noexcept -> const std::string&
{
	return _message;
}

auto Error::location(const std::source_location& location) noexcept -> void
{
	_location = location;
}

auto Error::location() const noexcept -> const std::source_location&
{
	return _location;
}

auto Error::to_string() const noexcept -> std::string
{
	return std::format("{} ## {}", _message, ::rh::to_string(_location));
}

auto make_sdl_error(std::string_view message, std::source_location location) -> Error
{
	auto full_message = std::string{};
	if (! message.empty()) {
		full_message += message;
		full_message += ": ";
	}
	full_message += "[SDL] ";
	full_message += SDL_GetError();

	return Error{full_message, location};
}

} // namespace rh

