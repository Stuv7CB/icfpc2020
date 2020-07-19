#include "GameState.hpp"

std::ostream &operator<<(std::ostream &os, const GameState &gameState) {
    return os << "{ GameState| "
              << "gameTick: " << gameState.gameTick << "; "
              << "x1: " << gameState.x1 << "}";
}
