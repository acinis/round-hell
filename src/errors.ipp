#include <utility>

namespace rh {

namespace internal {

template<typename ErrorType>
UnexpectedHelper<ErrorType>::UnexpectedHelper(ErrorType& error) noexcept
:
	_error{error}
{
}

template<typename ErrorType>
UnexpectedHelper<ErrorType>::UnexpectedHelper(const ErrorType& error) noexcept
:
	_error{error}
{
}

template<typename ErrorType>
UnexpectedHelper<ErrorType>::UnexpectedHelper(ErrorType&& error) noexcept
:
	_error{std::move(error)}
{
}

template<typename ErrorType>
UnexpectedHelper<ErrorType>::UnexpectedHelper(const ErrorType&& error) noexcept
:
	_error{error}
{
}

template<typename ErrorType>
UnexpectedHelper<ErrorType>::UnexpectedHelper(std::source_location location) noexcept
:
	_error{location}
{
}

template<typename ErrorType>
template<typename T1>
UnexpectedHelper<ErrorType>::UnexpectedHelper(T1&& arg1, std::source_location location) noexcept
:
	_error{std::forward<T1>(arg1), location}
{
}

template<typename ErrorType>
template<typename T1, typename T2>
UnexpectedHelper<ErrorType>::UnexpectedHelper(T1&& arg1, T2&& arg2, std::source_location location) noexcept
:
	_error{std::forward<T1>(arg1), std::forward<T2>(arg2), location}
{
}

template<typename ErrorType>
template<typename T1, typename T2, typename T3>
UnexpectedHelper<ErrorType>::UnexpectedHelper(T1&& arg1, T2&& arg2, T3&& arg3, std::source_location location) noexcept
:
	_error{std::forward<T1>(arg1), std::forward<T2>(arg2), std::forward<T3>(arg3), location}
{
}

template<typename ErrorType>
template<typename... Args>
UnexpectedHelper<ErrorType>::UnexpectedHelper(Args&&...) noexcept
{
	static_assert(false, "rh::internal::UnexpectedHelper: Unsupported amount of arguments passed to forwarding constructor");
}

template<typename ErrorType>
template<typename SuccessType>
UnexpectedHelper<ErrorType>::operator std::expected<SuccessType, ErrorType>() && noexcept
{
	return std::unexpected<ErrorType>{std::move(_error)};
}

template<typename ErrorType>
template<typename SuccessType>
UnexpectedHelper<ErrorType>::operator std::expected<SuccessType, ErrorType>() & noexcept
{
	return std::unexpected<ErrorType>{_error};
}

} // namespace internal

} // namespace rh

