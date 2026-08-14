#ifndef ROUNDHELL_DATA_RESOURCES_DATA_HPP
#define ROUNDHELL_DATA_RESOURCES_DATA_HPP

#include <string_view>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>
using namespace std::string_view_literals;

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_rect.h>

#include <entt/core/hashed_string.hpp>
using namespace entt::literals;

#include "any_component.hpp"
#include "resource_multi_cache.hpp"
#include "utils.hpp"

namespace rh {

// ANIMATION_SPEED_* is in [ms], so bigger ANIMATION_SPEED_*_FACTOR is bigger time between frames
// and slower animation.
inline constexpr Uint64 ANIMATION_SPEED_NORMAL = 140;
inline constexpr float ANIMATION_SPEED_FAST_FACTOR = 0.7142f;
inline constexpr float ANIMATION_SPEED_SLOW_FACTOR = 1.3571f;
inline constexpr Uint64 ANIMATION_SPEED_FAST = uround<Uint64>(ANIMATION_SPEED_NORMAL * ANIMATION_SPEED_FAST_FACTOR);
inline constexpr Uint64 ANIMATION_SPEED_SLOW = uround<Uint64>(ANIMATION_SPEED_NORMAL * ANIMATION_SPEED_SLOW_FACTOR);

// MOVEMENT_SPEED_* is in [px/s]
inline constexpr float MOVEMENT_SPEED_NORMAL = 20.0f;
inline constexpr float MOVEMENT_SPEED_FAST_FACTOR = 1.80f;
inline constexpr float MOVEMENT_SPEED_SLOW_FACTOR = 0.65f;
inline constexpr float MOVEMENT_SPEED_FAST = MOVEMENT_SPEED_NORMAL * MOVEMENT_SPEED_FAST_FACTOR;
inline constexpr float MOVEMENT_SPEED_SLOW = MOVEMENT_SPEED_NORMAL * MOVEMENT_SPEED_SLOW_FACTOR;

inline const auto TEXTURES = std::vector<std::string_view>
{
	// From assets/list.txt (paths relative to `assets/` directory).
	// Path is used as id.

	"characters/char_1_nh.png"sv,
	"characters/char_1.png"sv,
	"characters/char_2_nh.png"sv,
	"characters/char_2.png"sv,
	"characters/char_3_nh.png"sv,
	"characters/char_3.png"sv,
	"characters/char_4_nh.png"sv,
	"characters/char_4.png"sv,
	"enemies/enemy_1.png"sv,
	"enemies/enemy_2.png"sv,
	"enemies/enemy_3.png"sv,
	"enemies/enemy_4.png"sv,
	"environment/rocks.png"sv,
	"extras/bullet.png"sv,
	"extras/crosshair.png"sv,
	"extras/generic_death.png"sv,
	"extras/muzzle.png"sv,
	"splash.png"sv,
	"weapons/weapons.png"sv,

};

inline const auto SUBTEXTURES = std::unordered_map<
	entt::hashed_string::hash_type,
	std::tuple<std::string_view, SDL_Rect>
>
{
	// Format: sub texture id - sdl texture path (id), texture rect
	// For animated things - rect is rect of first frame.

	{ "char-1"_hs,          { "characters/char_1.png"sv,    {     0, 3*164, 164, 164 } } },
	{ "char-1-nh"_hs,       { "characters/char_1_nh.png"sv, {     0, 3*164, 164, 164 } } },
	{ "char-2"_hs,          { "characters/char_2.png"sv,    {     0, 3*164, 164, 164 } } },
	{ "char-2-nh"_hs,       { "characters/char_2_nh.png"sv, {     0, 3*164, 164, 164 } } },
	{ "char-3"_hs,          { "characters/char_3.png"sv,    {     0, 3*164, 164, 164 } } },
	{ "char-3-nh"_hs,       { "characters/char_3_nh.png"sv, {     0, 3*164, 164, 164 } } },
	{ "char-4"_hs,          { "characters/char_4.png"sv,    {     0, 3*164, 164, 164 } } },
	{ "char-4-nh"_hs,       { "characters/char_4_nh.png"sv, {     0, 3*164, 164, 164 } } },

	{ "enemy-1"_hs,         { "enemies/enemy_1.png"sv,      {     0, 3*164, 164, 164 } } },
	{ "enemy-2"_hs,         { "enemies/enemy_2.png"sv,      {     0, 3*164, 164, 164 } } },
	{ "enemy-3"_hs,         { "enemies/enemy_3.png"sv,      {     0, 0*164, 164, 164 } } },
	{ "enemy-4"_hs,         { "enemies/enemy_4.png"sv,      {     0, 3*164, 164, 164 } } },

	{ "rock-1"_hs,          { "environment/rocks.png"sv,    { 0*164,     0, 164, 164 } } },
	{ "rock-2"_hs,          { "environment/rocks.png"sv,    { 1*164,     0, 164, 164 } } },
	{ "rock-3"_hs,          { "environment/rocks.png"sv,    { 2*164,     0, 164, 164 } } },

	{ "bullet-64x64"_hs,    { "extras/bullet.png"sv,        {     0,     0,  64,  64 } } },
	{ "bullet-48x48"_hs,    { "extras/bullet.png"sv,        {    64,     0,  48,  48 } } },
	{ "bullet-32x32"_hs,    { "extras/bullet.png"sv,        {   112,     0,  32,  32 } } },
	{ "bullet-24x24"_hs,    { "extras/bullet.png"sv,        {   112,    32,  24,  24 } } },
	{ "bullet-16x16"_hs,    { "extras/bullet.png"sv,        {    64,    48,  16,  16 } } },
	{ "bullet-12x12"_hs,    { "extras/bullet.png"sv,        {    80,    48,  12,  12 } } },
	{ "bullet-8x8"_hs,      { "extras/bullet.png"sv,        {    92,    48,   8,   8 } } },

	{ "crosshair-64x64"_hs, { "extras/crosshair.png"sv,     {     0,     0,  64,  64 } } },
	{ "crosshair-48x48"_hs, { "extras/crosshair.png"sv,     {    64,     0,  48,  48 } } },
	{ "crosshair-32x32"_hs, { "extras/crosshair.png"sv,     {   112,     0,  32,  32 } } },
	{ "crosshair-24x24"_hs, { "extras/crosshair.png"sv,     {   112,    32,  24,  24 } } },
	{ "crosshair-16x16"_hs, { "extras/crosshair.png"sv,     {    64,    48,  16,  16 } } },

	{ "generic-death"_hs,   { "extras/generic_death.png"sv, {     0, 0*164, 164, 164 } } },

	{ "muzzle-64x64"_hs,    { "extras/muzzle.png"sv,        {     0,     0,  64,  64 } } },
	{ "muzzle-48x48"_hs,    { "extras/muzzle.png"sv,        {    64,     0,  48,  48 } } },
	{ "muzzle-32x32"_hs,    { "extras/muzzle.png"sv,        {   112,     0,  32,  32 } } },
	{ "muzzle-24x24"_hs,    { "extras/muzzle.png"sv,        {   112,    32,  24,  24 } } },
	{ "muzzle-16x16"_hs,    { "extras/muzzle.png"sv,        {    64,    48,  16,  16 } } },
	{ "muzzle-12x12"_hs,    { "extras/muzzle.png"sv,        {    80,    48,  12,  12 } } },
	{ "muzzle-8x8"_hs,      { "extras/muzzle.png"sv,        {    92,    48,   8,   8 } } },

	{ "weapon-1"_hs,        { "weapons/weapons.png"sv,      { 0*164,     0, 164, 164 } } },
	{ "weapon-2"_hs,        { "weapons/weapons.png"sv,      { 1*164,     0, 164, 164 } } },
	{ "weapon-3"_hs,        { "weapons/weapons.png"sv,      { 2*164,     0, 164, 164 } } },

	{ "splash"_hs,          { "splash.png"sv,               {     0,     0, 900, 530 } } },

};

inline const auto ANIMATIONS = std::unordered_map<
	entt::hashed_string::hash_type,
	std::tuple<Uint16, Uint64, bool, bool> // data needed for construction of C::Animation
>
{
	// Format: animation id - frame_count, frame_duration, is_looped, direction_horizontal

	// All chars, hands and no-hands
	{ "char-death"_hs,         { 10, ANIMATION_SPEED_NORMAL, true, true } },
	{ "char-fall"_hs,          {  5, ANIMATION_SPEED_NORMAL, true, true } },
	{ "char-hit"_hs,           {  3, ANIMATION_SPEED_NORMAL, true, true } },
	{ "char-idle"_hs,          {  6, ANIMATION_SPEED_NORMAL, true, true } },
	{ "char-jump-end"_hs,      {  3, ANIMATION_SPEED_NORMAL, true, true } },
	{ "char-jump-start"_hs,    {  2, ANIMATION_SPEED_NORMAL, true, true } },
	{ "char-roll"_hs,          {  5, ANIMATION_SPEED_NORMAL, true, true } },
	{ "char-walk"_hs,          {  8, ANIMATION_SPEED_NORMAL, true, true } },

	// Enemy: 1, 2, 4
	// (in fact identical to char animations)
	{ "enemy-death"_hs,        { 10, ANIMATION_SPEED_NORMAL, true, true } },
	{ "enemy-fall"_hs,         {  5, ANIMATION_SPEED_NORMAL, true, true } },
	{ "enemy-hit"_hs,          {  3, ANIMATION_SPEED_NORMAL, true, true } },
	{ "enemy-idle"_hs,         {  6, ANIMATION_SPEED_NORMAL, true, true } },
	{ "enemy-jump-end"_hs,     {  3, ANIMATION_SPEED_NORMAL, true, true } },
	{ "enemy-jump-start"_hs,   {  2, ANIMATION_SPEED_NORMAL, true, true } },
	{ "enemy-roll"_hs,         {  5, ANIMATION_SPEED_NORMAL, true, true } },
	{ "enemy-walk"_hs,         {  8, ANIMATION_SPEED_NORMAL, true, true } },

	// Enemy: 3
	{ "enemy-fly"_hs,          {  6, ANIMATION_SPEED_NORMAL, true, true } },

	{ "generic-death"_hs,      {  3, ANIMATION_SPEED_NORMAL, true, true } },

};

// `PROTOTYPES` is mapping of Prototype ID to bag of its components (these will be copied on spawn).
inline auto PROTOTYPES = std::unordered_map<
	entt::hashed_string::hash_type,
	std::unordered_map<std::type_index, AnyComponent>
>
{};

// Generate `PROTOTYPES` data from `SUBTEXTURES` and `ANIMATIONS`.
auto prepare_prototypes(ResourceMultiCache& res_cache) noexcept -> void;

} // namespace rh

#endif // ROUNDHELL_DATA_RESOURCES_DATA_HPP

