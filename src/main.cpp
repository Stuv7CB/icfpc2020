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
