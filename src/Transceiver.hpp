#pragma once
#include <memory>
#include <httplib.h>

class Transceiver
{
public:
    Transceiver(const std::string &serverUrl);

    std::string send(std::string_view data);

private:
    std::unique_ptr<httplib::Client> _client;
    std::string _serverPath = "/aliens/send";

    void _errorCheck(std::shared_ptr<httplib::Response> &serverResponse);
};
