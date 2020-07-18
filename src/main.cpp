#include <iostream>
#include <regex>
#include <string>
#include <httplib.h>
#include "Modulation.hpp"

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
        std::cout << ", ";
    }
    std::cout << ')';
}

void errorCheck(std::shared_ptr<httplib::Response> &serverResponse)
{
    if (!serverResponse)
    {
        std::cout << "Unexpected server response:\nNo response from server" << std::endl;
        exit(1);
    }

    if (serverResponse->status != 200)
    {
        std::cout << "Unexpected server response:\nHTTP code: " << serverResponse->status
                  << "\nResponse body: " << serverResponse->body << std::endl;
        exit(2);
    }
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

        const std::regex urlRegexp("http://(.+):(\\d+)");
        std::smatch urlMatches;
        if (!std::regex_search(serverUrl, urlMatches, urlRegexp) || urlMatches.size() != 3)
        {
            std::cout << "Unexpected server response:\nBad server URL" << std::endl;
            return 1;
        }
        const std::string serverName = urlMatches[1];
        const int serverPort = std::stoi(urlMatches[2]);
        httplib::Client client(serverName, serverPort);
        serverResponse = client.Post(serverUrl.c_str(), playerKey.c_str(), "text/plain");
        errorCheck(serverResponse);
    }
    else
    {
        httplib::SSLClient client("icfpc2020-api.testkontur.ru");
        serverResponse =  client.Post("/aliens/send?apiKey=42d71c651c4a4048842b8973c8bb3608", "0", "text/plain");
        errorCheck(serverResponse);
        test = serverResponse->body;
        printResponse(Modulation::demodulateList(test));
        std::cout << std::endl;
        std::cout << "Server response: " << serverResponse->body << std::endl;
        serverResponse =  client.Post("/aliens/send?apiKey=42d71c651c4a4048842b8973c8bb3608",
                                      serverResponse->body, "text/plain");
        errorCheck(serverResponse);
        test = serverResponse->body;
        printResponse(Modulation::demodulateList(test));
        std::cout << std::endl;
    }

    std::cout << "Server response: " << serverResponse->body << std::endl;
    return 0;
}
