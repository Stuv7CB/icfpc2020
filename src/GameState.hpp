#pragma once
#include <cstdint>
#include <vector>
#include <ostream>
#include "Modulation.hpp"
#include "ShipAndCommands.hpp"
#include <any>
#include <optional>

struct GameState
{
    int64_t gameTick;
    std::any x1; // Unknown
    std::vector<ShipAndCommands> shipsAndCommands;
};

std::ostream& operator<<(std::ostream& os, const GameState& gameState);

std::ostream& operator<<(std::ostream& os, const std::optional<GameState>& gameState);
