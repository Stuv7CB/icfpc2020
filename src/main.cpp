#include <string>
#include "Modulation.hpp"
#include "Transceiver.hpp"

void printResponse(std::vector<std::any> resp)
{
    std::cout << '(';
    for (auto &el : resp)
    {
        if (typeid(BigInt) == el.type())
        {
            std::cout << std::any_cast<BigInt>(el);
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
    std::string_view test = "110110000111011111100001001110101100111000";
    printResponse(Modulation::demodulateList(test));
    std::cout << std::endl;

    std::shared_ptr<httplib::Response> serverResponse;
    if (argc == 3)
    {
        const std::string serverUrl(argv[1]);
        const std::string playerKey(argv[2]);

        std::cout << "ServerUrl: " << serverUrl << "; PlayerKey: " << playerKey << std::endl;

        Transceiver(serverUrl, playerKey);
    }
    else
    {
        Transceiver transceiver;
        auto response = transceiver.send("0");
        test = response;
        printResponse(Modulation::demodulateList(test));
        std::cout << std::endl;

        response = transceiver.send(response);
        test = response;
        printResponse(Modulation::demodulateList(test));
        std::cout << std::endl;

        response = transceiver.send("11011000011101000");
        test = response;
        printResponse(Modulation::demodulateList(test));
        std::cout << std::endl;
    }

    return 0;
}
