#pragma once
#include <ostream>
#include <string>
#include <optional>
#include "StaticGameInfo.hpp"
#include "GameState.hpp"
#include "Modulation.hpp"
#include "type_traits"
#include "helper.hpp"

enum class GameStage : int64_t
{
    NotStarted = 0,
    Running = 1,
    Finished = 2,
};

std::string getText(const GameStage gameStage);

std::ostream& operator<<(std::ostream& os, const GameStage gameStage);

struct GameResponse
{
    int64_t result = 1;
    GameStage gameStage;
    StaticGameInfo staticGameInfo;
    std::optional<GameState> gameState;
};

std::ostream& operator<<(std::ostream& os, const GameResponse &gameResponse);
