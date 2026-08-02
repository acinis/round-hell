#ifndef ROUNDHELL_COMPONENTS_ORDER_HPP
#define ROUNDHELL_COMPONENTS_ORDER_HPP

#include <limits>

namespace rh::C {

// Component for visual ordering of entities (order of drawing).
// Entities with lower order value are drawn earlier on screen.
// If there is no Order component, default order is equal to C::Order::DEFAULT_ORDER.

class Order
{
public:
	using ValueType = int;

	static constexpr ValueType DEFAULT = 0;
	static constexpr ValueType LOWEST = std::numeric_limits<ValueType>::min();
	static constexpr ValueType HIGHEST = std::numeric_limits<ValueType>::max();

private:
	ValueType _z_index = DEFAULT;

public:
	Order() noexcept = default;
	Order(ValueType z_index) noexcept;
	~Order() = default;

	auto order(ValueType z_index) noexcept -> void;
	auto order() const noexcept -> ValueType;
};

} // namespace rh::C

#endif // ROUNDHELL_COMPONENTS_ORDER_HPP

