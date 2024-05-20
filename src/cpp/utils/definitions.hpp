#pragma once

#include <cinttypes>
#include <type_traits>

typedef double real;
typedef float real_32;

const double ELSO_TOL = 1e-10;
const double MAX_VELOCITY = 1e-10;

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

static_assert(sizeof(real) == 8, "Real type must be 32 bits");

struct real2 { real x, y; };
struct real3 { real x, y, z; };

inline real2 operator/(const real2& vector, const real scalar)
{
    return { vector.x / scalar, vector.y / scalar };
}

inline real2 operator*(const real2& vector, const real scalar)
{
    return { vector.x * scalar, vector.y * scalar };
}

inline real2 operator+(const real2& v1, const real2& v2)
{
    return { v1.x + v2.x, v1.y + v2.y };
}

inline real2 operator-(const real2& v1, const real2& v2)
{
    return { v1.x - v2.x, v1.y - v2.y };
}

inline void operator+=(real2& v1, const real2& v2)
{
    v1.x += v2.x;
    v1.y += v2.y;
}

inline void operator-=(real2& v1, const real2& v2)
{
    v1.x -= v2.x;
    v1.y -= v2.y;
}