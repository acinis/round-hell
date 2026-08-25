#include "application.hpp"

#include <array>
#include <memory>
#include <print>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
using namespace std::string_view_literals;
using namespace std::string_literals;

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_pixels.h>

using namespace entt::literals;

// For getting version infos
#include <SDL3/SDL_version.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <entt/config/version.h>
#include <glm/detail/setup.hpp> // TODO This is in `detail` directory, so maybe include `glm/glm.hpp` instead?
#include "version.hpp"

#include "entity_builder.hpp"
#include "errors.hpp"
#include "utils.hpp"

#include "components/transform.hpp"
#include "components/movement.hpp"
#include "components/order.hpp"
#include "components/sprite.hpp"

#include "loaders/animation_data_loader.hpp"
#include "loaders/sdl_texture_loader.hpp"
#include "loaders/subtexture_loader.hpp"

namespace rh {

auto Application::_print_welcome() -> void
{
	std::println("Hello round world!");
	std::println();

	std::println("RoundHell v{} ({})", ROUNDHELL_VERSION, ROUNDHELL_COMMIT);
	std::println();

	std::println("Used libs:");
	std::println("* SDL3          {}", format_sdl_version(SDL_VERSION, SDL_GetVersion()));
	std::println("  * SDL3_image  {}", format_sdl_version(SDL_IMAGE_VERSION, IMG_Version()));
	std::println("  * SDL3_mixer  {}", format_sdl_version(SDL_MIXER_VERSION, MIX_Version()));
	std::println("  * SDL3_ttf    {}", format_sdl_version(SDL_TTF_VERSION, TTF_Version()));
	std::println("* EnTT          v{}", ENTT_VERSION);
	std::println("* GLM           v{}.{}.{}", GLM_VERSION_MAJOR, GLM_VERSION_MINOR, GLM_VERSION_PATCH);
}

auto Application::_print_goodbye() -> void
{
	std::println("» Time elapsed: {:.4f}s ({:.1f}m)",
		_frame_counter.total_time() / 1000.0f,
		_frame_counter.total_time() / 1000.0f / 60.0f
	);
	std::println("» Rendered {} frames", _frame_counter.frame_count());
	std::println("» At average there was {:.2f} frames per second", _frame_counter.average_frame_rate());
	std::println("» At average each frame took {:.2f} ms", _frame_counter.average_frame_time());
}

auto Application::_prepare_resources() noexcept -> Expected<void>
{
	auto r = Expected<void>{};

	auto base_path = "./assets/"s;

	// Textures:
	for (const auto& path : TEXTURES) {
		auto id = entt::hashed_string{path.data(), path.size()};
		auto full_path = base_path + std::string{path};
		r = _resource_multi_cache.load<SDL_Texture>(id, _renderer, full_path);
		if (! r) {
			return Unexpected{r.error()};
		}
	}

	// Subtextures:
	for (const auto& [id, data] : SUBTEXTURES) {
		const auto& [path, rect] = data;
		auto tex_id = entt::hashed_string{path.data(), path.size()};
		auto texture = _resource_multi_cache.get<SDL_Texture>(tex_id);
		r = _resource_multi_cache.load<Subtexture>(id, texture, rect);
		if (! r) {
			return Unexpected{r.error()};
		}
	}

	// Generated textures and subtextures
	{
		const auto bg_color = SDL_Color{109, 105, 135, 255};
		auto texture_id = "@GEN/bg-color"_hs;
		auto subtexture_id = "bg-color"_hs;

		r = _resource_multi_cache.load<SDL_Texture>(texture_id, _renderer, bg_color);
		if (! r) {
			return Unexpected{r.error()};
		}

		auto texture = _resource_multi_cache.get<SDL_Texture>(texture_id);
		r = _resource_multi_cache.load<Subtexture>(subtexture_id, texture);
		if (! r) {
			return Unexpected{r.error()};
		}
	}

	// Animations:
	for (const auto& [id, data] : ANIMATIONS) {
		r = _resource_multi_cache.load<AnimationData>(id, data);
		if (! r) {
			return Unexpected{r.error()};
		}
	}

	// Prototypes:
	prepare_prototypes(_resource_multi_cache);

	return {};
}

auto Application::_cleanup_resources() noexcept -> void
{
}

auto Application::_handle_input() const noexcept -> bool
{
	auto running = true;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			running = false;
		}
		else if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
			running = false;
		}
	}

	return running;
}

auto Application::_spawn(entt::entity parent, entt::hashed_string::hash_type prototype_id, SDL_FPoint position) noexcept -> entt::entity
{
	int order = static_cast<int>(position.y);

	auto maker = make_entity(_registry, parent)
		.emplace<C::Order>(order)
		.emplace<C::LocalTransform>(to_mat4(position.x, position.y))
		.emplace<C::WorldTransform>()
	;

	for (const auto& any_component : PROTOTYPES[prototype_id] | std::views::values) {
		maker.emplace(any_component);
	}

	return maker.get_entity();
};

Application::Application(int argc, char *argv[])
:
	Application(make_args(argc, argv))
{
}

auto Application::_handle_app_args() noexcept -> void
{
	auto check = [&args = std::as_const(this->_app_args)](std::string_view arg)
	{
		return args.end() != std::find(args.begin(), args.end(), arg);
	};

	if (check("--no-fps-limit"sv)) {
		_fps_limiter.limit(0);
	}
}

auto Application::_mockup() -> void
{
	_mockup_swarm();
}

auto Application::_mockup_swarm() -> void
{
	_root = make_entity(_registry)
		.emplace<C::Order>(C::Order::LOWEST)
		.emplace<C::LocalTransform>(to_mat4(0.0f, 0.0f))
		.emplace<C::WorldTransform>()
		.get_entity()
	;

	auto entity_bg = make_entity(_registry, _root)
		.emplace<C::Order>(C::Order::LOWEST + 100)
		.emplace<C::LocalTransform>(to_mat4(0.0f, 0.0f))
		.emplace<C::WorldTransform>()
		.emplace<C::Sprite>(*(_resource_multi_cache.get<Subtexture>("bg-color"_hs).handle().get()))
		.get_entity()
	;
	RH_UNUSED(entity_bg);

	auto ids = std::vector<entt::hashed_string::hash_type>{
		"char-1"_hs,
		"char-2"_hs,
		"char-3"_hs,
		"char-4"_hs,
		"enemy-1"_hs,
		"enemy-2"_hs,
		"enemy-3"_hs,
		"enemy-4"_hs,
	};

	auto speeds = std::array{
		MOVEMENT_SPEED_NORMAL,
		MOVEMENT_SPEED_FAST,
		MOVEMENT_SPEED_SLOW,
	};

	for (int i = 0; i < 100; i++) {
		auto entity = _spawn(
			_root,
			ids[i % ids.size()],
			{
				rand<float>(-60, _window_size.x - 105),
				rand<float>(-86, _window_size.y - 143)
			}
		);

		_registry.emplace<C::Movement>(entity, speeds[i % speeds.size()]);
	}
}

auto Application::_pre_render() noexcept -> Expected<void>
{
	auto neutral_color = SDL_Color{80, 80, 80, 255};

	if (! SDL_SetRenderDrawColor(_renderer, neutral_color.r, neutral_color.g, neutral_color.b, neutral_color.a)) {
		return Unexpected{make_sdl_error("SDL_SetRenderDrawColor")};
	}

	if (! SDL_RenderClear(_renderer)) {
		return Unexpected{make_sdl_error("SDL_RenderClear")};
	}

	return {};
}

auto Application::_post_render() noexcept -> Expected<void>
{
	// `SDL_RenderPresent()` call is needed, see:
	// https://discourse.libsdl.org/t/window-not-showing/57898/3
	if (! SDL_RenderPresent(_renderer)) {
		return Unexpected{make_sdl_error("SDL_RenderPresent")};
	}

	return {};
}

// Run main game loop (fixed step).
auto Application::_loop(Uint64 time_per_update, std::size_t max_updates) noexcept -> Expected<int>
{
	// Startup phase
	_frame_counter.reset();

	bool running = true;
	Clock game_clock; // ie. iteration clock
	Uint64 lag = 0;

	while (running) {

		const Uint64 elapsed = game_clock.restart();
		lag += elapsed;

		running = _handle_input();

		std::size_t update_count = 0;
		while (lag >= time_per_update) {

			// Update phase
			// Note: `time_per_update` is delta time.
			_world_transform_updater.run(_registry, _root);
			_sorter.run<C::Sprite>(_registry);
			_animation.run(time_per_update, _registry, _root);
			_movement.run(time_per_update, _registry, _root);
			_random_movement.run(time_per_update, _registry, _root);

			lag -= time_per_update;
			update_count += 1;

			// Reset `lag` if update cannot catch-up with wall clock (stop updating and skip time
			// accumulated in `lag` variable).
			if (update_count >= max_updates) {
				lag = 0;
				// lag %= time_per_update;
				// TODO Which one is better? We are skipping some updates, so there may be some
				//      glitches, etc. I think resetting accumulated lag to zero is ok, maybe even
				//      better.
			}
		}

		// Render phase
		// Note: `elapsed` is delta time.
		if (auto e = _pre_render(); !e) {
			return Unexpected{e.error()};
		}

		_sprite_renderer.run(elapsed, _renderer, _registry, _root);

		if (auto e = _post_render(); !e) {
			return Unexpected{e.error()};
		}

		_fps_limiter.run(game_clock.elapsed());

		_frame_counter.frame_done();
	}

	return 0;
}

Application::Application(std::vector<std::string_view> args)
:
	_app_args {args},
	_window_size {800, 600},
	_init_flags {SDL_INIT_VIDEO | SDL_INIT_EVENTS},
	_window_flags {SDL_WINDOW_OPENGL},
	_window {nullptr},
	_renderer {nullptr},
	_registry {},
	_root {entt::null},
	_resource_multi_cache {},
	_fps_limiter{60},
	_random_movement{0, 0, _window_size.x, _window_size.y}
{
	_handle_app_args();

	if (! SDL_Init(_init_flags)) {
		throw std::runtime_error{make_sdl_error("Cannot initialize SDL: ").to_string()};
	}

	_window = SDL_CreateWindow("round-hell", _window_size.x, _window_size.y, _window_flags);
	if (! _window) {
		throw std::runtime_error{make_sdl_error("Cannot create window: ").to_string()};
	}

	_renderer = SDL_CreateRenderer(_window, nullptr);
	if (! _renderer) {
		throw std::runtime_error{make_sdl_error("error: Cannot create renderer: ").to_string()};
	}

	if (auto r = _prepare_resources(); !r) {
		throw std::runtime_error{r.error().to_string()};
	}
}

Application::~Application()
{
	_cleanup_resources();

	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

auto Application::run() noexcept -> Expected<int>
{
	// Init phase
	_print_welcome();
	std::println();
	_mockup();

	if (entt::null == _root) {
		return rh::Unexpected{rh::Error{"Cannot run application with null root entity"sv}};
	}

	// fixed time of update step (can be many in row before frame rendering)
	const Uint64 time_per_update {16}; // [ms], ie. ~60Hz

	// max number of update steps, until loop bail out and skip steps to catch up
	const std::size_t max_updates {10}; // TODO URGENT Why 10?

	auto r = _loop(time_per_update, max_updates);
	if (!r) {
		// Early return on error - do not run shutdown phase.
		return r;
	}

	// Shutdown phase
	std::println();
	_print_goodbye();

	return *r;
}

} // namespace rh

