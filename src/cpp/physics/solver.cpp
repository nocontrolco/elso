#include "solver.hpp"
#include "models.hpp"

#include <cmath>
#include <cstring>
#include <algorithm>

namespace elso::solver
{

    void Model::setup()
    {
        // Resize arrays that will be carried through the game
        this->forces.resize(1);
    }

    bool Model::run(real simulation_time, real output_frequency)
    {
        const int max_iterations = std::ceil(simulation_time / this->_timestep);
        const int output_iterations = std::ceil(output_frequency / this->_timestep);

        auto done = [this, max_iterations](int it) -> bool
        {
            return it >= max_iterations && this->_status == MatchStatus::_ended;
        };

        // Game main loop
        bool is_input = true;
        int count = 0;
        for(int i = 0; !done(i); ++i)
        {
            // Gather game inputs
            if (is_input)
            {
                is_input = false;
            }

            // Dispatch neighbors search for entities

            // Process forces & torques on entities
            this->ball_arena_interaction();

            // Move entities
            this->_ball.move(
                (this->forces[0] / this->_ball._virtual_mass) + this->_gravity,
                this->_timestep);

            // Post iteration
            this->_current_time += this->_timestep;
            if (this->_current_time >= simulation_time)
                this->_status = MatchStatus::_ended;
            
            if (output_iterations && (i % output_iterations == 0))
            {
                printf("Ball at %d: (%.20f, %.20f)\nVelocity: (%.20f, %.20f)\nForce: (%.20f, %.20f)\n",
                       i, this->_ball._gravity_center.x, this->_ball._gravity_center.y,
                       this->_ball._velocity.x, this->_ball._velocity.y,
                       this->forces[0].x, this->forces[0].y);
                printf("---------------------------------\n");
                // if (count++ > 250)
                //     exit(0);
            }

            std::fill_n(this->forces.begin(), this->forces.size(), real2 { });
        }

        return true;
    }

    /**
     * @brief Get overlap between all walls and the normal force
     * 
     */
    void Model::ball_arena_interaction()
    {
        auto& ball_forces = this->forces[0];
        const auto& ball = this->_ball;
        const auto& arena = this->_arena._bbox;

        // Left wall
        real overlap = std::max(
            0.0, ball._radius - ball._gravity_center.x - arena._min.x
        );
        ball_forces.x += normal_force(
            overlap, ball._velocity.x, this->_stiffness, this->_damping
        );

        // Right wall
        overlap = std::max(
            0.0, ball._radius + ball._gravity_center.x - arena._max.x
        );
        ball_forces.x -= normal_force(
            overlap, -ball._velocity.x, this->_stiffness, this->_damping
        );

        // Down wall
        overlap = std::max(
            0.0, ball._radius - ball._gravity_center.y - arena._min.y
        );
        ball_forces.y += normal_force(
            overlap, ball._velocity.y, this->_stiffness, this->_damping
        );

        // Up wall
        overlap = std::max(
            0.0, ball._radius + ball._gravity_center.y - arena._max.y
        );
        ball_forces.y -= normal_force(
            overlap, -ball._velocity.y, this->_stiffness, this->_damping
        );
    }

} // namespace elso::solver