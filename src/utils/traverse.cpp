#include "utils/traverse.hpp"

#include <cstddef>

#include "components/relation.hpp"

namespace rh::internal {

enum class TraverseOrder
{
	// Depth-first:
	PreOrder,
	PostOrder,
};

auto traverse(TraverseOrder order, entt::registry& registry, entt::entity entity, EntityVisitor visitor) -> void
{
	if (order == TraverseOrder::PreOrder) {
		visitor(registry, entity);
	}

	auto* c_relation = registry.try_get<C::Relation>(entity);

	if (c_relation && c_relation->has_children()) {

		const auto first = c_relation->first();
		auto current = first;

		do {
			traverse(order, registry, current, visitor);

			auto current_c_relation = registry.try_get<C::Relation>(current);

			if (nullptr == current_c_relation) {
				break;
			}

			current = current_c_relation->next();
		}
		while (current != first);

	}

	if (order == TraverseOrder::PostOrder) {
		visitor(registry, entity);
	}
}

} // namespace rh::internal

namespace rh {

auto pre_order_traverse(entt::registry& registry, entt::entity entity, EntityVisitor visitor) -> void
{
	internal::traverse(internal::TraverseOrder::PreOrder, registry, entity, visitor);
}

auto post_order_traverse(entt::registry& registry, entt::entity entity, EntityVisitor visitor) -> void
{
	internal::traverse(internal::TraverseOrder::PostOrder, registry, entity, visitor);
}

} // namespace rh

