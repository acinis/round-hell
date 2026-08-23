#ifndef ROUNDHELL_ANY_COMPONENT_HPP
#define ROUNDHELL_ANY_COMPONENT_HPP

#include <any>
#include <functional>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

namespace rh {

// Wrapper around `std::any` that knows how to `emplace()` stored component in `entt::registry`.
class AnyComponent
{
	std::any _component;
	std::function<void(entt::registry&, entt::entity, const std::any&)> _emplacer;

	template<typename ComponentType>
	static auto _make_emplacer() noexcept;

public:

	AnyComponent() = delete;

	AnyComponent(const AnyComponent& component) noexcept = default;
	AnyComponent(AnyComponent&& component) noexcept = default;
	auto operator=(const AnyComponent&) noexcept -> AnyComponent& = default;
	auto operator=(AnyComponent&&) noexcept -> AnyComponent& = default;

	~AnyComponent() noexcept = default;

	template<typename ComponentType>
	explicit AnyComponent(const ComponentType& component) noexcept;

	template<typename ComponentType>
	explicit AnyComponent(ComponentType&& component) noexcept;

	auto emplace_into(entt::registry& registry, entt::entity entity) const noexcept -> void;
};

template<typename ComponentType, typename... Args>
auto make_any_component(Args&&... args) noexcept -> AnyComponent;

} // namespace rh

#include "any_component.ipp"

#endif // ROUNDHELL_ANY_COMPONENT_HPP

