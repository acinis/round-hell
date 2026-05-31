#ifndef ROUNDHELL_ERRORS_HPP
#define ROUNDHELL_ERRORS_HPP

/**
 * @file src/errors.hpp
 * @brief Representing an error.
 */

#include <expected>
#include <source_location>
#include <string>
#include <string_view>
using namespace std::literals::string_view_literals;

namespace rh {

/**
 * @brief Class representing an error.
 */
class [[nodiscard]] Error
{
	std::string _message;
	std::source_location _location;

public:

	/**
	 * @brief Default initialization is not allowed.
	 */
	Error() = delete;

	/**
	 * @brief Creates a new `Error` instance.
	 * @param location Source location (by default a location where `Error` instance is created).
	 */
	Error(std::source_location location = std::source_location::current()) noexcept;

	/**
	 * @brief Creates a new `Error` instance.
	 * @param message Error message.
	 * @param location Source location (by default a location where `Error` instance is created).
	 */
	Error(const std::string& message, std::source_location location = std::source_location::current()) noexcept;

	/**
	 * @brief Creates a new `Error` instance.
	 * @param message Error message - will be copied to internal `std::string`.
	 * @param location Source location (by default a location where `Error` instance is created).
	 */
	Error(const std::string_view message, std::source_location location = std::source_location::current()) noexcept;

	/**
	 * @brief Creates a new `Error` instance.
	 * @param message Error message - will be copied to internal `std::string`.
	 * @param location Source location (by default a location where `Error` instance is created).
	 */
	Error(const char* message, std::source_location location = std::source_location::current()) noexcept;

	/**
	 * @brief Default copy constructor.
	 */
	Error(const Error&) noexcept = default;

	/**
	 * @brief Default move constructor.
	 */
	Error(Error&&) noexcept = default;

	/**
	 * @brief Default destructor.
	 */
	~Error() = default;

	/**
	 * @brief Default copy assignment operator.
	 * @return This `Error` instance.
	 */
	auto operator=(const Error&) noexcept -> Error& = default;

	/**
	 * @brief Default move assignment operator.
	 * @return This `Error` instance.
	 */
	auto operator=(Error&&) noexcept -> Error& = default;

	/**
	 * @brief Most of comparisons are prohibited.
	 */
	[[nodiscard]] auto operator<=>(const Error&) const = delete;

	/**
	 * @brief Equality operator.
	 * @param other Other `rh::Error` instance to compare.
	 * @return `true` if errors are identical, `false` otherwise.
	 */
	[[nodiscard]] auto operator==(const Error& other) const noexcept -> bool;

	/**
	 * @brief `bool` conversion operator.
	 * @return Always returns `false`.
	 */
	operator bool() const noexcept;

	/**
	 * @brief Message setter.
	 * @param message New message to set.
	 */
	auto message(const std::string& message) noexcept -> void;

	/**
	 * @brief Message getter.
	 * @return Error message.
	 */
	[[nodiscard]] auto message() const noexcept -> const std::string&;

	/**
	 * @brief Source location setter.
	 * @param location New source location to set.
	 */
	auto location(const std::source_location& location) noexcept -> void;

	/**
	 * @brief Source location getter.
	 * @return Error source location.
	 */
	[[nodiscard]] auto location() const noexcept -> const std::source_location&;

	/**
	 * @brief Converts this `Error` instance to string.
	 * @return This error as `std::string`.
	 */
	[[nodiscard]] auto to_string() const noexcept -> std::string;
};

/**
 * @brief Helper for creating `std::expected` with `rh::Error` as the type of the unexpected value.
 * @tparam T The type of the expected value.
 */
template<typename T>
using Expected = std::expected<T, Error>;

/**
 * @brief Helper for creating `std::expected` with `rh::Error` as the unexpected value.
 *
 * Not strictly needed, just for completeness' sake.
 *
 */
using Unexpected = std::unexpected<Error>;

// TODO Rename to `last_sdl_error()`?
/**
 * @brief Helper for creating SDL error.
 *
 * `message` will be prepended to SDL's error text. By default message is empty.
 * This helper will call `SDL_GetError()` to retrieve last SDL's error message.
 *
 * @attention You must manually check, if there *was* an error in SDL's call.
 *
 * @param message Message for `rh::Error` object (empty by default).
 * @param location Source location (by default this is place where `make_sdl_error()` was called).
 * @return `rh::Error` instance.
 */
auto make_sdl_error(std::string_view message = {}, std::source_location location = std::source_location::current()) -> Error;

} // namespace rh

#endif // ROUNDHELL_ERRORS_HPP

