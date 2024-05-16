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
        // Shape
        real _radius { 1.5 };

        // Inertia properties
        real _virtual_mass { 5000.0 };
        real2 _gravity_center { 0.0, 0.0 };

        void move(const real2& linear_acceleration, const real dt);
    };

    struct BoundingBox
    {
        real2 _min;
        real2 _max;
    };

    struct Car
    {
        // Shape: hitbox & levitation height
        BoundingBox _hitbox;
        real _levitation_height;

        // Inertia properties
        real _virtual_mass;
        real2 _gravity_center;
    };

    struct Arena
    {
        BoundingBox _bbox { { 0.0, 0.0 }, { 20.0, 20.0 } };
        real _corner_arc;
    };
} // namespace elso::type