#include <cmath>
#include <random>

namespace rh {

template<std::floating_point T>
auto iround(T v) -> int
{
	return static_cast<int>(std::lround(v));
}

template<std::unsigned_integral R, std::floating_point T>
constexpr auto uround(T value) -> R
{
	return static_cast<R>(std::max(T{0}, std::round(value)));
}

template<typename T>
	requires std::is_arithmetic_v<T>
auto smooth(T value, T prev_value, float smoothing) -> T
{
	return (prev_value * smoothing) + (value * (1.0f - smoothing));
}

template<class T>
auto default_if_nullptr(const T* what, const T& default_value) -> const T&
{
	if (what) {
		return *what;
	}
	else {
		return default_value;
	}
}

template<typename ReturnType, typename IntType>
auto rand(IntType a, IntType b) -> ReturnType
{
	static auto gen = std::mt19937(std::random_device{}());
	auto distrib = std::uniform_int_distribution<IntType>(a, b);
	return static_cast<ReturnType>(distrib(gen));
}

template<std::unsigned_integral T>
constexpr auto saturating_sub(T x, T y) noexcept -> T
{
	if (x <= y) {
		return 0;
	}
	return x - y;
}

constexpr auto from_seconds(Uint64 value) noexcept -> Uint64
{
	return value * 1'000'000'000;
}

constexpr auto from_milliseconds(Uint64 value) noexcept -> Uint64
{
	return value * 1'000'000;
}

constexpr auto to_seconds(Uint64 value) noexcept -> Uint64
{
	return value / 1'000'000'000;
}

constexpr auto to_milliseconds(Uint64 value) noexcept -> Uint64
{
	return value / 1'000'000;
}

constexpr auto to_fseconds(Uint64 value) noexcept -> float
{
	return value / 1'000'000'000.0f;
}

constexpr auto to_fmilliseconds(Uint64 value) noexcept -> float
{
	return value / 1'000'000.0f;
}

constexpr auto to_fminutes(Uint64 value) noexcept -> float
{
	return value / 1'000'000'000.0f / 60.0f;
}

} // namespace rh

