#include <SDL3/SDL_main.h>

#include <cstdio> // stderr
#include <print>
#include <stdexcept>

#include "application.hpp"
#include "errors.hpp"

auto main(int argc, char *argv[]) -> int
{
	try {
		auto app = rh::Application(argc, argv);

		if (auto r = app.run()) {
			return *r;
		}
		else {
			std::println(stderr, "error: {}", r.error().to_string());
			return 1;
		}
	}
	catch (std::exception& e) {
		std::println(stderr, "error: {}", e.what());
		return 1;
	}
}

