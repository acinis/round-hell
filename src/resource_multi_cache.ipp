#include <utility>

namespace rh {

template<typename ResourceType, typename LoaderType>
[[nodiscard]] auto ResourceMultiCache::cache() noexcept -> entt::resource_cache<ResourceType, LoaderType>&
{
	using CacheType = entt::resource_cache<ResourceType, LoaderType>;
	auto& cache = _caches[std::type_index(typeid(CacheType))];
	if (! cache.has_value()) { // Freshly constructed instance - empty `any`
		cache = CacheType{};
	}
	assert((cache.type() == typeid(CacheType)) && "INTERNAL: std::any type mismatch in _caches");
	return std::any_cast<CacheType&>(cache);
}

template<typename ResourceType, typename... Args>
auto ResourceMultiCache::load(entt::hashed_string::hash_type id, Args&&... args) noexcept -> Expected<void>
{
	auto error = std::optional<Error>{};

	cache<ResourceType>().load(id, error, std::forward<Args>(args)...);

	if (error) {
		return Unexpected{*error};
	}

	return {};
}

template<typename ResourceType, typename... Args>
auto ResourceMultiCache::force_load(entt::hashed_string::hash_type id, Args&&... args) noexcept -> Expected<void>
{
	auto error = std::optional<Error>{};

	cache<ResourceType>().force_load(id, error, std::forward<Args>(args)...);

	if (error) {
		return Unexpected{*error};
	}

	return {};
}

template<typename ResourceType, typename LoaderType>
auto ResourceMultiCache::get(entt::hashed_string::hash_type id) noexcept -> entt::resource<ResourceType>
{
	auto resource = cache<ResourceType, LoaderType>()[id];
	return resource;
}

} // namespace rh

