#ifndef ROUNDHELL_SYSTEMS_HPP
#define ROUNDHELL_SYSTEMS_HPP

#include "systems/fps_limiter.hpp"
#include "systems/frame_counter.hpp"
#include "systems/animation.hpp"
#include "systems/movement.hpp"
#include "systems/random_movement.hpp"
#include "systems/sorter.hpp"
#include "systems/sprite_renderer.hpp"
#include "systems/world_transform_updater.hpp"

namespace rh {

struct Systems
{
	S::FpsLimiter            fps_limiter             {0};
	S::FrameCounter          frame_counter           {};
	S::WorldTransformUpdater world_transform_updater {};
	S::SpriteRenderer        sprite_renderer         {};
	S::Animation             animation               {};
	S::Movement              movement                {};
	S::RandomMovement        random_movement;
	S::Sorter                sorter                  {};
};

} // namespace rh

#endif // ROUNDHELL_SYSTEMS_HPP

