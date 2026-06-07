#ifndef ROUNDHELL_RESOURCE_MULTI_CACHE_HPP
#define ROUNDHELL_RESOURCE_MULTI_CACHE_HPP

/**
 * @file src/resource_multi_cache.hpp
 * @brief Wrapper around multiple `entt::resource_cache` with `rh::Expected` error reporting.
 */

#include <any>
#include <cassert>
#include <expected>
#include <memory>
#include <optional>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

#include <entt/core/hashed_string.hpp>
#include <entt/resource/cache.hpp>
#include <entt/resource/resource.hpp>

#include "errors.hpp"
#include "resource_loader_for.hpp"

namespace rh {

/**
 * @brief Simple class that create and wrap multiple `entt::resource_cache` instances.
 *
 * Wrapper around `entt::resource_cache`.
 * Automatically acts on cache for given resource type (creates new caches on the fly - but
 * currently it won't remove empty caches).
 * Resource loaders can be registered via `rh::ResourceLoaderFor` structure template
 * specializations.
 * Uses another error reporting approach - loaders can provide `rh::Error` that will be returned
 * from methods in `rh::Expected`.
 */
class ResourceMultiCache
{
	std::unordered_map<std::type_index, std::any> _caches;

	/**
	 * @internal
	 *
	 * @brief Get reference to `entt::resource_cache` instance for given resource and loader type.
	 *
	 * It will create given cache, if it does not exists.
	 *
	 * @tparam ResourceType Type of resource.
	 * @tparam LoaderType Type of resource loader (by default use type from `ResourceLoaderFor`
	 *         specialization.
	 * @return Reference to appropriate cache instance.
	 */
	template<typename ResourceType, typename LoaderType = ResourceLoaderFor<ResourceType>::Type>
	[[nodiscard]] auto cache() noexcept -> entt::resource_cache<ResourceType, LoaderType>&;

public:

	/**
	 * @brief Default constructor.
	 */
	ResourceMultiCache() noexcept = default;

	/**
	 * @brief Default copy constructor.
	 */
	ResourceMultiCache(const ResourceMultiCache&) noexcept = default;

	/**
	 * @brief Default move constructor.
	 */
	ResourceMultiCache(ResourceMultiCache&&) noexcept = default;

	/**
	 * @brief Default destructor.
	 */
	~ResourceMultiCache() = default;

	/**
	 * @brief Default copy assignment operator.
	 * @return This `ResourceMultiCache` instance.
	 */
	auto operator=(const ResourceMultiCache&) noexcept -> ResourceMultiCache& = default;

	/**
	 * @brief Default move assignment operator.
	 * @return This `ResourceMultiCache` instance.
	 */
	auto operator=(ResourceMultiCache&&) noexcept -> ResourceMultiCache& = default;

	/**
	 * @brief Loads a resource, if its identifier does not exist.
	 *
	 * `load()` will forward arguments to `load()` method of appropriate `cache` instance, and
	 * `force_load()` will forward to `force_load()`. For more see their docs in EnTT's
	 * documentation.
	 *
	 * @note
	 * First argument for resource loader must be `std::optional<rh::Error>&`. It will be used to
	 * report loading errors - loader must set error as optional's value. This error will be
	 * returned from `load()` and `force_load()` calls as `rh::Expected<void>`.
	 *
	 * @tparam ResourceType Type of resource to load.
	 * @tparam Args Types of arguments to use to load the resource if required.
	 * @param id Unique resource identifier.
	 * @param args Arguments to use to load the resource if required.
	 * @return Nothing (void) as expected value or `rh::Error` as unexpected value on error.
	 */
	template<typename ResourceType, typename... Args>
	auto load(entt::hashed_string::hash_type id, Args&&... args) noexcept -> Expected<void>;

	/**
	 * @brief Force loading a resource, even if its identifier exists already.
	 *
	 * @copydetails load
	 *
	 */
	template<typename ResourceType, typename... Args>
	auto force_load(entt::hashed_string::hash_type id, Args&&... args) noexcept -> Expected<void>;

	/**
	 * @brief Get handle to given resource.
	 *
	 * @attention
	 * Resource may be invalid, check it first in boolean context, eg. `if (res) {}`.
	 *
	 * @tparam ResourceType Type of resource.
	 * @param id Unique resource identifier.
	 * @return Resource handle (may be invalid).
	 */
	template<typename ResourceType, typename LoaderType = ResourceLoaderFor<ResourceType>::Type>
	[[nodiscard]] auto get(entt::hashed_string::hash_type id) noexcept -> entt::resource<ResourceType>;
};

} // namespace rh

#include "resource_multi_cache.ipp"

#endif // ROUNDHELL_RESOURCE_MULTI_CACHE_HPP

