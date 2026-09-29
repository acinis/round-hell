#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinAbs;

#include <memory>

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <entt/resource/resource.hpp>

#include "errors.hpp"
#include "subtexture.hpp"

TEST_CASE("BasicSubtexture", "[basic_subtexture]")
{
	int w {10};
	int h {10};
	SDL_PixelFormat format {SDL_PIXELFORMAT_RGB24};

	auto surface = std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>{
		SDL_CreateSurface(w, h, format),
		SDL_DestroySurface
	};
	if (! surface) {
		FAIL("Error creating a SDL_Surface: " << SDL_GetError());
	}

	auto renderer = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>{
		SDL_CreateSoftwareRenderer(surface.get()),
		SDL_DestroyRenderer
	};
	if (! renderer) {
		FAIL("Error creating a software SDL_Renderer: " << SDL_GetError());
	}

	auto texture = entt::resource<SDL_Texture>{
		std::shared_ptr<SDL_Texture>(
			SDL_CreateTexture(renderer.get(), format, SDL_TEXTUREACCESS_STATIC, w, h),
			&SDL_DestroyTexture
		)
	};
	if (! texture) {
		FAIL("Error creating a SDL_Texture: " << SDL_GetError());
	}

	SECTION("BasicSubtexture(TextureHandleType, float, float, float, float) constructor")
	{
		auto rect = SDL_FRect{5.0f, 6.0f, 7.0f, 8.0f};
		auto subtexture = rh::BasicSubtexture<entt::resource<SDL_Texture>>{texture, rect.x, rect.y, rect.w, rect.h};
		REQUIRE(subtexture.raw() == texture.handle().get());
		REQUIRE_THAT(subtexture.x(), WithinAbs(rect.x, 0.01f));
		REQUIRE_THAT(subtexture.y(), WithinAbs(rect.y, 0.01f));
		REQUIRE_THAT(subtexture.w(), WithinAbs(rect.w, 0.01f));
		REQUIRE_THAT(subtexture.h(), WithinAbs(rect.h, 0.01f));
	}

	SECTION("BasicSubtexture(TextureHandleType, SDL_FPoint, SDL_FPoint) constructor")
	{
		auto offset = SDL_FPoint{5.0f, 6.0f};
		auto size = SDL_FPoint{7.0f, 8.0f};
		auto subtexture = rh::BasicSubtexture<entt::resource<SDL_Texture>>{texture, offset, size};
		REQUIRE(subtexture.raw() == texture.handle().get());
		REQUIRE_THAT(subtexture.x(), WithinAbs(offset.x, 0.01f));
		REQUIRE_THAT(subtexture.y(), WithinAbs(offset.y, 0.01f));
		REQUIRE_THAT(subtexture.w(), WithinAbs(size.x, 0.01f));
		REQUIRE_THAT(subtexture.h(), WithinAbs(size.y, 0.01f));
	}

	SECTION("BasicSubtexture(TextureHandleType, SDL_FRect) constructor")
	{
		auto rect = SDL_FRect{5.0f, 6.0f, 7.0f, 8.0f};
		auto subtexture = rh::BasicSubtexture<entt::resource<SDL_Texture>>{texture, rect};
		REQUIRE(subtexture.raw() == texture.handle().get());
		REQUIRE_THAT(subtexture.x(), WithinAbs(rect.x, 0.01f));
		REQUIRE_THAT(subtexture.y(), WithinAbs(rect.y, 0.01f));
		REQUIRE_THAT(subtexture.w(), WithinAbs(rect.w, 0.01f));
		REQUIRE_THAT(subtexture.h(), WithinAbs(rect.h, 0.01f));
	}

	SECTION("BasicSubtexture(TextureHandleType, ) constructor")
	{
		try {
			auto subtexture = rh::BasicSubtexture<entt::resource<SDL_Texture>>{texture};
			REQUIRE(subtexture.raw() == texture.handle().get());
			REQUIRE_THAT(subtexture.x(), WithinAbs(0.0f, 0.01f));
			REQUIRE_THAT(subtexture.y(), WithinAbs(0.0f, 0.01f));
			REQUIRE_THAT(subtexture.w(), WithinAbs(w * 1.0f, 0.01f));
			REQUIRE_THAT(subtexture.h(), WithinAbs(h * 1.0f, 0.01f));
		}
		catch(std::runtime_error& e) {
			FAIL("Valid texture failed with std::runtime_error: " << e.what());
		}
	}

	SECTION("BasicSubtexture(TextureHandleType, ) constructor - exception check")
	{
		#ifdef NDEBUG
			try {
				auto subtexture = rh::BasicSubtexture<entt::resource<SDL_Texture>>{entt::resource<SDL_Texture>{nullptr}};
			}
			catch(std::runtime_error& e) {
				SUCCEED("Exception thrown on failure");
			}
		#else
			SKIP("This test cannot be performed in DEBUG build.");
		#endif
	}

	SECTION("BasicSubtexture(entt::resource<SDL_Texture>, float, float) constructor")
	{
		auto size = SDL_FPoint{9.0f, 9.0f};
		auto subtexture = rh::BasicSubtexture<entt::resource<SDL_Texture>>{texture, size.x, size.y};
		REQUIRE(subtexture.raw() == texture.handle().get());
		REQUIRE_THAT(subtexture.x(), WithinAbs(0.0f, 0.01f));
		REQUIRE_THAT(subtexture.y(), WithinAbs(0.0f, 0.01f));
		REQUIRE_THAT(subtexture.w(), WithinAbs(size.x, 0.01f));
		REQUIRE_THAT(subtexture.h(), WithinAbs(size.y, 0.01f));
	}

	SECTION("BasicSubtexture(entt::resource<SDL_Texture>, SDL_FPoint) constructor")
	{
		auto size = SDL_FPoint{9.0f, 9.0f};
		auto subtexture = rh::BasicSubtexture<entt::resource<SDL_Texture>>{texture, size};
		REQUIRE(subtexture.raw() == texture.handle().get());
		REQUIRE_THAT(subtexture.x(), WithinAbs(0.0f, 0.01f));
		REQUIRE_THAT(subtexture.y(), WithinAbs(0.0f, 0.01f));
		REQUIRE_THAT(subtexture.w(), WithinAbs(size.x, 0.01f));
		REQUIRE_THAT(subtexture.h(), WithinAbs(size.y, 0.01f));
	}

	SECTION("BasicSubtexture copy constructor")
	{
		rh::BasicSubtexture<entt::resource<SDL_Texture>> subtexture_1 {texture};
		rh::BasicSubtexture<entt::resource<SDL_Texture>> subtexture_2 {subtexture_1};
		REQUIRE(subtexture_1.raw() == texture.handle().get());
		REQUIRE(subtexture_2.raw() == texture.handle().get());
		REQUIRE_THAT(subtexture_1.x(), WithinAbs(subtexture_2.x(), 0.01f));
		REQUIRE_THAT(subtexture_1.y(), WithinAbs(subtexture_2.y(), 0.01f));
		REQUIRE_THAT(subtexture_1.w(), WithinAbs(subtexture_2.w(), 0.01f));
		REQUIRE_THAT(subtexture_1.h(), WithinAbs(subtexture_2.h(), 0.01f));
	}

	SECTION("BasicSubtexture move constructor")
	{
		auto rect = SDL_FRect{5.0f, 6.0f, 7.0f, 8.0f};
		auto tmp = rh::BasicSubtexture<entt::resource<SDL_Texture>>{texture, rect};
		rh::BasicSubtexture<entt::resource<SDL_Texture>> subtexture {std::move(tmp)};
		REQUIRE(subtexture.raw() == texture.handle().get());
		REQUIRE_THAT(subtexture.x(), WithinAbs(rect.x, 0.01f));
		REQUIRE_THAT(subtexture.y(), WithinAbs(rect.y, 0.01f));
		REQUIRE_THAT(subtexture.w(), WithinAbs(rect.w, 0.01f));
		REQUIRE_THAT(subtexture.h(), WithinAbs(rect.h, 0.01f));
	}

	SECTION("BasicSubtexture copy assignment operator")
	{
		rh::BasicSubtexture<entt::resource<SDL_Texture>> subtexture_1 {texture};
		rh::BasicSubtexture<entt::resource<SDL_Texture>> subtexture_2 = subtexture_1;
		REQUIRE(subtexture_1.raw() == texture.handle().get());
		REQUIRE(subtexture_2.raw() == texture.handle().get());
		REQUIRE_THAT(subtexture_1.x(), WithinAbs(subtexture_2.x(), 0.01f));
		REQUIRE_THAT(subtexture_1.y(), WithinAbs(subtexture_2.y(), 0.01f));
		REQUIRE_THAT(subtexture_1.w(), WithinAbs(subtexture_2.w(), 0.01f));
		REQUIRE_THAT(subtexture_1.h(), WithinAbs(subtexture_2.h(), 0.01f));
	}

	SECTION("BasicSubtexture move assignment operator")
	{
		auto rect = SDL_FRect{5.0f, 6.0f, 7.0f, 8.0f};
		auto tmp = rh::BasicSubtexture<entt::resource<SDL_Texture>>{texture, rect};
		rh::BasicSubtexture<entt::resource<SDL_Texture>> subtexture = std::move(tmp);
		REQUIRE(subtexture.raw() == texture.handle().get());
		REQUIRE_THAT(subtexture.x(), WithinAbs(rect.x, 0.01f));
		REQUIRE_THAT(subtexture.y(), WithinAbs(rect.y, 0.01f));
		REQUIRE_THAT(subtexture.w(), WithinAbs(rect.w, 0.01f));
		REQUIRE_THAT(subtexture.h(), WithinAbs(rect.h, 0.01f));
	}

	SECTION("BasicSubtexture::handle() accessor")
	{
		auto subtexture = rh::BasicSubtexture<entt::resource<SDL_Texture>>{texture};
		REQUIRE(subtexture.handle() == texture);
	}

	SECTION("BasicSubtexture::raw() accessor")
	{
		auto subtexture = rh::BasicSubtexture<entt::resource<SDL_Texture>>{texture};
		REQUIRE(subtexture.raw() == texture.handle().get());
	}

	SECTION("BasicSubtexture dimension accessors")
	{
		auto rect = SDL_FRect{51.0f, 52.0f, 53.0f, 54.0f};
		auto subtexture = rh::BasicSubtexture<entt::resource<SDL_Texture>>{texture, rect.x, rect.y, rect.w, rect.h};
		REQUIRE_THAT(subtexture.offset().x, WithinAbs(rect.x, 0.01f));
		REQUIRE_THAT(subtexture.offset().y, WithinAbs(rect.y, 0.01f));
		REQUIRE_THAT(subtexture.size().x, WithinAbs(rect.w, 0.01f));
		REQUIRE_THAT(subtexture.size().y, WithinAbs(rect.h, 0.01f));
		REQUIRE_THAT(subtexture.rect().x, WithinAbs(rect.x, 0.01f));
		REQUIRE_THAT(subtexture.rect().y, WithinAbs(rect.y, 0.01f));
		REQUIRE_THAT(subtexture.rect().w, WithinAbs(rect.w, 0.01f));
		REQUIRE_THAT(subtexture.rect().h, WithinAbs(rect.h, 0.01f));
		REQUIRE_THAT(subtexture.x(), WithinAbs(rect.x, 0.01f));
		REQUIRE_THAT(subtexture.y(), WithinAbs(rect.y, 0.01f));
		REQUIRE_THAT(subtexture.w(), WithinAbs(rect.w, 0.01f));
		REQUIRE_THAT(subtexture.h(), WithinAbs(rect.h, 0.01f));
	}
}

