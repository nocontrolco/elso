
#include "solver.hpp"
#include <math.h>

namespace elso::solver
{

    bool Model::Run()
    {
        const int max_iterations = std::ceil(300.f / this->_timestep); // 300s = 5min

        auto done = [this, max_iterations](int it) -> bool
        {
            return it >= max_iterations && this->_status == MatchStatus::_ended;
        };

        for(int i = 0; !done(i); ++i)
        {
            this->_current_time += this->_timestep;
            if (this->_current_time >= 300.f)
                this->_status = MatchStatus::_ended;
        }

        return true;
    }

} // namespace elso::solver