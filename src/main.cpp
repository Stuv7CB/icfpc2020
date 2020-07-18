#include <string>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <type_traits>
#include "Modulation.hpp"
#include "Transceiver.hpp"
#include "helper.hpp"

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

    auto joinResponseString = transeiver.send(Modulation::modulateList(joinRequest));
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
                            std::variant<int64_t, Modulation::List>(0),
                            std::variant<int64_t, Modulation::List>(0),
                            std::variant<int64_t, Modulation::List>(0),
                            std::variant<int64_t, Modulation::List>(0),
                        }))
    };

    std::cout << "Start Request" << std::endl;
    printResponse(startRequest);

    auto startResponseString = transeiver.send(Modulation::modulateList(startRequest));
    auto startResponseStringView = std::string_view(startResponseString);

    auto startResponse = Modulation::demodulateList(startResponseStringView);

    std::cout << "Start Response" << std::endl;
    printResponse(startResponse);

    auto gameState = std::get<int64_t>(startResponse.value[1]);

    while (gameState != 2)
    {
        break;
    }

    return 0;
}
