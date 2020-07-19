#include "GameState.hpp"

std::ostream &operator<<(std::ostream &os, const GameState &gameState)
{
    return os << "{ GameState| "
              << "gameTick: " << gameState.gameTick << "; "
              << "x1: " << gameState.x1 << "; "
              << "shipsAndCommands: " << gameState.shipsAndCommands << "}";
}

std::ostream &operator<<(std::ostream &os, const std::optional<GameState> &gameState)
{
    if (gameState.has_value())
    {
        return os << gameState.value();
    }
    return os << "<unknown>";
}
