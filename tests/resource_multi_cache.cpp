#include <catch2/catch_test_macros.hpp>

#include <memory>
#include <optional>

#include <entt/core/hashed_string.hpp>
using namespace entt::literals;

#include "errors.hpp"
#include "resource_multi_cache.hpp"

// Sample resource type and loader
struct Foo { int index; };
struct FooLoader
{
	// How many times loader was called.
	inline static int _loader_count = 0;

	// Error used in loader call.
	inline static rh::Error _error {"Foo resource loader error"};

	using result_type = std::shared_ptr<Foo>;
	auto operator()(std::optional<rh::Error>& error, int index) -> result_type
	{
		_loader_count += 1;

		if (index >= 0) {
			return std::shared_ptr<Foo>(new Foo(index));
		}
		else {
			error = _error;
			return nullptr;
		}
	}
};
template<> struct rh::ResourceLoaderFor<Foo> { using Type = FooLoader; };

TEST_CASE("Getting / loading resources", "[resource_multi_cache]")
{
	auto resource_multi_cache = rh::ResourceMultiCache{};

	SECTION("Load successfully")
	{
		auto ex = resource_multi_cache.load<Foo>("1"_hs, 1);
		REQUIRE(ex);

		auto res = resource_multi_cache.get<Foo>("1"_hs);
		REQUIRE(res);
	}

	SECTION("Load unsuccessfully")
	{
		auto ex = resource_multi_cache.load<Foo>("-1"_hs, -1);
		REQUIRE_FALSE(ex);
		REQUIRE(ex.error() == FooLoader::_error);

		auto res = resource_multi_cache.get<Foo>("-1"_hs);
		REQUIRE_FALSE(res);
	}

	SECTION("Not loaded")
	{
		auto res = resource_multi_cache.get<Foo>("-"_hs);
		REQUIRE_FALSE(res);
	}

	SECTION("Force load")
	{
		FooLoader::_loader_count = 0;

		auto ex = resource_multi_cache.load<Foo>("1"_hs, 1);
		REQUIRE(ex);
		REQUIRE(FooLoader::_loader_count == 1);

		(void) resource_multi_cache.get<Foo>("1"_hs);
		REQUIRE(FooLoader::_loader_count == 1);

		ex = resource_multi_cache.load<Foo>("1"_hs, 1);
		REQUIRE(ex);
		REQUIRE(FooLoader::_loader_count == 1);

		ex = resource_multi_cache.force_load<Foo>("1"_hs, 1);
		REQUIRE(ex);
		REQUIRE(FooLoader::_loader_count == 2);
	}
}

