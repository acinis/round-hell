#ifndef ROUNDHELL_UTILS_ENTT_HPP
#define ROUNDHELL_UTILS_ENTT_HPP

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "components/relation.hpp"

namespace rh {

// Helper: we can use it in constructors' init list, so `entt::entity` member can be `const`.
auto create_entity_if_null(entt::registry& registry, entt::entity entity) -> entt::entity;

template<class T>
auto get_from_parent(entt::registry& registry, entt::entity entity, const T& default_component) noexcept -> const T&;

template<class T>
auto get_from_parent(entt::registry& registry, entt::entity entity, const T&& default_component) -> const T& = delete; // Prohibit passing a temporary as a default value

template<class T>
auto get_from_parent(entt::registry& registry, const C::Relation& c_relation, const T& default_component) noexcept -> const T&;

template<class T>
auto get_from_parent(entt::registry& registry, const C::Relation& c_relation, const T&& default_component) -> const T& = delete; // Prohibit passing a temporary as a default value

} // namespace rh

#include "utils/entt.ipp"

#endif // ROUNDHELL_UTILS_ENTT_HPP

