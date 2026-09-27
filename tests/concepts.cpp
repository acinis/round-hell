#include <catch2/catch_test_macros.hpp>

#include <memory>

#include <entt/resource/resource.hpp>

#include "concepts.hpp"

TEST_CASE("PointerLike concepts", "[concepts]")
{
	SECTION("Standard types")
	{
		REQUIRE(rh::PointerLike<int*>);
		REQUIRE_FALSE(rh::PointerLike<float>);

		REQUIRE(rh::ConcretePointerLike<int*, int>);
		REQUIRE_FALSE(rh::ConcretePointerLike<int*, float>);

		REQUIRE(rh::PointerLike<std::shared_ptr<int>>);
		REQUIRE(rh::ConcretePointerLike<std::shared_ptr<int>, int>);
		REQUIRE_FALSE(rh::ConcretePointerLike<std::shared_ptr<int>, float>);

		REQUIRE_FALSE(rh::ConcretePointerLike<int*, std::shared_ptr<int>>);
		REQUIRE_FALSE(rh::ConcretePointerLike<std::shared_ptr<int>, int*>);
	}

	SECTION("Constant types and constant pointers")
	{
		REQUIRE(rh::PointerLike<const int *>);
		REQUIRE(rh::ConcretePointerLike<const int *, const int>);
		REQUIRE_FALSE(rh::ConcretePointerLike<const int *, int>);

		REQUIRE(rh::PointerLike<int *const>);
		REQUIRE(rh::ConcretePointerLike<int *const, int>);
		REQUIRE_FALSE(rh::ConcretePointerLike<int *const, const int>);

		REQUIRE(rh::PointerLike<const int *const>);
		REQUIRE(rh::ConcretePointerLike<const int *const, const int>);
		REQUIRE_FALSE(rh::ConcretePointerLike<const int *const, int>);
	}

	SECTION("EnTT types")
	{
		REQUIRE(rh::PointerLike<entt::resource<int>>);
		REQUIRE(rh::ConcretePointerLike<entt::resource<int>, int>);
	}
}

