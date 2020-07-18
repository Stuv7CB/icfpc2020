#include <string>
#include <cstdint>
#include <iostream>
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
    std::vector<std::any> testData = {std::any(static_cast<int64_t>(1)),
                                      std::any(std::vector<std::any>({std::any(std::vector<std::any>({static_cast<int64_t>(0), static_cast<int64_t>(8450062863238389037)})),
                                                                      std::any(std::vector<std::any>({static_cast<int64_t>(1), static_cast<int64_t>(6382104060584514366)}))})
                                              )};
    std::cout << Modulation::modulateList(testData) << std::endl;
    std::string_view test = "110110000111011111100001001110101100111000";
    printResponse(Modulation::demodulateList(test));
    std::cout << std::endl;

    std::shared_ptr<httplib::Response> serverResponse;
    if (argc != 3)
    {
        return 1;
    }

    const std::string serverUrl(argv[1]);
    const std::string playerKey(argv[2]);

    std::cout << "ServerUrl: " << serverUrl << "; PlayerKey: " << playerKey << std::endl;

    Transceiver transeiver(serverUrl);

    return 0;
}
