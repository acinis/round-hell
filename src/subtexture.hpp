#ifndef ROUNDHELL_SUBTEXTURE_HPP
#define ROUNDHELL_SUBTEXTURE_HPP

/**
 * @file src/subtexture.hpp
 * @brief Helper class for managing textures that are part of other texture (atlases, sheets, etc).
 */

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

namespace rh {

/**
 * @brief Tight wrapper around `SDL_Texture` that has offset and size. Ideal for using with atlases.
 */
class Subtexture final
{
	SDL_Texture* _texture {nullptr}; //!< whole texture (eg. altas or sprite sheet)

	float _x {0.0f}; //!< x offset (position in whole texture)
	float _y {0.0f}; //!< y offset (position in whole texture)
	float _w {0.0f}; //!< width of subtexture
	float _h {0.0f}; //!< height of subtexture

public:

	/** @brief Default initialization is not allowed. */
	Subtexture() = delete;

	/**
	 * @brief Creates a new `Subtexture` instance.
	 *
	 * @warning
	 * - `x`, `y`, `w`, `h` are not validated if they are in range of given texture size.
	 * - `texture` is checked against `nullptr` only in debug build via assertion.
	 * - `x` and `y` are checked against `w` and `h` only in debug build via assertion.
	 *
	 * @param texture Pointer to `SDL_Texture` for underlying texture data.
	 * @param x Subtexture `x` offset inside whole texture.
	 * @param y Subtexture `y` offset inside whole texture.
	 * @param w Subtexture width.
	 * @param h Subtexture height.
	 */
	Subtexture(SDL_Texture *texture, float x, float y, float w, float h) noexcept;

	/**
	 * @brief Creates a new `Subtexture` instance.
	 *
	 * @warning
	 * - `offset` and `size` are not validated if they are in range of given texture size.
	 * - `texture` is checked against `nullptr` only in debug build via assertion.
	 * - `x` and `y` are checked against `w` and `h` only in debug build via assertion.
	 *
	 * @param texture Pointer to `SDL_Texture` for underlying texture data.
	 * @param offset Subtexture `x` and `y` offset inside whole texture.
	 * @param size Subtexture size (width is `size.x` and height is `size.y`).
	 */
	Subtexture(SDL_Texture *texture, SDL_FPoint offset, SDL_FPoint size) noexcept;

	/**
	 * @brief Creates a new `Subtexture` instance.
	 *
	 * @warning
	 * - `rect` is not validated if it is in range of given texture size.
	 * - `texture` is checked against `nullptr` only in debug build via assertion.
	 * - `x` and `y` are checked against `w` and `h` only in debug build via assertion.
	 *
	 * @param texture Pointer to `SDL_Texture` for underlying texture data.
	 * @param rect Subtexture rectangle (offset - `rect.x`, `rect.y` and size - `rect.w`, `rect.h`).
	 */
	Subtexture(SDL_Texture *texture, SDL_FRect rect) noexcept;

	/**
	 * @brief Creates a new `Subtexture` instance with default offset (0.0f, 0.0f).
	 *
	 * This will query underlying texture for width and height, and can throw!
	 *
	 * @warning
	 * - `texture` is checked against `nullptr` only in debug build via assertion.
	 *
	 * @param texture Pointer to `SDL_Texture` for underlying texture data.
	 *
	 * @throw rh::RuntimeException If there is an error getting texture size.
	 */
	Subtexture(SDL_Texture *texture);

	/**
	 * @brief Creates a new `Subtexture` instance with default offset (0.0f, 0.0f).
	 *
	 * @warning
	 * - `w`, `h` are not validated if they are in range of given texture size.
	 * - `texture` is checked against `nullptr` only in debug build via assertion.
	 *
	 * @param texture Pointer to `SDL_Texture` for underlying texture data.
	 * @param w Subtexture width.
	 * @param h Subtexture height.
	 */
	Subtexture(SDL_Texture *texture, float w, float h) noexcept;

	/**
	 * @brief Creates a new `Subtexture` instance with default offset (0.0f, 0.0f).
	 *
	 * @warning
	 * - `size` is not validated if it is in range of given texture size.
	 * - `texture` is checked against `nullptr` only in debug build via assertion.
	 *
	 * @param texture Pointer to `SDL_Texture` for underlying texture data.
	 * @param size Subtexture size (width is `size.x` and height is `size.y`).
	 * @return
	 */
	Subtexture(SDL_Texture *texture, SDL_FPoint size) noexcept;

	/**
	 * @brief Default copy constructor.
	 */
	Subtexture(const Subtexture&) noexcept = default;

	/**
	 * @brief Default move constructor.
	 */
	Subtexture(Subtexture&&) noexcept = default;

	/**
	 * @brief Default destructor.
	 */
	~Subtexture() = default;

	/**
	 * @brief Default copy assignment operator.
	 * @return This `Subtexture` instance.
	 */
	auto operator=(const Subtexture&) noexcept -> Subtexture& = default;

	/**
	 * @brief Default move assignment operator.
	 * @return This `Subtexture` instance.
	 */
	auto operator=(Subtexture&&) noexcept -> Subtexture& = default;

	/**
	 * @brief Get raw pointer to underlying texture.
	 *
	 * @warning Changes to this data will be not reflected automatically in `Subtexture` instance.
	 * @warning This gives access to *whole* texture, not only part used by `Subtexture` instance.
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

} // namespace rh

#endif // ROUNDHELL_SUBTEXTURE_HPP

