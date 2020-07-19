#pragma once
#include "Modulation.hpp"
#include "GameResponse.hpp"
#include "GameState.hpp"
#include "StaticGameInfo.hpp"
#include "Vector.hpp"
#include "Commands.hpp"
#include "Ship.hpp"
#include "ShipAndCommands.hpp"

template<typename T>
static T fromList(const Modulation::List &list)
{
    if constexpr (std::is_same_v<T, GameState>)
    {
        GameState gameState;

        gameState.gameTick = std::get<int64_t>(list.value[0]);
        gameState.x1 = list.value[1];
        gameState.shipsAndCommands = fromList<std::vector<ShipAndCommands>>(std::get<Modulation::List>(list.value[2]));

        return gameState;
    }
    else if constexpr (std::is_same_v<T, std::vector<ShipAndCommands>>)
    {
        std::vector<ShipAndCommands> ships;

        for (auto &el : list.value)
        {
            ships.push_back(fromList<ShipAndCommands>(std::get<Modulation::List>(el)));
        }

        return ships;
    }
    else if constexpr (std::is_same_v<T, StaticGameInfo>)
    {
        StaticGameInfo staticGameInfo;
        staticGameInfo.x0 = list.value[0];
        staticGameInfo.role = static_cast<Role>(std::get<int64_t>(list.value[1]));
        staticGameInfo.x2 = list.value[2];
        staticGameInfo.x3 = list.value[3];
        staticGameInfo.x4 = list.value[4];
        return staticGameInfo;
    }
    else if constexpr (std::is_same_v<T, GameResponse>)
    {
        GameResponse gameResponse;

        gameResponse.gameStage = static_cast<GameStage>(std::get<int64_t>(list.value[1]));

        gameResponse.staticGameInfo = fromList<StaticGameInfo>(std::get<Modulation::List>(list.value[2]));

        if (list.value.size() == 4)
        {
            gameResponse.gameState = fromList<GameState>(std::get<Modulation::List>(list.value[3]));
        }

        return gameResponse;
    }
    else if constexpr (std::is_same_v<T, AccCommand>)
    {
        AccCommand accCommand;
        accCommand.shipId = std::get<int64_t>(list.value[1]);
        accCommand.vector = fromList<Vector>(std::get<Modulation::List>(list.value[2]));

        return accCommand;
    }
    else if constexpr (std::is_same_v<T, DetonateCommand>)
    {
        DetonateCommand detonateCommand;
        detonateCommand.shipId = std::get<int64_t>(list.value[1]);

        return detonateCommand;
    }
    else if constexpr (std::is_same_v<T, ShootCommand>)
    {
        ShootCommand shootCommand;
        shootCommand.shipId = std::get<int64_t>(list.value[1]);
        shootCommand.vector = fromList<Vector>(std::get<Modulation::List>(list.value[2]));
        shootCommand.x3 = list.value[3];

        return shootCommand;
    }
    else if constexpr (std::is_same_v<T, Ship>)
    {
        Ship ship;

        ship.role = static_cast<Role>(std::get<int64_t>(list.value[0]));
        ship.shipId = std::get<int64_t>(list.value[1]);
        ship.position = fromList<Vector>(std::get<Modulation::List>(list.value[2]));
        ship.velocity = fromList<Vector>(std::get<Modulation::List>(list.value[3]));
        ship.x4 = list.value[4];
        ship.x5 = list.value[5];
        ship.x6 = list.value[6];
        ship.x7 = list.value[7];

        return ship;
    }
    else if constexpr (std::is_same_v<T, ShipAndCommands>)
    {
        ShipAndCommands ship;

        ship.ship = fromList<Ship>(std::get<Modulation::List>(list.value[0]));
        ship.appliedCommands = fromList<std::vector<std::variant<AccCommand, DetonateCommand, ShootCommand>>>(std::get<Modulation::List>(list.value[1]));

        return ship;
    }
    else if constexpr (std::is_same_v<T, std::vector<std::variant<AccCommand, DetonateCommand, ShootCommand>>>)
    {
        std::vector<std::variant<AccCommand, DetonateCommand, ShootCommand>> vector;
        for (auto &el : list.value)
        {
            auto value = std::get<Modulation::List>(el);
            switch (std::get<int64_t>(value.value[0]))
            {
            case 0:
                vector.push_back(fromList<AccCommand>(value));
                break;
            case 1:
                vector.push_back(fromList<DetonateCommand>(value));
                break;
            case 2:
                vector.push_back(fromList<ShootCommand>(value));
                break;
            }
        }
        return vector;
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
