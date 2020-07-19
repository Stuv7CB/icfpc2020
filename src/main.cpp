#include <string>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <type_traits>
#include "Modulation.hpp"
#include "Transceiver.hpp"
#include "helper.hpp"
#include "StaticGameInfo.hpp"
#include "GameResponse.hpp"
#include "Converter.hpp"
#include "BasicOrbitAlgo.hpp"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        return 1;
    }

    const std::string serverUrl(argv[1]);
    const std::string playerKeyString(argv[2]);

    int64_t playerKey;

    std::stringstream strStr(playerKeyString);

    strStr >> playerKey;

    std::cout << "ServerUrl: " << serverUrl << "; PlayerKey: " << playerKey << std::endl;

    Transceiver transeiver(serverUrl);

    Modulation::List joinRequest;
    joinRequest.value = std::vector<std::variant<int64_t, Modulation::List>>
    {
        std::variant<int64_t, Modulation::List>(2),
        std::variant<int64_t, Modulation::List>(playerKey),
        std::variant<int64_t, Modulation::List>(Modulation::List()),
    };

    std::cout << "Join Request" << std::endl;
    printResponse(joinRequest);
    auto joinRequestString = Modulation::modulateList(joinRequest);
    std::cout << joinRequestString << std::endl;
    auto joinResponseString = transeiver.send(joinRequestString);
    auto joinResponseStringView = std::string_view(joinResponseString);

    auto joinResponse = Modulation::demodulateList(joinResponseStringView);
    std::cout << "Join Response" << std::endl;
    printResponse(joinResponse);

    Modulation::List startRequest;
    startRequest.value = std::vector<std::variant<int64_t, Modulation::List>>
    {
        std::variant<int64_t, Modulation::List>(3),
        std::variant<int64_t, Modulation::List>(playerKey),
        std::variant<int64_t, Modulation::List>(
                    Modulation::List(
                        std::vector<std::variant<int64_t, Modulation::List>>
                        {
                            std::variant<int64_t, Modulation::List>(1),
                            std::variant<int64_t, Modulation::List>(2),
                            std::variant<int64_t, Modulation::List>(3),
                            std::variant<int64_t, Modulation::List>(4),
                        }))
    };

    std::cout << "Start Request" << std::endl;
    printResponse(startRequest);

    auto startRequestString = Modulation::modulateList(startRequest);
    std::cout << startRequestString << std::endl;

    auto startResponseString = transeiver.send(startRequestString);
    auto startResponseStringView = std::string_view(startResponseString);

    auto startResponse = Modulation::demodulateList(startResponseStringView);

    std::cout << "Start Response" << std::endl;
    printResponse(startResponse);

    auto response = fromList<GameResponse>(startResponse);
    auto gameState = response.gameStage;

    const auto role = response.staticGameInfo.role;
    BasicOrbitAlgo orbitAlgo;
    while (gameState != GameStage::Finished)
    {
        Ship *ship = nullptr;
        for (auto &shipcom : response.gameState.value().shipsAndCommands)
        {
            if (shipcom.ship.role == role)
            {
                ship = &shipcom.ship;
            }
        }
        auto acceleration = orbitAlgo.calculateSpeed(ship->position, ship->velocity);

        Modulation::List comandRequest;
        comandRequest.value = std::vector<std::variant<int64_t, Modulation::List>>
        {
            std::variant<int64_t, Modulation::List>(4),
            std::variant<int64_t, Modulation::List>(playerKey),
            std::variant<int64_t, Modulation::List>(
                        Modulation::List({
                            std::variant<int64_t, Modulation::List>(Modulation::List(
                                             {std::variant<int64_t, Modulation::List>(1),
                                              std::variant<int64_t, Modulation::List>(ship->shipId),
                                              /*Modulation::List({std::variant<int64_t, Modulation::List>(acceleration.x),
                                                                std::variant<int64_t, Modulation::List>(acceleration.y)
                                                                })*/
                                                            }))
                                                        })
                                                    )
        };
        std::cout << "Comand Request" << std::endl;
        printResponse(comandRequest);

        auto comandRequestString = Modulation::modulateList(comandRequest);

        auto comandResponseString = transeiver.send(comandRequestString);
        auto comandResponseStringView = std::string_view(comandResponseString);

        auto comandResponse = Modulation::demodulateList(comandResponseStringView);

        std::cout << "Comand Response" << std::endl;
        printResponse(comandResponse);

        response = fromList<GameResponse>(comandResponse);

        std::cout << response << std::endl;

        gameState = response.gameStage;
    }

    return 0;
}
