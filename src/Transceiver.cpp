#include "Transceiver.hpp"
#include <regex>

Transceiver::Transceiver()
{
    _client = std::make_unique<httplib::SSLClient>("icfpc2020-api.testkontur.ru");
}

Transceiver::Transceiver(const std::string &serverPath, const std::string &playerKey)
    : _serverPath(serverPath), _playerKey(playerKey)
{
    const std::regex urlRegexp("http://(.+):(\\d+)");
    std::smatch urlMatches;
    if (!std::regex_search(serverPath, urlMatches, urlRegexp) || urlMatches.size() != 3)
    {
        throw std::runtime_error("Unexpected server response:\nBad server URL");
    }
    const std::string serverName = urlMatches[1];
    const int serverPort = std::stoi(urlMatches[2]);

    _client = std::make_unique<httplib::Client>(serverName, serverPort);
    auto serverResponse = _client->Post(serverPath.c_str(), playerKey.c_str(), "text/plain");
    _errorCheck(serverResponse);
}

std::string Transceiver::send(std::string_view data)
{
    auto serverResponse = _client->Post(_serverPath.c_str(), data.data(), "text/plain");
    _errorCheck(serverResponse);
    return serverResponse->body;
}

void Transceiver::_errorCheck(std::shared_ptr<httplib::Response> &serverResponse)
{
    if (!serverResponse)
    {
        throw std::runtime_error("Unexpected server response:\nNo response from server");
    }

    if (serverResponse->status != 200)
    {
        throw std::runtime_error("Unexpected server response:\nHTTP code: " + std::to_string(serverResponse->status)
                                 + "\nResponse body: " + serverResponse->body);
    }
    std::cout << "Server response: " << serverResponse->body << std::endl;
}
