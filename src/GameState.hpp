#pragma once
#include <cstdint>
#include <vector>
#include <ostream>
#include "Modulation.hpp"
#include "ShipAndCommands.hpp"

struct GameState
{
    int64_t gameTick;
    int64_t x1; // Unknown
    std::vector<ShipAndCommands> shipsAndCommands;
};

std::ostream& operator<<(std::ostream& os, const GameState& gameState);
