#include "components/order.hpp"

namespace rh::C {

Order::Order(ValueType z_index) noexcept
:
	_z_index {z_index}
{
}

auto Order::order(ValueType z_index) noexcept -> void
{
	_z_index = z_index;
}

auto Order::order() const noexcept -> ValueType
{
	return _z_index;
}

} // namespace rh::C

