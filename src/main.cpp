#include <string>
#include <cstdint>
#include <iostream>
#include <sstream>
#include "Modulation.hpp"
#include "Transceiver.hpp"

void printResponse(std::vector<std::any> resp)
{
    std::cout << '(';
    for (auto &el : resp)
    {
        if (typeid(int64_t) == el.type())
        {
            std::cout << std::any_cast<int64_t>(el);
        }
        if (typeid(std::vector<std::any>) == el.type())
        {
            printResponse(std::any_cast<std::vector<std::any>>(el));
        }
        if (&el != &resp.back())
        {
            std::cout << ", ";
        }
    }
    std::cout << ')';
}

int main(int argc, char* argv[])
{
    std::shared_ptr<httplib::Response> serverResponse;
    if (argc != 3)
    {
        return 1;
    }

    const std::string serverUrl(argv[1]);
    const std::string playerKeyString(argv[2]);

    uint64_t playerKey;

    std::stringstream strStr(playerKeyString);

    strStr >> playerKey;

    std::cout << "ServerUrl: " << serverUrl << "; PlayerKey: " << playerKey << std::endl;

    Transceiver transeiver(serverUrl);

    std::vector<std::any> joinRequest =
    {
        std::any(2),
        std::any(playerKey),
        std::any(std::vector<std::any>())
    };

    std::cout << "Join Request" << std::endl;
    printResponse(joinRequest);

    auto joinResponseString = transeiver.send(Modulation::modulateList(joinRequest));
    auto joinResponseStringView = std::string_view(joinResponseString);

    auto joinResponse = Modulation::demodulateList(joinResponseStringView);
    std::cout << "Join Response" << std::endl;
    printResponse(joinResponse);

    std::vector<std::any> startRequest =
    {
        std::any(3),
        std::any(playerKey),
        std::any(std::vector<std::any>(4, std::any(0)))
    };

    std::cout << "Start Request" << std::endl;
    printResponse(startRequest);

    auto startResponseString = transeiver.send(Modulation::modulateList(startRequest));
    auto startResponseStringView = std::string_view(startResponseString);

    auto startResponse = Modulation::demodulateList(startResponseStringView);

    std::cout << "Start Response" << std::endl;
    printResponse(startResponse);

    auto gameState = std::any_cast<int64_t>(startResponse[1]);

    while (gameState != 2)
    {
    }

    return 0;
}
