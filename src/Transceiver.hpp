#pragma once
#include <memory>
#include <httplib.h>

class Transceiver
{
public:
    Transceiver(const std::string &serverPath, const std::string &playerKey);

    std::string send(std::string_view data);

private:
    std::unique_ptr<httplib::Client> _client;
    std::string _serverPath = "/aliens/send?apiKey=42d71c651c4a4048842b8973c8bb3608";
    std::string _playerKey;

    void _errorCheck(std::shared_ptr<httplib::Response> &serverResponse);
};
