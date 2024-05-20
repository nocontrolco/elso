#pragma once

#include "definitions.hpp"

#include <boost/date_time/gregorian/gregorian.hpp>

#include <string>
#include <cmath>

namespace elso::math 
{

inline bool is_close(real a, real b, real tol = 1e-5)
{
    return fabs(a - b) <= tol;
}

} // namespace elso::math