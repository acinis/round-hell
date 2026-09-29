#ifndef ROUNDHELL_SUBTEXTURE_HPP
#define ROUNDHELL_SUBTEXTURE_HPP

/**
 * @file src/subtexture.hpp
 * @brief Helper class for managing textures that are part of other texture (atlases, sheets, etc).
 */

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include <entt/resource/resource.hpp>

#include "concepts.hpp"

namespace rh {

/**
 * @brief
 * @tparam
 */
template<typename T>
concept SdlTexturePointerLike = ConcretePointerLike<T, SDL_Texture>;

/**
 * @brief Tight wrapper around `SDL_Texture` that has offset and size. Ideal for using with atlases.
 * @tparam
 */
template<SdlTexturePointerLike TextureHandleType>
class BasicSubtexture final
{
	TextureHandleType _texture {}; //!< whole texture (eg. altas or sprite sheet)

	float _x {0.0f}; //!< x offset (position in whole texture)
	float _y {0.0f}; //!< y offset (position in whole texture)
	float _w {0.0f}; //!< width of subtexture
	float _h {0.0f}; //!< height of subtexture

public:

	/** @brief Default initialization is not allowed. */
	BasicSubtexture() = delete;

	/**
	 * @brief Creates a new `BasicSubtexture` instance.
	 *
	 * @warning
	 * - `x`, `y`, `w`, `h` are not validated if they are in range of given texture size.
	 * - `texture` is checked against `nullptr` only in debug build via assertion.
	 * - `x` and `y` are checked against `w` and `h` only in debug build via assertion.
	 *
	 * @param texture `TextureHandleType` instance for underlying texture data.
	 * @param x Subtexture `x` offset inside whole texture.
	 * @param y Subtexture `y` offset inside whole texture.
	 * @param w Subtexture width.
	 * @param h Subtexture height.
	 */
	BasicSubtexture(TextureHandleType texture, float x, float y, float w, float h) noexcept;

	/**
	 * @brief Creates a new `BasicSubtexture` instance.
	 *
	 * @warning
	 * - `offset` and `size` are not validated if they are in range of given texture size.
	 * - `texture` is checked against `nullptr` only in debug build via assertion.
	 * - `x` and `y` are checked against `w` and `h` only in debug build via assertion.
	 *
	 * @param texture `TextureHandleType` instance for underlying texture data.
	 * @param offset Subtexture `x` and `y` offset inside whole texture.
	 * @param size Subtexture size (width is `size.x` and height is `size.y`).
	 */
	BasicSubtexture(TextureHandleType texture, SDL_FPoint offset, SDL_FPoint size) noexcept;

	/**
	 * @brief Creates a new `BasicSubtexture` instance.
	 *
	 * @warning
	 * - `rect` is not validated if it is in range of given texture size.
	 * - `texture` is checked against `nullptr` only in debug build via assertion.
	 * - `x` and `y` are checked against `w` and `h` only in debug build via assertion.
	 *
	 * @param texture `TextureHandleType` instance for underlying texture data.
	 * @param rect Subtexture rectangle (offset - `rect.x`, `rect.y` and size - `rect.w`, `rect.h`).
	 */
	BasicSubtexture(TextureHandleType texture, SDL_FRect rect) noexcept;

	/**
	 * @brief Creates a new `BasicSubtexture` instance with default offset (0.0f, 0.0f).
	 *
	 * This will query underlying texture for width and height, and can throw!
	 *
	 * @warning
	 * - `texture` is checked against `nullptr` only in debug build via assertion.
	 *
	 * @param texture `TextureHandleType` instance for underlying texture data.
	 *
	 * @throw rh::RuntimeException If there is an error getting texture size.
	 */
	BasicSubtexture(TextureHandleType texture);

	/**
	 * @brief Creates a new `BasicSubtexture` instance with default offset (0.0f, 0.0f).
	 *
	 * @warning
	 * - `w`, `h` are not validated if they are in range of given texture size.
	 * - `texture` is checked against `nullptr` only in debug build via assertion.
	 *
	 * @param texture `TextureHandleType` instance for underlying texture data.
	 * @param w Subtexture width.
	 * @param h Subtexture height.
	 */
	BasicSubtexture(TextureHandleType texture, float w, float h) noexcept;

	/**
	 * @brief Creates a new `BasicSubtexture` instance with default offset (0.0f, 0.0f).
	 *
	 * @warning
	 * - `size` is not validated if it is in range of given texture size.
	 * - `texture` is checked against `nullptr` only in debug build via assertion.
	 *
	 * @param texture `TextureHandleType` instance for underlying texture data.
	 * @param size Subtexture size (width is `size.x` and height is `size.y`).
	 * @return
	 */
	BasicSubtexture(TextureHandleType texture, SDL_FPoint size) noexcept;

	/**
	 * @brief Default copy constructor.
	 */
	BasicSubtexture(const BasicSubtexture&) noexcept = default;

	/**
	 * @brief Default move constructor.
	 */
	BasicSubtexture(BasicSubtexture&&) noexcept = default;

	/**
	 * @brief Default destructor.
	 */
	~BasicSubtexture() = default;

	/**
	 * @brief Default copy assignment operator.
	 * @return This `BasicSubtexture` instance.
	 */
	auto operator=(const BasicSubtexture&) noexcept -> BasicSubtexture& = default;

	/**
	 * @brief Default move assignment operator.
	 * @return This `BasicSubtexture` instance.
	 */
	auto operator=(BasicSubtexture&&) noexcept -> BasicSubtexture& = default;

	/**
	 * @brief Get handle to underlying resource.
	 *
	 * @return Underlying resource handle.
	 */
	auto handle() noexcept -> TextureHandleType;

	/**
	 * @brief Get raw pointer to underlying texture.
	 *
	 * @warning Changes to this data will be not reflected automatically in `BasicSubtexture` instance.
	 * @warning This gives access to *whole* texture, not only part used by `BasicSubtexture` instance.
	 *
	 * @return Pointer to underlying `SDL_Texture`.
	 */
	auto raw() noexcept -> SDL_Texture*;

	/**
	 * @brief Get offset of subtexture.
	 * @return Subtexture offset.
	 */
	auto offset() const noexcept -> SDL_FPoint;

	/**
	 * @brief Get size of subtexture.
	 * @return Subtexture size.
	 */
	auto size() const noexcept -> SDL_FPoint;

	/**
	 * @brief Get enclosing rectangle of subtexture.
	 * @return Subtexture rectangle.
	 */
	auto rect() const noexcept -> SDL_FRect;

	/**
	 * @brief Get x offset of subtexture.
	 * @return Subtexture x offset.
	 */
	auto x() const noexcept -> float;

	/**
	 * @brief Get y offset of subtexture.
	 * @return Subtexture y offset.
	 */
	auto y() const noexcept -> float;

	/**
	 * @brief Get width of subtexture.
	 * @return Subtexture width.
	 */
	auto w() const noexcept -> float;

	/**
	 * @brief Get height of subtexture.
	 * @return Subtexture height.
	 */
	auto h() const noexcept -> float;
};

/**
 * @brief
 */
using Subtexture = BasicSubtexture<entt::resource<SDL_Texture>>;

} // namespace rh

#include "subtexture.ipp"

#endif // ROUNDHELL_SUBTEXTURE_HPP

