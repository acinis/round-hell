namespace rh {

template<class T>
auto get_from_parent(entt::registry& registry, entt::entity entity, const T& default_component) noexcept -> const T&
{
	const auto* c_relation = registry.try_get<C::Relation>(entity);

	if (! c_relation) {
		return default_component;
	}

	return get_from_parent<T>(registry, *c_relation, default_component);
}

template<class T>
auto get_from_parent(entt::registry& registry, const C::Relation& c_relation, const T& default_component) noexcept -> const T&
{
	if (! c_relation.has_parent()) {
		return default_component;
	}

	auto parent = c_relation.parent();

	const auto* parent_component = registry.try_get<T>(parent);

	if (! parent_component) {
		return default_component;
	}

	return *parent_component;
}

} // namespace rh

