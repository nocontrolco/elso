#pragma once

#include "definitions.hpp"

#include <cassert>
#include <string>
#include <vector>
#include <memory>

namespace elso::type
{
    struct Ball
    {
        real _radius;
        real _virtual_mass;
    };

    struct BoundingBox
    {
        real2 _min;
        real2 _max;
    };

    struct Car
    {
        // Shape: hitbox & wheels
        BoundingBox _hitbox;
        real _wheel_radius;

        // Inertia properties
        real _virtual_mass;
        real2 _gravity_center;
    };

    struct Arena
    {
        BoundingBox _bbox;
        real _corner_arc;
    };
} // namespace elso::type