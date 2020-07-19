#include "GameResponse.hpp"

std::ostream &operator<<(std::ostream &os, const GameResponse &gameResponse)
{
    return os << "{ GameResponse| "
              << "result: " << gameResponse.result << "; "
              << "gameStage: " << gameResponse.gameStage << "; "
              << "staticGameInfo: " << gameResponse.staticGameInfo << "; "
              << "gameState: " << gameResponse.gameState << "}";
}

std::ostream &operator<<(std::ostream &os, const GameStage gameStage)
{
    return os << getText(gameStage);
}

std::string getText(const GameStage gameStage)
{
    switch (gameStage)
    {
    case GameStage::NotStarted:
        return "NotStarted";
    case GameStage::Running:
        return "Running";
    case GameStage::Finished:
        return "Finished";
    }
}
