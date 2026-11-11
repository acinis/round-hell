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
	 * @brief Default destructor.
	 */
	~Error() = default;

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

/** @internal */

namespace internal {

/**
 * @brief Internal helper for `rh::Unexpected`.
 *
 * This helper is intended to be used as `rh::Unexpected<ErrorType>` instead of `std::unexpected<ErrorType>`.
 * It will construct `ErrorType` from given arguments with correct source location.
 * Using `std::unexpected` directly leads to source location set to `std::expected` constructor.
 *
 * Usually we want source location pointing to place where `rh::Unexpected` instance is created, like `return Unexpected{"Message"};`.
 * Without this helper only way of getting correct source location is creating `ErrorType` directly, like `return Unexpected{Error{"Message"}};`.
 * This helper will be converted implicitly to `std::expected<SuccessType, ErrorType>` so it can be used transparently in return statement (for any `SuccessType`).
 *
 * `ErrorType` requirements:
 * - Type is copyable and movable.
 * - Object can be constructed from at most three arguments (plus `std::source_location` as last argument).
 *
 * @attention This helper was designed to be used with `rh::Error` as `ErrorType`. It is templated over `ErrorType` only for convenience.
 *
 * @tparam ErrorType Type used as error.
 */
template<typename ErrorType>
struct [[nodiscard]] UnexpectedHelper
{
	/** @brief Error instance. */
	ErrorType _error;

public:

	/**
	 * @brief Copy constructor (alternative form with non-const reference argument).
	 *
	 * Explicitly provided so compiler will not try to use templated forwarding constructors instead of copy and move ones.
	 *
	 * @param error The instance to copy from.
	 */
	explicit UnexpectedHelper(ErrorType& error) noexcept;

	/**
	 * @brief Copy constructor.
	 *
	 * Explicitly provided so compiler will not try to use templated forwarding constructors instead of copy and move ones.
	 *
	 * @param error The instance to copy from.
	 */
	explicit UnexpectedHelper(const ErrorType& error) noexcept;

	/**
	 * @brief Move constructor.
	 *
	 * Explicitly provided so compiler will not try to use templated forwarding constructors instead of copy and move ones.
	 *
	 * @param error The instance to move from.
	 */
	explicit UnexpectedHelper(ErrorType&& error) noexcept;

	/**
	 * @brief Move constructor (alternative form with const reference argument).
	 *
	 * Explicitly provided so compiler will not try to use templated forwarding constructors instead of copy and move ones.
	 *
	 * @note Const rvalue references are rather rare - this overload is just for completeness (so templated constructors won't be picked in some edge cases).
	 * @note If somehow this constructor will be called - it will make a copy (not move!) due to constant argument.
	 *
	 * @param error The instance to copy (sic!) from.
	 */
	explicit UnexpectedHelper(const ErrorType&& error) noexcept;

	/**
	 * @brief Construct internal `Error` instance from passed arguments.
	 * @param location Source location (by default the location where `UnexpectedHelper` instance is created).
	 */
	explicit UnexpectedHelper(std::source_location location = std::source_location::current()) noexcept;

	/**
	 * @brief @copybrief UnexpectedHelper(std::source_location)
	 * @tparam T1 Type of first argument.
	 * @param arg1 First argument that will be forwarded to `Error`'s constructor.
	 * @param location Source location (by default the location where `UnexpectedHelper` instance is created).
	 */
	template<typename T1>
	explicit UnexpectedHelper(T1&& arg1, std::source_location location = std::source_location::current()) noexcept;

	/**
	 * @brief @copybrief UnexpectedHelper(std::source_location)
	 * @tparam T1 Type of first argument.
	 * @tparam T2 Type of second argument.
	 * @param arg1 First argument that will be forwarded to `Error`'s constructor.
	 * @param arg2 Second argument that will be forwarded to `Error`'s constructor.
	 * @param location Source location (by default the location where `UnexpectedHelper` instance is created).
	 */
	template<typename T1, typename T2>
	explicit UnexpectedHelper(T1&& arg1, T2&& arg2, std::source_location location = std::source_location::current()) noexcept;

	/**
	 * @brief @copybrief UnexpectedHelper(std::source_location)
	 * @tparam T1 Type of first argument.
	 * @tparam T2 Type of second argument.
	 * @tparam T3 Type of third argument.
	 * @param arg1 First argument that will be forwarded to `Error`'s constructor.
	 * @param arg2 Second argument that will be forwarded to `Error`'s constructor.
	 * @param arg3 Third argument that will be forwarded to `Error`'s constructor.
	 * @param location Source location (by default the location where `UnexpectedHelper` instance is created).
	 */
	template<typename T1, typename T2, typename T3>
	explicit UnexpectedHelper(T1&& arg1, T2&& arg2, T3&& arg3, std::source_location location = std::source_location::current()) noexcept;

	/**
	 * @brief Catch-all constructor - produce cleaner compilation error when there are more arguments than we can handle.
	 *
	 * This constructor will be called if someone tries to use `Unexpected` with unsupported number of arguments.
	 *
	 * @tparam Args Types of arguments.
	 */
	template<typename... Args>
	explicit UnexpectedHelper(Args&&...) noexcept;

	/**
	 * @brief Convert this instance to `rh::Expected` (aka `std::expected`).
	 * @note This overoad will move from internal `ErrorType` instance.
	 */
	template<typename SuccessType>
	[[nodiscard]] operator std::expected<SuccessType, ErrorType>() && noexcept;

	/**
	 * @brief Convert this instance to `rh::Expected` (aka `std::expected`).
	 * @note This overoad will copy internal `ErrorType` instance.
	 */
	template<typename SuccessType>
	[[nodiscard]] operator std::expected<SuccessType, ErrorType>() & noexcept;
};

} // namespace internal

/** @endinternal */

} // namespace rh

#include "errors.ipp"

#endif // ROUNDHELL_ERRORS_HPP

