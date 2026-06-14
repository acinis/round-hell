#include <catch2/catch_test_macros.hpp>

#include <chrono>
#include <thread>

#include "clock.hpp"

// TODO Maybe add flag for ignoring clock testing? Playing with time is probably bad idea...
TEST_CASE("Simple clock test", "[clock]")
{
	auto clock = rh::Clock{};

	std::this_thread::sleep_for(std::chrono::milliseconds{100});
	REQUIRE(clock.elapsed() >= 100);
	REQUIRE(clock.restart() >= 100);
	REQUIRE(clock.elapsed() < 100);

	// Check again (first time was after creation, now check after restart).
	std::this_thread::sleep_for(std::chrono::milliseconds{100});
	REQUIRE(clock.elapsed() >= 100);
}

