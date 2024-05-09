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

inline uint32_t days_between(uint32_t start, uint32_t end)
{
    // TODO: Better evaluate this function performance
    using namespace boost::gregorian;
    date d1(from_undelimited_string(std::to_string(start)));
    date d2(from_undelimited_string(std::to_string(end)));
    return (d2 - d1).days();
}

} // namespace elso::math