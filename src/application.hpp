#ifndef ROUNDHELL_APPLICATION_HPP
#define ROUNDHELL_APPLICATION_HPP

#include <cstddef>
#include <cstdio> // stderr
#include <string_view>
#include <vector>

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>

#include <entt/core/hashed_string.hpp>
#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "data/resources_data.hpp"
#include "errors.hpp"
#include "resource_multi_cache.hpp"

#include "systems/fps_limiter.hpp"
#include "systems/frame_counter.hpp"
#include "systems/animation.hpp"
#include "systems/movement.hpp"
#include "systems/random_movement.hpp"
#include "systems/sorter.hpp"
#include "systems/sprite_renderer.hpp"
#include "systems/world_transform_updater.hpp"

namespace rh {

class Application
{
	std::vector<std::string_view> _app_args;

	SDL_Point _window_size;
	SDL_InitFlags _init_flags;
	SDL_WindowFlags _window_flags;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	entt::registry _registry;
	entt::entity _root;

	ResourceMultiCache _resource_multi_cache;

	S::FpsLimiter _fps_limiter;
	S::FrameCounter _frame_counter;
	S::WorldTransformUpdater _world_transform_updater;
	S::SpriteRenderer _sprite_renderer;
	S::Animation _animation;
	S::Movement _movement;
	S::RandomMovement _random_movement;
	S::Sorter _sorter;

	auto _print_welcome() -> void;
	auto _print_goodbye() -> void;

	auto _prepare_resources() noexcept -> Expected<void>;
	auto _cleanup_resources() noexcept -> void;

	// return true if engine is still running, false if we are exiting right now
	[[nodiscard]] auto _handle_input() const noexcept -> bool;

	auto _handle_app_args() noexcept -> void;

	auto _mockup() -> void;
	auto _mockup_swarm() -> void;

	// Spawn game object
	auto _spawn(entt::entity parent, entt::hashed_string::hash_type prototype_id, SDL_FPoint position) noexcept -> entt::entity;

	// TODO These two are common for (almost) all renderers, but currently there is no right place
	//      for them. Maybe later move to some renderer base class (if we decide to make one)?
	auto _pre_render() noexcept -> Expected<void>;
	auto _post_render() noexcept -> Expected<void>;

	auto _loop(Uint64 time_per_update, std::size_t max_updates) noexcept -> Expected<int>;

public:
	explicit Application(int argc, char *argv[]);
	Application(std::vector<std::string_view> args = {});
	~Application();

	[[nodiscard]] auto run() noexcept -> Expected<int>;
};

} // namespace rh

#endif // ROUNDHELL_APPLICATION_HPP

