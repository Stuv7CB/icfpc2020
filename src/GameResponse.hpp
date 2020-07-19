#pragma once
#include <ostream>
#include <string>
#include "StaticGameInfo.hpp"
#include "GameState.hpp"

enum class GameStage : int64_t
{
    NotStarted = 0,
    Running = 1,
    Finished = 2,
};

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

std::ostream& operator<<(std::ostream& os, const GameStage gameStage)
{
    return os << getText(gameStage);
}

struct GameResponse
{
    const int64_t result = 1;
    GameStage gameStage;
    StaticGameInfo staticGameInfo;
    GameState gameState;
};

std::ostream& operator<<(std::ostream& os, const GameResponse &gameResponse)
{
    return os << "{ GameResponse| "
              << "result: " << gameResponse.result << "; "
              << "gameStage: " << gameResponse.gameStage << "; "
              << "staticGameInfo: " << gameResponse.staticGameInfo << "; "
              << "gameState: " << gameResponse.gameState << "}";
}
