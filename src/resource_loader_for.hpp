#ifndef ROUNDHELL_RESOURCE_LOADER_FOR_HPP
#define ROUNDHELL_RESOURCE_LOADER_FOR_HPP

/**
 * @file src/resource_loader_for.hpp
 * @brief Helper for registering loader type for given resource.
 */

#include <type_traits>

namespace rh {

/**
 * @brief Helper for registering loader type for given resource.
 *
 * Users can specialize this structure template for given resource type, so they can left
 * `LoaderType` parameter in `ResourceMultiCache` unspecified. By default, `ResourceMultiCache` will
 * get `LoaderType` from these specializations.
 *
 * Specialization must define a `Type` member that is an alias for loader type.
 *
 * For more informations about loaders see their EnTT's documentation or oficial wiki page available
 * [here](https://github.com/skypjack/entt/wiki/Resource-management).
 *
 * Example for resource type `app::Sound` and loader type `app::SoundLoader`
 * @code
 * template<>
 * struct rh::ResourceLoaderFor<Sound> {
 *     using Type = SoundLoader;
 * };
 * @endcode
 *
 * @tparam ResourceType The type of a resource for which we are registering a loader.
 */
template<typename ResourceType>
struct ResourceLoaderFor
{
	// `static_assert` must be dependent on a template parameter to work correctly.
	static_assert(! std::is_same_v<ResourceType, ResourceType>, "You must specialize `ResourceLoaderFor` instead of using primary template.");

	/** @brief Type of loader for given resource. Must be defined in specializations! */
	using Type = void;
};

} // namespace rh

#endif // ROUNDHELL_RESOURCE_LOADER_FOR_HPP

