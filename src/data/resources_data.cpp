#include "data/resources_data.hpp"

#include <tuple>
#include <utility>

#include "subtexture.hpp"
#include "loaders/subtexture_loader.hpp"

#include "components/animation.hpp"
#include "components/sprite.hpp"

namespace rh {

namespace {

// Helper for making type-value pairs (type and its instance).
template<typename T, typename... Args>
auto mk_tv(Args&&... args) -> std::pair<std::type_index, AnyComponent>
{
	return {
		typeid(T),
		make_any_component<T>(
			std::forward<Args>(args)...
		)
	};
}

} // namespace

auto prepare_prototypes(ResourceMultiCache& res_cache) noexcept -> void
{
	// Helpers:

	auto sub = [&res_cache](auto id) -> Subtexture
	{
		return *(res_cache.get<Subtexture, SubtextureLoader>(id).handle().get());
	};

	auto ani = [](auto id)
	{
		// TODO Handle `std::out_of_range` that may be thrown from `at()` call below.
		const auto animation_data = ANIMATIONS.at(id);
		return std::make_from_tuple<C::Animation>(animation_data);
	};

	// Generate prototypes data:

	PROTOTYPES = {

		{ "rock-1"_hs,          { mk_tv<C::Sprite>(sub("rock-1"_hs)) } },
		{ "rock-2"_hs,          { mk_tv<C::Sprite>(sub("rock-2"_hs)) } },
		{ "rock-3"_hs,          { mk_tv<C::Sprite>(sub("rock-3"_hs)) } },

		{ "bullet-64x64"_hs,    { mk_tv<C::Sprite>(sub("bullet-64x64"_hs)) } },
		{ "bullet-48x48"_hs,    { mk_tv<C::Sprite>(sub("bullet-48x48"_hs)) } },
		{ "bullet-32x32"_hs,    { mk_tv<C::Sprite>(sub("bullet-32x32"_hs)) } },
		{ "bullet-24x24"_hs,    { mk_tv<C::Sprite>(sub("bullet-24x24"_hs)) } },
		{ "bullet-16x16"_hs,    { mk_tv<C::Sprite>(sub("bullet-16x16"_hs)) } },
		{ "bullet-12x12"_hs,    { mk_tv<C::Sprite>(sub("bullet-12x12"_hs)) } },
		{ "bullet-8x8"_hs,      { mk_tv<C::Sprite>(sub("bullet-8x8"_hs)) } },

		{ "crosshair-64x64"_hs, { mk_tv<C::Sprite>(sub("crosshair-64x64"_hs)) } },
		{ "crosshair-48x48"_hs, { mk_tv<C::Sprite>(sub("crosshair-48x48"_hs)) } },
		{ "crosshair-32x32"_hs, { mk_tv<C::Sprite>(sub("crosshair-32x32"_hs)) } },
		{ "crosshair-24x24"_hs, { mk_tv<C::Sprite>(sub("crosshair-24x24"_hs)) } },
		{ "crosshair-16x16"_hs, { mk_tv<C::Sprite>(sub("crosshair-16x16"_hs)) } },

		{ "muzzle-64x64"_hs,    { mk_tv<C::Sprite>(sub("muzzle-64x64"_hs)) } },
		{ "muzzle-48x48"_hs,    { mk_tv<C::Sprite>(sub("muzzle-48x48"_hs)) } },
		{ "muzzle-32x32"_hs,    { mk_tv<C::Sprite>(sub("muzzle-32x32"_hs)) } },
		{ "muzzle-24x24"_hs,    { mk_tv<C::Sprite>(sub("muzzle-24x24"_hs)) } },
		{ "muzzle-16x16"_hs,    { mk_tv<C::Sprite>(sub("muzzle-16x16"_hs)) } },
		{ "muzzle-12x12"_hs,    { mk_tv<C::Sprite>(sub("muzzle-12x12"_hs)) } },
		{ "muzzle-8x8"_hs,      { mk_tv<C::Sprite>(sub("muzzle-8x8"_hs)) } },

		{ "char-1"_hs,          { mk_tv<C::Sprite>(sub("char-1"_hs)),        mk_tv<C::Animation>(ani("char-idle"_hs)) } },
		{ "char-1-nh"_hs,       { mk_tv<C::Sprite>(sub("char-1-nh"_hs)),     mk_tv<C::Animation>(ani("char-idle"_hs)) } },
		{ "char-2"_hs,          { mk_tv<C::Sprite>(sub("char-2"_hs)),        mk_tv<C::Animation>(ani("char-idle"_hs)) } },
		{ "char-2-nh"_hs,       { mk_tv<C::Sprite>(sub("char-2-nh"_hs)),     mk_tv<C::Animation>(ani("char-idle"_hs)) } },
		{ "char-3"_hs,          { mk_tv<C::Sprite>(sub("char-3"_hs)),        mk_tv<C::Animation>(ani("char-idle"_hs)) } },
		{ "char-3-nh"_hs,       { mk_tv<C::Sprite>(sub("char-3-nh"_hs)),     mk_tv<C::Animation>(ani("char-idle"_hs)) } },
		{ "char-4"_hs,          { mk_tv<C::Sprite>(sub("char-4"_hs)),        mk_tv<C::Animation>(ani("char-idle"_hs)) } },
		{ "char-4-nh"_hs,       { mk_tv<C::Sprite>(sub("char-4-nh"_hs)),     mk_tv<C::Animation>(ani("char-idle"_hs)) } },

		{ "enemy-1"_hs,         { mk_tv<C::Sprite>(sub("enemy-1"_hs)),       mk_tv<C::Animation>(ani("enemy-idle"_hs)) } },
		{ "enemy-2"_hs,         { mk_tv<C::Sprite>(sub("enemy-2"_hs)),       mk_tv<C::Animation>(ani("enemy-idle"_hs)) } },
		{ "enemy-3"_hs,         { mk_tv<C::Sprite>(sub("enemy-3"_hs)),       mk_tv<C::Animation>(ani("enemy-fly"_hs)) } },
		{ "enemy-4"_hs,         { mk_tv<C::Sprite>(sub("enemy-4"_hs)),       mk_tv<C::Animation>(ani("enemy-idle"_hs)) } },

		{ "generic-death"_hs,   { mk_tv<C::Sprite>(sub("generic-death"_hs)), mk_tv<C::Animation>(ani("generic-death"_hs)) } },

		{ "weapon-1"_hs,        { mk_tv<C::Sprite>(sub("weapon-1"_hs)) } },
		{ "weapon-2"_hs,        { mk_tv<C::Sprite>(sub("weapon-2"_hs)) } },
		{ "weapon-3"_hs,        { mk_tv<C::Sprite>(sub("weapon-3"_hs)) } },

	};
};

} // namespace rh

