#include <utility>

namespace rh {

template<typename ComponentType>
auto AnyComponent::_make_emplacer() noexcept
{
	return [](entt::registry& registry, entt::entity entity, const std::any& component) -> void
	{
		// TODO Maybe check any_cast for errors? But we *know* what type is inside `any`, right?
		registry.emplace<ComponentType>(entity, std::any_cast<ComponentType>(component));
	};
}

template<typename ComponentType>
AnyComponent::AnyComponent(const ComponentType& component) noexcept
:
	_component {component}
{
	_emplacer = _make_emplacer<ComponentType>();
}

template<typename ComponentType>
AnyComponent::AnyComponent(ComponentType&& component) noexcept
:
	_component {std::move(component)}
{
	_emplacer = _make_emplacer<ComponentType>();
}

template<typename ComponentType, typename... Args>
auto make_any_component(Args&&... args) noexcept -> AnyComponent
{
	return AnyComponent{ComponentType{std::forward<Args>(args)...}};
}

} // namespace rh

