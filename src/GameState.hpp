#pragma once
#include <ostream>

struct GameState
{
    int64_t gameTick;
    int64_t x1; // Unknown
};

std::ostream& operator<<(std::ostream& os, const GameState& gameState) {
    return os << "{ GameState| "
              << "gameTick: " << gameState.gameTick << "; "
              << "x1: " << gameState.x1 << "}";
}
