#ifndef ROUNDHELL_VERSION_HPP
#define ROUNDHELL_VERSION_HPP

/**
 * @file src/version.hpp
 * @brief App version and simple helpers.
 */

#include "config/commit.hpp"

/** @brief Major version number macro. */
#define ROUNDHELL_VERSION_MAJOR 0
/** @brief Minor version number macro. */
#define ROUNDHELL_VERSION_MINOR 2
/** @brief Patch version number macro. */
#define ROUNDHELL_VERSION_PATCH 5

/** @cond INTERNAL */
// [X]STR macros fits into utils, but I don't like to `#include` it here.
// For now make them an internal helper.
#define ROUNDHELL_DETAIL_STR(s) #s
/** @endcond */

/**
 * @brief Make version string literal (three components, eg. `(1,2,3) -> "1" "." "2" "." "3"`).
 *
 * @param a Major version number.
 * @param b Minor version number.
 * @param c Patch version number.
 */
#define ROUNDHELL_MAKE_VERSION(a, b, c) \
	ROUNDHELL_DETAIL_STR(a) "." \
	ROUNDHELL_DETAIL_STR(b) "." \
	ROUNDHELL_DETAIL_STR(c)

/** @brief Full version as string literal (eg. `"1" "." "2" "." "3"`). */
#define ROUNDHELL_VERSION ROUNDHELL_MAKE_VERSION( \
	ROUNDHELL_VERSION_MAJOR, \
	ROUNDHELL_VERSION_MINOR, \
	ROUNDHELL_VERSION_PATCH \
)

/**
 * @brief Make version number literal (three components, eg.`(1,2,3) -> 1002003`).
 *
 * Another example: `(11, 2, 33) -> 11002033`.
 *
 * Version number will fit in 32-bit integer, eg. `std::int_fast32_t`.
 *
 * @param a Major version number.
 * @param b Minor version number.
 * @param c Patch version number.
 */
#define ROUNDHELL_MAKE_VERSION_NUMBER(a, b, c) (a * 1000000 + b * 1000 + c)

/** @brief Full version as number literal (eg. `1002003`). */
#define ROUNDHELL_VERSION_NUMBER ROUNDHELL_MAKE_VERSION_NUMBER( \
	ROUNDHELL_VERSION_MAJOR, \
	ROUNDHELL_VERSION_MINOR, \
	ROUNDHELL_VERSION_PATCH \
)

#endif // ROUNDHELL_VERSION_HPP

