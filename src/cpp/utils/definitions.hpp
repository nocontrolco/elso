#pragma once

#include <cinttypes>
#include <type_traits>

typedef float real;
typedef double real_64;

/**
 * @brief Checks if a type is a POD (Plain Old Data) type
 *
 * @tparam T type to check
 */
template <typename T>
struct is_pod
{
    static constexpr bool value = std::is_trivial<T>::value && std::is_standard_layout<T>::value;
};

static_assert(sizeof(real) == 4, "Real type must be 32 bits");

struct real2 { real x, y; };
struct real3 { real x, y, z; };