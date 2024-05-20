#include "types.hpp"
#include "math.hpp"

#include <cmath>

namespace elso::type
{

    void Ball::move(const real2& linear_acceleration, const real dt)
    {
        // Normal movement
        this->_velocity += linear_acceleration * dt;
        this->_gravity_center += this->_velocity * dt;
    }

} // namespace elso::type
