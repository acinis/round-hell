#ifndef ROUNDHELL_CONCEPTS_HPP
#define ROUNDHELL_CONCEPTS_HPP

/**
 * @file src/concepts.hpp
 * @brief Project's concept library.
 */

#include <concepts>
#include <type_traits>

/** @cond INTERNAL */
namespace rh::internal {

/**
 * @brief Satisfied when `T` is same as `U` or `T` is a reference to `U`.
 * @tparam T Type to check.
 * @tparam U Type to check against.
 */
template<typename T, typename U>
concept SameAsOrReferenceTo = std::is_same_v<std::remove_reference_t<T>, U>;

} // namespace rh::internal
/** @endcond */

namespace rh {

/**
 * @brief Satisfied when `P` is a pointer or type usable like a pointer.
 * @tparam P Type to check.
 */
template<typename P>
concept PointerLike = std::is_pointer_v<P> || requires (P p)
{
	{ static_cast<bool>(p) };
	{ p.operator*() };
	{ p.operator->() } -> std::same_as<decltype(&*p)>;
};

/**
 * @brief Satisfied when `P` is `PointerLike` and can be dereferenced to `U` type (no conversion allowed).
 * @tparam P Type to check.
 * @tparam U Underlying type to check against.
 */
template<typename P, typename U>
concept ConcretePointerLike =
	(std::is_pointer_v<P> && std::is_same_v<std::remove_pointer_t<P>, U>) ||
	requires(P p, U u) {
		requires PointerLike<P>;
		{ p.operator*() } -> internal::SameAsOrReferenceTo<U>;
		{ p.operator->() } -> std::same_as<decltype(&u)>;
	}
;

} // namespace rh

#endif // ROUNDHELL_CONCEPTS_HPP

