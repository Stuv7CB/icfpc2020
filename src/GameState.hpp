#pragma once
#include <ostream>
#include "Modulation.hpp"

struct GameState
{
    int64_t gameTick;
    int64_t x1; // Unknown
};

std::ostream& operator<<(std::ostream& os, const GameState& gameState);
