#ifndef ROUNDHELL_UTILS_TRAVERSE_HPP
#define ROUNDHELL_UTILS_TRAVERSE_HPP

#include <functional>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

namespace rh {

using EntityVisitor = std::function<void(entt::registry& registry, entt::entity entity)>;

auto pre_order_traverse(entt::registry& registry, entt::entity entity, EntityVisitor visitor) -> void;

auto post_order_traverse(entt::registry& registry, entt::entity entity, EntityVisitor visitor) -> void;

} // namespace rh

#endif // ROUNDHELL_UTILS_TRAVERSE_HPP

