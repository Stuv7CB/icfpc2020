#pragma once
#include "Modulation.hpp"
#include "GameResponse.hpp"
#include "GameState.hpp"
#include "StaticGameInfo.hpp"
#include "Vector.hpp"

template<typename T>
static T fromList(const Modulation::List &list)
{
    if constexpr (std::is_same_v<T, GameState>)
    {
        GameState gameState;

        gameState.gameTick = std::get<int64_t>(list.value[0]);
        gameState.x1 = std::get<int64_t>(list.value[1]);

        return gameState;
    }
    else if constexpr (std::is_same_v<T, StaticGameInfo>)
    {
        StaticGameInfo staticGameInfo;
        staticGameInfo.x0 = std::get<int64_t>(list.value[0]);
        staticGameInfo.role = static_cast<Role>(std::get<int64_t>(list.value[0]));
        staticGameInfo.x2 = std::get<int64_t>(list.value[2]);
        staticGameInfo.x3 = std::get<int64_t>(list.value[3]);
        staticGameInfo.x4 = std::get<int64_t>(list.value[4]);
        return staticGameInfo;
    }
    else if constexpr (std::is_same_v<T, GameResponse>)
    {
        GameResponse gameResponse;

        gameResponse.gameStage = static_cast<GameStage>(std::get<int64_t>(list.value[1]));

        gameResponse.staticGameInfo = fromList<StaticGameInfo>(std::get<Modulation::List>(list.value[2]));

        return gameResponse;
    }
    else if constexpr (std::is_same_v<T, Vector>)
    {
        Vector vector;

        vector.x = std::get<int64_t>(list.value[0]);
        vector.y = std::get<int64_t>(list.value[1]);

        return vector;
    }
    else
    {
        static_assert(always_false_v<T>, "non-exhaustive visitor!");
    }
}
