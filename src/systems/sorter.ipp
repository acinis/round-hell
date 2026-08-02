#include "components/order.hpp"

#include <entt/entity/entity.hpp>

namespace rh::S {

template<class ComponentType>
auto Sorter::run(entt::registry& registry) -> void
{
	registry.sort<ComponentType>(
		[&registry](const entt::entity lhs, const entt::entity rhs)
		{
			C::Order* lhs_c_order = registry.try_get<C::Order>(lhs);
			C::Order* rhs_c_order = registry.try_get<C::Order>(rhs);

			int lhs_z_index = C::Order::DEFAULT;
			if (lhs_c_order) {
				lhs_z_index = lhs_c_order->order();
			}

			int rhs_z_index = C::Order::DEFAULT;
			if (rhs_c_order) {
				rhs_z_index = rhs_c_order->order();
			}

			return lhs_z_index < rhs_z_index;
		}
	);
}

} // namespace rh::S

