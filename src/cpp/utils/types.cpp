#include "types.hpp"
#include "math.hpp"

#include <cmath>

namespace elso::type
{

    void Ball::move(const real2& linear_acceleration, const real dt)
    {
        // Normal movement
        auto linear_displacement = linear_acceleration * dt * dt;
        this->_gravity_center += linear_displacement;
    }

} // namespace elso::type
