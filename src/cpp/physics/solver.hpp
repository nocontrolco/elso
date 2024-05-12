#pragma once

#include "../utils/definitions.hpp"
#include "../utils/types.hpp"

using namespace elso;

namespace elso::solver
{
    enum MatchStatus
    {
        _notStarted = 0,
        _kickoff = 1,
        _ended = 2
    };

    struct Model
    {
        // World parameters
        const real2 _gravity { .x = 0.f, .y = -9.81f };
        const real _timestep { 5e-5f }; // 0.0005s per iteration
        type::Arena _arena;

        // Moving Agents
        std::vector<type::Car> _cars;
        type::Ball _ball;
        real _current_time { 0.f };

        MatchStatus _status { _notStarted };

        bool Run();
    };
} // namespace elso::solver