#include <utility>
#include <type_traits>

namespace rh {

template<class Component, class... Args>
auto EntityBuilder::emplace(Args&&... args) -> EntityBuilder&
{
	_registry.emplace<Component>(_entity, std::forward<Args>(args)...);
	return *this;
}

template<class Component, class... Args>
auto EntityBuilder::emplace_or_replace(Args&&... args) -> EntityBuilder&
{
	_registry.emplace_or_replace<Component>(_entity, std::forward<Args>(args)...);
	return *this;
}

template<class Component, class... Args>
auto EntityBuilder::replace(Args&&... args) -> EntityBuilder&
{
	_registry.replace<Component>(_entity, std::forward<Args>(args)...);
	return *this;
}

template<class Component, std::invocable... Invocables>
auto EntityBuilder::patch(Invocables&&... invocables) -> EntityBuilder&
{
	_registry.patch<Component>(_entity, std::forward<Invocables>(invocables)...);
	return *this;
}

template<class Component>
auto EntityBuilder::erase() -> EntityBuilder&
{
	_registry.erase<Component>(_entity);
	return *this;
}

template<class Component>
auto EntityBuilder::remove() -> EntityBuilder&
{
	_registry.remove<Component>(_entity);
	return *this;
}

template<entt::id_type Tag>
auto EntityBuilder::emplace_tag() -> EntityBuilder&
{
	_registry.emplace<entt::tag<Tag>>(_entity);
	return *this;
}

template<entt::id_type Tag>
auto EntityBuilder::emplace_or_replace_tag() -> EntityBuilder&
{
	_registry.emplace_or_replace<entt::tag<Tag>>(_entity);
	return *this;
}

template<entt::id_type Tag>
auto EntityBuilder::replace_tag() -> EntityBuilder&
{
	_registry.replace<entt::tag<Tag>>(_entity);
	return *this;
}

template<entt::id_type Tag>
auto EntityBuilder::erase_tag() -> EntityBuilder&
{
	_registry.erase<entt::tag<Tag>>(_entity);
	return *this;
}

template<entt::id_type Tag>
auto EntityBuilder::remove_tag() -> EntityBuilder&
{
	_registry.remove<entt::tag<Tag>>(_entity);
	return *this;
}

} // namespace rh

