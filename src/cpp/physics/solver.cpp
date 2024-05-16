
#include "solver.hpp"
#include <math.h>

namespace elso::solver
{

    void Model::setup()
    {
        // Resize arrays that will be carried through the game
        this->forces.resize(1);
    }

    bool Model::run(real output_frequency)
    {
        const int max_iterations = std::ceil(300.0 / this->_timestep); // 300s = 5min
        const int output_iterations = std::ceil(output_frequency / this->_timestep);

        auto done = [this, max_iterations](int it) -> bool
        {
            return it >= max_iterations && this->_status == MatchStatus::_ended;
        };

        // Game main loop
        bool is_input = true;
        for(int i = 0; !done(i); ++i)
        {
            // Gather game inputs
            if (is_input)
            {
                is_input = false;
            }

            // Process forces & torques on entities

            // Move entities
            this->_ball.move(
                (this->forces[0] / this->_ball._virtual_mass) + this->_gravity,
                this->_timestep);

            // Post iteration
            this->_current_time += this->_timestep;
            if (this->_current_time >= 300.0)
                this->_status = MatchStatus::_ended;
            
            if (output_iterations && (i % output_iterations == 0))
            {
                // printf("Ball at %d: (%.20f, %.20f)\n", i, this->_ball._gravity_center.x, this->_ball._gravity_center.y);
            }
        }

        return true;
    }

} // namespace elso::solver