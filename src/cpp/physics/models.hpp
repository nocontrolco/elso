#pragma once

#include "../utils/definitions.hpp"
#include "../utils/types.hpp"

namespace elso::solver
{

    /**
     * @brief Function to calculate the normal force due to a overlapping contact.
     * This method uses the Linear Spring-Damper Model.
     * 
     * @param overlap 
     * @param relative_normal_velocity 
     * @param stiffness_coeff 
     * @param damping_coeff 
     * @return real 
     */
    real normal_force(
        real overlap, real relative_normal_velocity, real stiffness_coeff, real damping_coeff)
    {
        if (overlap <= 0.0)
        {
            return 0.0;  // No contact
        }

        // Calculate the elastic force (spring component)
        real elasticForce = stiffness_coeff * overlap;

        // Calculate the damping force (damping component)
        real dampingForce = damping_coeff * relative_normal_velocity;

        // Total normal force
        return elasticForce + dampingForce;
    }

} // namespace elso::solver